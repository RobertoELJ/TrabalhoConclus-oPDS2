#pragma once

#include "FormaPagamento.hpp"

/** @brief Pagamento por boleto em 1 a 32 parcelas, sem juros. Com 1 parcela é à vista. */
class Boleto : public FormaPagamento {
public:
    /** @brief Maior número de parcelas aceito. */
    static const int MAX_PARCELAS = 32;

    /** @brief Cria o pagamento com o número de parcelas e os dias até o primeiro vencimento. Lança PagamentoInvalidoException se as parcelas saírem de 1 até MAX_PARCELAS ou se o prazo não for maior que zero. */
    Boleto(int numeroParcelas, int diasParaVencimento);

    /** @brief Devolve o próprio preço base, pois o boleto não tem juros. */
    double calcularValorFinal(double precoBase) const override;

    /** @brief Texto como "Boleto em 3x (primeiro vencimento em 5 dias)". */
    std::string descricao() const override;

    /** @brief Os boletos são pagos depois, então esta validação sempre passa. */
    void validarPagamento(double valorFinal) const override;

    /** @brief Valor de cada boleto: preço dividido pelo número de parcelas. */
    double valorDaParcela(double precoBase) const;

    /** @brief Quantidade de parcelas. */
    int getNumeroParcelas() const;

    /** @brief Dias até o primeiro vencimento. */
    int getDiasParaVencimento() const;

private:
    int numeroParcelas_;
    int diasParaVencimento_;
};
