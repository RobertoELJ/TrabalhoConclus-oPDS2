#pragma once

#include "FormaPagamento.hpp"

/** @brief Pagamento parcelado no cartão, com juros aplicados uma vez sobre o preço. */
class Cartao : public FormaPagamento {
public:
    /** @brief Maior número de parcelas aceito. */
    static const int MAX_PARCELAS = 12;

    /** @brief Cria o pagamento com parcelas de 1 a MAX_PARCELAS e juros em percentual (5 é 5%). Lança PagamentoInvalidoException se as parcelas saírem do limite ou o juros for negativo. */
    Cartao(int numeroParcelas, double taxaJuros);

    /** @brief Preço base mais os juros. */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto como "Cartao em 3x". */
    std::string descricao() const override;

    /** @brief O cartão cobra o valor exato, então esta validação sempre passa. */
    void validarPagamento(double valorFinal) const override;

    /** @brief Valor de cada parcela: valor final dividido pelo número de parcelas. */
    double valorDaParcela(double precoBase) const;

    /** @brief Quantidade de parcelas. */
    int getNumeroParcelas() const;

    /** @brief Percentual de juros. */
    double getTaxaJuros() const;

private:
    int numeroParcelas_;
    double taxaJuros_;
};
