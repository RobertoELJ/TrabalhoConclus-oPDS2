#pragma once

#include "FormaPagamento.hpp"

/** @brief Pagamento por boleto: sem desconto, sem juros e sem troco; o valor tem que ser exato. */
class Boleto : public FormaPagamento {
public:
    /** @brief Cria o pagamento com o prazo em dias e o valor pago. Lança PagamentoInvalidoException se o prazo não for maior que zero ou o valor for negativo. */
    Boleto(int diasParaVencimento, double valorPago);

    /** @brief Devolve o próprio preço base. */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto como "Boleto (vencimento em 3 dias)". */
    std::string descricao() const override;

    /** @brief Lança PagamentoInvalidoException se o valor pago for diferente do valor final. */
    void validarPagamento(double valorFinal) const override;

    /** @brief Prazo em dias até o vencimento. */
    int getDiasParaVencimento() const;

    /** @brief Valor pago na compensação. */
    double getValorPago() const;

private:
    int diasParaVencimento_;
    double valorPago_;
};
