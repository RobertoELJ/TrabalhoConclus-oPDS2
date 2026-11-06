#include "Vendedor.hpp"
#include <stdexcept>

Vendedor::Vendedor(const std::string& nome, const std::string& id, double percentualComissao)
    : nome_(nome), id_(id), percentualComissao_(percentualComissao) {
        if (nome.empty() || id.empty()) {
            throw std::invalid_argument("Nome ou ID invalido");
        }

        if (percentualComissao < 0 || percentualComissao > 100) {
            throw std::invalid_argument("Percentual de comissao invalido");
        }
    }

std::string Vendedor::getNome() const {
    return nome_;
}

std::string Vendedor::getId() const {
    return id_;
}

double Vendedor::getPercentualComissao() const {
    return percentualComissao_;
}

bool Vendedor::cadastrarVeiculo(CadastroVeiculos& cadastro, const Veiculo& veiculo) {
    return cadastro.cadastrarVeiculo(veiculo);
}

const Veiculo* Vendedor::consultarVeiculo(const CadastroVeiculos& cadastro, const std::string& placa) const {
    return cadastro.buscarVeiculo(placa);
}

bool Vendedor::atualizarVeiculo(CadastroVeiculos& cadastro, const std::string& placa, const Veiculo& novosDados) {
    return cadastro.atualizarVeiculo(placa, novosDados);
}

double Vendedor::calcularComissao(double valorVenda) const {
    if (valorVenda < 0) {
        throw std::invalid_argument("Valor de venda invalido");
    }
    return (valorVenda * percentualComissao_) / 100.0;
}