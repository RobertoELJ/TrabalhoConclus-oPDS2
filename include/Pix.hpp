#pragma once

#include "FormaPagamento.hpp"

/** @brief Pagamento por PIX: sem desconto, sem juros e sem troco; o valor tem que ser exato. */
class Pix : public FormaPagamento {
public:
    /** @brief Cria o pagamento com o valor transferido. Lança PagamentoInvalidoException se for negativo. */
    explicit Pix(double valorPago);

    /** @brief Devolve o próprio preço base. */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto "PIX". */
    std::string descricao() const override;

    /** @brief Lança PagamentoInvalidoException se o valor transferido for diferente do valor final. */
    void validarPagamento(double valorFinal) const override;

    /** @brief Valor que o cliente transferiu. */
    double getValorPago() const;

private:
    double valorPago_;
};
