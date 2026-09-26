#ifndef DINHEIRO_HPP
#define DINHEIRO_HPP

#include "FormaPagamento.hpp"

/**
 * @file Dinheiro.hpp
 * @brief Pagamento à vista em dinheiro, com desconto e troco.
 */

/**
 * @brief Pagamento em dinheiro.
 *
 * Aplica um desconto à vista sobre o preço e devolve troco quando o cliente
 * entrega mais do que o valor final.
 */
class Dinheiro : public FormaPagamento {
public:
    /**
     * @brief Cria um pagamento em dinheiro.
     * @param percentualDesconto Desconto à vista, de 0 a 100 (ex.: 5 significa 5%).
     * @param valorPago Quanto o cliente entregou ao caixa.
     * @throws PagamentoInvalidoException se o desconto estiver fora de 0 a 100
     *         ou se o valor pago for negativo.
     */
    Dinheiro(double percentualDesconto, double valorPago);

    /** @brief Preço base menos o desconto à vista. */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto como "Dinheiro (5% de desconto)". */
    std::string descricao() const override;

    /**
     * @brief Confere se o valor entregue é igual ou maior que o valor final.
     * @throws PagamentoInvalidoException se o valor pago for menor que o total.
     */
    void validarPagamento(double valorFinal) const override;

    /** @brief Diferença entre o valor pago e o valor final. */
    double calcularTroco(double valorFinal) const override;

    /** @brief Percentual de desconto à vista. */
    double getPercentualDesconto() const;

    /** @brief Valor que o cliente entregou. */
    double getValorPago() const;

private:
    double percentualDesconto_;
    double valorPago_;
};

#endif
