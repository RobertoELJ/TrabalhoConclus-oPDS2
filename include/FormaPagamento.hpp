#pragma once

#include <string>

/** @brief Classe abstrata com o que toda forma de pagamento sabe fazer; cada subclasse decide como. */
class FormaPagamento {
public:
    virtual ~FormaPagamento() = default;

    /** @brief Calcula o valor final a pagar com o desconto ou os juros desta forma. Lança PagamentoInvalidoException se o preço base for negativo. */
    virtual double calcularValorFinal(double precoBase) const = 0;

    /** @brief Devolve um texto curto para mostrar ao usuário, como "Cartao em 3x". */
    virtual std::string descricao() const = 0;

    /** @brief Confere se o pagamento cobre o valor final. Lança PagamentoInvalidoException se não cobrir. */
    virtual void validarPagamento(double valorFinal) const = 0;

    /** @brief Calcula o troco. Por padrão é zero; só o Dinheiro devolve troco. */
    virtual double calcularTroco(double valorFinal) const;
};
