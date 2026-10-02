#ifndef PIX_HPP
#define PIX_HPP

#include "FormaPagamento.hpp"

/**
 * @file Pix.hpp
 * @brief Pagamento por PIX, sempre no valor exato.
 */

/**
 * @brief Pagamento por PIX.
 *
 * Não tem desconto nem juros e o valor transferido precisa ser igual ao total.
 * Por isso nunca gera troco.
 */
class Pix : public FormaPagamento {
public:
    /**
     * @brief Cria um pagamento por PIX.
     * @param valorPago Quanto o cliente transferiu.
     * @throws PagamentoInvalidoException se o valor pago for negativo.
     */
    explicit Pix(double valorPago);

    /** @brief Devolve o próprio preço base, pois o PIX não altera o valor. */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto "PIX". */
    std::string descricao() const override;

    /**
     * @brief Confere se o valor transferido é exatamente o valor final.
     * @throws PagamentoInvalidoException se o valor pago for diferente do total.
     */
    void validarPagamento(double valorFinal) const override;

    /** @brief Valor que o cliente transferiu. */
    double getValorPago() const;

private:
    double valorPago_;
};

#endif
