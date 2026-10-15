#include "Venda.hpp"

#include <iomanip>
#include <sstream>
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
    if (percentualDesconto < 0.0 || percentualDesconto > 100.0) {
        throw PagamentoInvalidoException("O desconto deve estar entre 0 e 100.");
    }
    if (percentualDesconto > 0.0 && (gerente == nullptr || !gerente->aprovarDesconto(percentualDesconto))) {
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
    linha << cliente_->getCpf() << ";" << vendedor_->getId() << ";"
          << valorFinal_ << ";" << comissao_ << ";" << situacao;
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

void Venda::definirData(const std::string& data) {
    if (data.size() != 10 || data[4] != '-' || data[7] != '-') {
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
