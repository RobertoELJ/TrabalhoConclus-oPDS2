#pragma once

#include <string>
#include "Carrinho.hpp"

class Cliente;
class Vendedor;
class Gerente;
class FormaPagamento;
class Estoque;

/** @brief Uma venda: liga cliente, vendedor, carrinho e forma de pagamento. Não conhece o Caixa. */
class Venda {
public:
    /** @brief Cria a venda com o carrinho já montado. */
    Venda(Cliente* cliente, Vendedor* vendedor, const Carrinho& carrinho);

    /** @brief Finaliza a venda: confere desconto e pagamento, tira os itens do estoque e calcula a comissão. Lança PagamentoInvalidoException se o pagamento não cobrir o total ou faltar item no estoque, e PermissaoNegadaException se o desconto passar do limite sem o gerente aprovar. */
    void finalizar(FormaPagamento* pagamento, Estoque& estoque, double percentualDesconto, Gerente* gerente);

    /** @brief Cancela uma venda concluída: devolve os itens ao estoque e zera a comissão. Lança PagamentoInvalidoException se a venda não estiver concluída ou já estiver cancelada. */
    void cancelar(Estoque& estoque);

    /** @brief Texto com os itens comprados e o valor total. */
    std::string gerarComprovante() const;

    /** @brief Venda convertida em uma linha de texto, para salvar em arquivo. */
    std::string toLinha() const;

    /** @brief Valor final da venda (zero antes de finalizar). */
    double getValorFinal() const;

    /** @brief Comissão do vendedor (zero antes de finalizar ou depois de cancelar). */
    double getComissao() const;

    /** @brief Diz se a venda já foi finalizada. */
    bool estaConcluida() const;

    /** @brief Diz se a venda foi cancelada. */
    bool estaCancelada() const;

private:
    Cliente* cliente_;
    Vendedor* vendedor_;
    Carrinho carrinho_;
    double valorFinal_;
    double comissao_;
    bool concluida_;
    bool cancelada_;
};
