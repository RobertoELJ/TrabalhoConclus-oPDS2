#ifndef FINANCIAMENTO_HPP
#define FINANCIAMENTO_HPP

#include "FormaPagamento.hpp"

/**
 * @file Financiamento.hpp
 * @brief Pagamento financiado, com entrada, prazo e taxa mensal.
 */

/**
 * @brief Pagamento financiado (extra).
 *
 * O cliente dá uma entrada e paga o restante em parcelas mensais, com juros
 * sobre o saldo financiado (o preço menos a entrada).
 */
class Financiamento : public FormaPagamento {
public:
    /**
     * @brief Cria um financiamento.
     * @param entrada Valor pago à vista, antes de financiar o restante.
     * @param prazoMeses Quantidade de meses para pagar o saldo financiado.
     * @param taxaMensal Juros ao mês sobre o saldo, de 0 em diante (ex.: 2 significa 2% ao mês).
     * @throws PagamentoInvalidoException se o prazo não for maior que zero
     *         ou se a entrada ou a taxa forem negativas.
     */
    Financiamento(double entrada, int prazoMeses, double taxaMensal);

    /**
     * @brief Calcula o valor final: entrada mais o saldo financiado com juros.
     * @throws PagamentoInvalidoException se a entrada for maior que o preço base.
     */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto como "Financiamento em 24x". */
    std::string descricao() const override;

    /** @brief O financiamento cobre o valor exato, então esta validação sempre passa. */
    void validarPagamento(double valorFinal) const override;

    /**
     * @brief Calcula o valor de cada parcela mensal.
     * @param precoBase Preço dos itens, antes da entrada e dos juros.
     * @return Valor final menos a entrada, dividido pelo prazo em meses.
     */
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

#endif
