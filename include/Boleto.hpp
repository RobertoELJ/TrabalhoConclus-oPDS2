#ifndef BOLETO_HPP
#define BOLETO_HPP

#include "FormaPagamento.hpp"

/**
 * @file Boleto.hpp
 * @brief Pagamento por boleto bancário, com vencimento e valor exato.
 */

/**
 * @brief Pagamento por boleto.
 *
 * Não tem desconto nem juros e o valor pago precisa ser igual ao total, como
 * no PIX. A diferença é que o boleto tem um prazo de vencimento em dias.
 */
class Boleto : public FormaPagamento {
public:
    /**
     * @brief Cria um pagamento por boleto.
     * @param diasParaVencimento Prazo em dias até o boleto vencer.
     * @param valorPago Quanto foi pago na compensação do boleto.
     * @throws PagamentoInvalidoException se os dias para vencimento não forem
     *         maiores que zero ou se o valor pago for negativo.
     */
    Boleto(int diasParaVencimento, double valorPago);

    /** @brief Devolve o próprio preço base, pois o boleto não altera o valor. */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto como "Boleto (vencimento em 3 dias)". */
    std::string descricao() const override;

    /**
     * @brief Confere se o valor pago é exatamente o valor final.
     * @throws PagamentoInvalidoException se o valor pago for diferente do total.
     */
    void validarPagamento(double valorFinal) const override;

    /** @brief Prazo em dias até o vencimento. */
    int getDiasParaVencimento() const;

    /** @brief Valor pago na compensação do boleto. */
    double getValorPago() const;

private:
    int diasParaVencimento_;
    double valorPago_;
};

#endif
