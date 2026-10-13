#pragma once

#include "FormaPagamento.hpp"

/** @brief Pagamento financiado: entrada à vista e o resto em parcelas mensais com juros simples. */
class Financiamento : public FormaPagamento {
public:
    /** @brief Cria o financiamento com a entrada, o prazo em meses e a taxa ao mês (2 é 2%). Lança PagamentoInvalidoException se o prazo não for maior que zero ou a entrada ou a taxa forem negativas. */
    Financiamento(double entrada, int prazoMeses, double taxaMensal);

    /** @brief Entrada mais o saldo com juros simples (saldo x taxa x meses). Ex.: preço 1000, entrada 200, 10 meses a 2% dá 1160. Lança PagamentoInvalidoException se a entrada for maior que o preço. */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto como "Financiamento em 24x". */
    std::string descricao() const override;

    /** @brief O financiamento cobra o valor exato, então esta validação sempre passa. */
    void validarPagamento(double valorFinal) const override;

    /** @brief Valor de cada parcela: (valor final menos a entrada) dividido pelo prazo. */
    double valorDaParcela(double precoBase) const;

    /** @brief Valor da entrada. */
    double getEntrada() const;

    /** @brief Prazo em meses. */
    int getPrazoMeses() const;

    /** @brief Taxa de juros ao mês. */
    double getTaxaMensal() const;

private:
    double entrada_;
    int prazoMeses_;
    double taxaMensal_;
};
