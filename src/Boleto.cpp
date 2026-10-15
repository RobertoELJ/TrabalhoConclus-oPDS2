#include "Boleto.hpp"

#include <sstream>
#include "PagamentoInvalidoException.hpp"

const int Boleto::MAX_PARCELAS;

Boleto::Boleto(int numeroParcelas, int diasParaVencimento)
    : numeroParcelas_(numeroParcelas), diasParaVencimento_(diasParaVencimento) {
    if (numeroParcelas < 1 || numeroParcelas > MAX_PARCELAS) {
        throw PagamentoInvalidoException("O numero de parcelas deve ser de 1 ate 32.");
    }
    if (diasParaVencimento <= 0) {
        throw PagamentoInvalidoException("O prazo do boleto deve ser maior que zero dias.");
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
    texto << "Boleto em " << numeroParcelas_ << "x (primeiro vencimento em "
          << diasParaVencimento_ << " dias)";
    return texto.str();
}

void Boleto::validarPagamento(double) const {}

double Boleto::valorDaParcela(double precoBase) const {
    return calcularValorFinal(precoBase) / numeroParcelas_;
}

int Boleto::getNumeroParcelas() const {
    return numeroParcelas_;
}

int Boleto::getDiasParaVencimento() const {
    return diasParaVencimento_;
}
