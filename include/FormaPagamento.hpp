#ifndef FORMA_PAGAMENTO_HPP
#define FORMA_PAGAMENTO_HPP

#include <string>

/**
 * @file FormaPagamento.hpp
 * @brief Contrato comum a todas as formas de pagamento da loja.
 */

/**
 * @brief Classe abstrata que representa uma forma de pagamento.
 *
 * Não existe "pagamento genérico": cada subclasse (Dinheiro, Cartao, Pix)
 * decide como calcular o valor final e como validar o pagamento. A Venda usa
 * apenas esta interface, sem saber qual subclasse recebeu (polimorfismo).
 * Para criar uma forma nova de pagamento basta criar uma nova subclasse.
 */
class FormaPagamento {
public:
    /** @brief Destrutor virtual, para apagar corretamente pela classe base. */
    virtual ~FormaPagamento() = default;

    /**
     * @brief Calcula quanto o cliente vai pagar no total.
     * @param precoBase Preço dos itens, sem desconto nem juros.
     * @return Valor final a pagar, já com desconto ou juros desta forma de pagamento.
     */
    virtual double calcularValorFinal(double precoBase) const = 0;

    /**
     * @brief Descreve o pagamento para mostrar ao usuário.
     * @return Texto como "Dinheiro (5% de desconto)" ou "Cartão em 3x".
     */
    virtual std::string descricao() const = 0;

    /**
     * @brief Confere se o pagamento cobre o valor final.
     * @param valorFinal Valor que precisa ser pago.
     * @throws PagamentoInvalidoException se o valor pago não cobre o total.
     */
    virtual void validarPagamento(double valorFinal) const = 0;

    /**
     * @brief Calcula o troco a devolver ao cliente.
     * @param valorFinal Valor que precisava ser pago.
     * @return Troco. Por padrão é zero; só o Dinheiro devolve troco.
     */
    virtual double calcularTroco(double valorFinal) const;
};

#endif
