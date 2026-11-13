#include "Venda.hpp"

#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <limits>
#include <vector>
#include "Cliente.hpp"
#include "FormaPagamento.hpp"
#include "Gerente.hpp"
#include "PagamentoInvalidoException.hpp"
#include "PermissaoNegadaException.hpp"
#include "Vendedor.hpp"

Venda::Venda(Cliente* cliente, Vendedor* vendedor, const Carrinho& carrinho)
    : cliente_(cliente), vendedor_(vendedor), carrinho_(carrinho),
      valorFinal_(0.0), comissao_(0.0), concluida_(false), cancelada_(false) {
    if (cliente == nullptr || vendedor == nullptr) {
        throw PagamentoInvalidoException("A venda precisa de cliente e vendedor.");
    }
    if (carrinho.estaVazio()) {
        throw PagamentoInvalidoException("O carrinho esta vazio.");
    }
}

void Venda::finalizar(FormaPagamento* pagamento, double percentualDesconto, Gerente* gerente) {
    if (concluida_ || cancelada_) {
        throw PagamentoInvalidoException("Esta venda ja foi finalizada ou cancelada.");
    }
    if (pagamento == nullptr) {
        throw PagamentoInvalidoException("Escolha uma forma de pagamento.");
    }
    if (!(percentualDesconto >= 0.0 && percentualDesconto <= 100.0)) {
        throw PagamentoInvalidoException("O desconto deve estar entre 0 e 100.");
    }
    if (percentualDesconto > 0.0 && (gerente == nullptr || !gerente->aprovarDescontoMaior(percentualDesconto))) {
        throw PermissaoNegadaException("Desconto sem aprovacao do gerente.");
    }

    const double comDesconto = carrinho_.calcularTotal() * (1.0 - percentualDesconto / 100.0);
    const double valor = pagamento->calcularValorFinal(comDesconto);
    pagamento->validarPagamento(valor);

    valorFinal_ = valor;
    comissao_ = vendedor_->calcularComissao(valor);
    concluida_ = true;
}

void Venda::cancelar() {
    if (!concluida_) {
        throw PagamentoInvalidoException("So da para cancelar uma venda concluida.");
    }
    concluida_ = false;
    cancelada_ = true;
    comissao_ = 0.0;
}

std::string Venda::gerarComprovante() const {
    std::ostringstream texto;
    texto << std::fixed << std::setprecision(2);
    texto << "Cliente: " << cliente_->getNome() << "\n";
    texto << "Vendedor: " << vendedor_->getNome() << "\n";
    for (const ItemCarrinho& item : carrinho_.getItens()) {
        texto << item.getQuantidade() << "x " << item.getDescricao()
              << " = " << item.calcularSubtotal() << "\n";
    }
    texto << "Total: " << valorFinal_ << "\n";
    return texto.str();
}

std::string Venda::toLinha() const {
    std::string situacao = "aberta";
    if (cancelada_) {
        situacao = "cancelada";
    } else if (concluida_) {
        situacao = "concluida";
    }
    std::ostringstream linha;
   linha << cliente_->getCpf() << ";"
      << vendedor_->getId() << ";"
      << valorFinal_ << ";"
      << comissao_ << ";"
      << situacao << ";"
      << data_;
      linha << std::setprecision(std::numeric_limits<double>::max_digits10);

for (const ItemCarrinho& item : carrinho_.getItens()) {
    linha << ";"
          << item.getDescricao() << ";"
          << item.getPrecoUnitario() << ";"
          << item.getQuantidade();
}
    return linha.str();
}

double Venda::getValorFinal() const {
    return valorFinal_;
}

double Venda::getComissao() const {
    return comissao_;
}

bool Venda::estaConcluida() const {
    return concluida_;
}

bool Venda::estaCancelada() const {
    return cancelada_;
}

bool Venda::dataValida(const std::string& data) {
    if (data.size() != 10 || data[4] != '-' || data[7] != '-') {
        return false;
    }
    for (std::size_t i = 0; i < data.size(); ++i) {
        if (i != 4 && i != 7 && !std::isdigit(static_cast<unsigned char>(data[i]))) {
            return false;
        }
    }
    const int mes = std::atoi(data.substr(5, 2).c_str());
    const int dia = std::atoi(data.substr(8, 2).c_str());
    return mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31;
}

void Venda::definirData(const std::string& data) {
    if (!dataValida(data)) {
        throw PagamentoInvalidoException("A data deve estar no formato AAAA-MM-DD.");
    }
    data_ = data;
}

std::string Venda::getData() const {
    return data_;
}

std::string Venda::getIdVendedor() const {
    return vendedor_->getId();
}

std::string Venda::getCpfCliente() const {
    return cliente_->getCpf();
}
Venda Venda::deLinha(
    const std::string& linha,
    Cliente* cliente,
    Vendedor* vendedor
) {
    std::stringstream ss(linha);
    std::vector<std::string> campos;
    std::string campo;

    while (std::getline(ss, campo, ';')) {
        campos.push_back(campo);
    }

    if (campos.size() < 9 || (campos.size() - 6) % 3 != 0) {
        throw PagamentoInvalidoException(
            "Formato invalido de venda salva."
        );
    }

  Carrinho carrinho;

for (std::size_t i = 6; i < campos.size(); i += 3) {
    const std::string& descricao = campos[i];
    double preco = std::stod(campos[i + 1]);
    int quantidade = std::stoi(campos[i + 2]);

    ItemCarrinho item(descricao, preco, quantidade);
    carrinho.adicionarItem(item);
}

if (cliente == nullptr || vendedor == nullptr) {
    throw PagamentoInvalidoException(
        "Cliente ou vendedor nao encontrado."
    );
}

if (campos[0] != cliente->getCpf() ||
    campos[1] != vendedor->getId()) {
    throw PagamentoInvalidoException(
        "Cliente ou vendedor nao corresponde a venda salva."
    );
}

Venda venda(cliente, vendedor, carrinho);

venda.valorFinal_ = std::stod(campos[2]);
venda.comissao_ = std::stod(campos[3]);

if (campos[4] == "concluida") {
    venda.concluida_ = true;
} else if (campos[4] == "cancelada") {
    venda.cancelada_ = true;
} else if (campos[4] != "aberta") {
    throw PagamentoInvalidoException(
        "Situacao invalida de venda salva."
    );
}

if (!campos[5].empty()) {
    venda.definirData(campos[5]);
}

return venda;
}
