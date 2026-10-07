#include "Financiamento.hpp"

#include <sstream>
#include "PagamentoInvalidoException.hpp"

Financiamento::Financiamento(double entrada, int prazoMeses, double taxaMensal)
    : entrada_(entrada), prazoMeses_(prazoMeses), taxaMensal_(taxaMensal) {
    if (prazoMeses <= 0) {
        throw PagamentoInvalidoException("O prazo do financiamento deve ser maior que zero meses.");
    }
    if (entrada < 0.0) {
        throw PagamentoInvalidoException("A entrada nao pode ser negativa.");
    }
    if (taxaMensal < 0.0) {
        throw PagamentoInvalidoException("A taxa mensal nao pode ser negativa.");
    }
}

double Financiamento::calcularValorFinal(double precoBase) const {
    if (precoBase < 0.0) {
        throw PagamentoInvalidoException("O preco base nao pode ser negativo.");
    }
    if (entrada_ > precoBase) {
        throw PagamentoInvalidoException("A entrada nao pode ser maior que o preco.");
    }
    const double saldo = precoBase - entrada_;
    return entrada_ + saldo * (1.0 + taxaMensal_ / 100.0 * prazoMeses_);
}

std::string Financiamento::descricao() const {
    std::ostringstream texto;
    texto << "Financiamento em " << prazoMeses_ << "x";
    return texto.str();
}

void Financiamento::validarPagamento(double) const {}

double Financiamento::valorDaParcela(double precoBase) const {
    return (calcularValorFinal(precoBase) - entrada_) / prazoMeses_;
}

double Financiamento::getEntrada() const {
    return entrada_;
}

int Financiamento::getPrazoMeses() const {
    return prazoMeses_;
}

double Financiamento::getTaxaMensal() const {
    return taxaMensal_;
}
