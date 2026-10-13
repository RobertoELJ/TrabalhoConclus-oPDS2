#pragma once

#include "FormaPagamento.hpp"

/** @brief Pagamento em dinheiro: tem desconto à vista e devolve troco. */
class Dinheiro : public FormaPagamento {
public:
    /** @brief Cria o pagamento com desconto de 0 a 100 (5 é 5%) e o valor entregue. Lança PagamentoInvalidoException se o desconto sair de 0 a 100 ou o valor pago for negativo. */
    Dinheiro(double percentualDesconto, double valorPago);

    /** @brief Preço base menos o desconto à vista. */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto como "Dinheiro (5% de desconto)". */
    std::string descricao() const override;

    /** @brief Lança PagamentoInvalidoException se o valor entregue for menor que o valor final. */
    void validarPagamento(double valorFinal) const override;

    /** @brief Valor entregue menos o valor final. */
    double calcularTroco(double valorFinal) const override;

    /** @brief Percentual de desconto à vista. */
    double getPercentualDesconto() const;

    /** @brief Valor que o cliente entregou. */
    double getValorPago() const;

private:
    double percentualDesconto_;
    double valorPago_;
};
