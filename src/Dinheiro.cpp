#include "Dinheiro.hpp"

#include <sstream>
#include "PagamentoInvalidoException.hpp"

namespace {
const double TOLERANCIA = 0.005;
}

Dinheiro::Dinheiro(double percentualDesconto, double valorPago)
    : percentualDesconto_(percentualDesconto), valorPago_(valorPago) {
    if (percentualDesconto < 0.0 || percentualDesconto > 100.0) {
        throw PagamentoInvalidoException("O desconto deve estar entre 0 e 100.");
    }
    if (valorPago < 0.0) {
        throw PagamentoInvalidoException("O valor pago nao pode ser negativo.");
    }
}

double Dinheiro::calcularValorFinal(double precoBase) const {
    if (precoBase < 0.0) {
        throw PagamentoInvalidoException("O preco base nao pode ser negativo.");
    }
    return precoBase * (1.0 - percentualDesconto_ / 100.0);
}

std::string Dinheiro::descricao() const {
    std::ostringstream texto;
    texto << "Dinheiro (" << percentualDesconto_ << "% de desconto)";
    return texto.str();
}

void Dinheiro::validarPagamento(double valorFinal) const {
    if (valorPago_ + TOLERANCIA < valorFinal) {
        throw PagamentoInvalidoException("O valor pago nao cobre o total da venda.");
    }
}

double Dinheiro::calcularTroco(double valorFinal) const {
    return valorPago_ - valorFinal;
}

double Dinheiro::getPercentualDesconto() const {
    return percentualDesconto_;
}

double Dinheiro::getValorPago() const {
    return valorPago_;
}
