#include "Boleto.hpp"

#include <cmath>
#include <sstream>
#include "PagamentoInvalidoException.hpp"

namespace {
const double TOLERANCIA = 0.005;
}

Boleto::Boleto(int diasParaVencimento, double valorPago)
    : diasParaVencimento_(diasParaVencimento), valorPago_(valorPago) {
    if (diasParaVencimento <= 0) {
        throw PagamentoInvalidoException("O prazo do boleto deve ser maior que zero dias.");
    }
    if (valorPago < 0.0) {
        throw PagamentoInvalidoException("O valor pago nao pode ser negativo.");
    }
}

double Boleto::calcularValorFinal(double precoBase) const {
    if (precoBase < 0.0) {
        throw PagamentoInvalidoException("O preco base nao pode ser negativo.");
    }
    return precoBase;
}

std::string Boleto::descricao() const {
    std::ostringstream texto;
    texto << "Boleto (vencimento em " << diasParaVencimento_ << " dias)";
    return texto.str();
}

void Boleto::validarPagamento(double valorFinal) const {
    if (std::fabs(valorPago_ - valorFinal) > TOLERANCIA) {
        throw PagamentoInvalidoException("O valor pago do boleto deve ser igual ao total da venda.");
    }
}

int Boleto::getDiasParaVencimento() const {
    return diasParaVencimento_;
}

double Boleto::getValorPago() const {
    return valorPago_;
}
