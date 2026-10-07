#include "Pix.hpp"

#include <cmath>
#include "PagamentoInvalidoException.hpp"

namespace {
const double TOLERANCIA = 0.005;
}

Pix::Pix(double valorPago) : valorPago_(valorPago) {
    if (valorPago < 0.0) {
        throw PagamentoInvalidoException("O valor pago nao pode ser negativo.");
    }
}

double Pix::calcularValorFinal(double precoBase) const {
    if (precoBase < 0.0) {
        throw PagamentoInvalidoException("O preco base nao pode ser negativo.");
    }
    return precoBase;
}

std::string Pix::descricao() const {
    return "PIX";
}

void Pix::validarPagamento(double valorFinal) const {
    if (std::fabs(valorPago_ - valorFinal) > TOLERANCIA) {
        throw PagamentoInvalidoException("O valor do PIX deve ser igual ao total da venda.");
    }
}

double Pix::getValorPago() const {
    return valorPago_;
}
