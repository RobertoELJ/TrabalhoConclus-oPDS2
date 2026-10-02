#ifndef CARTAO_HPP
#define CARTAO_HPP

#include "FormaPagamento.hpp"

/**
 * @file Cartao.hpp
 * @brief Pagamento parcelado no cartão, com juros.
 */

/**
 * @brief Pagamento no cartão.
 *
 * O cliente escolhe em quantas parcelas pagar. Os juros são um percentual
 * aplicado uma vez sobre o preço; sem juros, informe 0.
 */
class Cartao : public FormaPagamento {
public:
    /** @brief Maior número de parcelas aceito. */
    static const int MAX_PARCELAS = 12;

    /**
     * @brief Cria um pagamento no cartão.
     * @param numeroParcelas Quantidade de parcelas, de 1 até MAX_PARCELAS.
     * @param taxaJuros Juros sobre o preço, de 0 em diante (ex.: 5 significa 5%).
     * @throws PagamentoInvalidoException se as parcelas estiverem fora do limite
     *         ou se a taxa de juros for negativa.
     */
    Cartao(int numeroParcelas, double taxaJuros);

    /** @brief Preço base mais os juros. */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto como "Cartão em 3x". */
    std::string descricao() const override;

    /** @brief O cartão cobra o valor exato, então esta validação sempre passa. */
    void validarPagamento(double valorFinal) const override;

    /**
     * @brief Calcula o valor de cada parcela.
     * @param precoBase Preço dos itens, antes dos juros.
     * @return Valor final dividido pelo número de parcelas.
     */
    double valorDaParcela(double precoBase) const;

    /** @brief Quantidade de parcelas escolhida. */
    int getNumeroParcelas() const;

    /** @brief Percentual de juros aplicado. */
    double getTaxaJuros() const;

private:
    int numeroParcelas_;
    double taxaJuros_;
};

#endif
