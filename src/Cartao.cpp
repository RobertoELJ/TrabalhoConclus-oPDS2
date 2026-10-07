#include "Cartao.hpp"

#include <sstream>
#include "PagamentoInvalidoException.hpp"

const int Cartao::MAX_PARCELAS;

Cartao::Cartao(int numeroParcelas, double taxaJuros)
    : numeroParcelas_(numeroParcelas), taxaJuros_(taxaJuros) {
    if (numeroParcelas < 1 || numeroParcelas > MAX_PARCELAS) {
        throw PagamentoInvalidoException("O numero de parcelas deve ser de 1 ate 12.");
    }
    if (taxaJuros < 0.0) {
        throw PagamentoInvalidoException("A taxa de juros nao pode ser negativa.");
    }
}

double Cartao::calcularValorFinal(double precoBase) const {
    if (precoBase < 0.0) {
        throw PagamentoInvalidoException("O preco base nao pode ser negativo.");
    }
    return precoBase * (1.0 + taxaJuros_ / 100.0);
}

std::string Cartao::descricao() const {
    std::ostringstream texto;
    texto << "Cartao em " << numeroParcelas_ << "x";
    return texto.str();
}

void Cartao::validarPagamento(double) const {}

double Cartao::valorDaParcela(double precoBase) const {
    return calcularValorFinal(precoBase) / numeroParcelas_;
}

int Cartao::getNumeroParcelas() const {
    return numeroParcelas_;
}

double Cartao::getTaxaJuros() const {
    return taxaJuros_;
}
