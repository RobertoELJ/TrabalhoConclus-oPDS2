#ifndef VENDA_HPP
#define VENDA_HPP

#include <string>
#include "Carrinho.hpp"
#include "FormaPagamento.hpp"
#include "Estoque.hpp"

class Cliente;
class Vendedor;
class Gerente;

/**
 * @file Venda.hpp
 * @brief A venda: liga cliente, vendedor, carrinho e forma de pagamento.
 */

/**
 * @brief Representa uma venda, do carrinho até o comprovante.
 *
 * Não conhece o Caixa nem o menu: só sabe fazer a própria regra de negócio
 * e lançar exceções quando algo está errado. Quem chama é que decide o que
 * mostrar ao usuário.
 */
class Venda {
public:
    /**
     * @brief Cria uma venda com o carrinho já montado.
     * @param cliente Cliente da venda.
     * @param vendedor Vendedor responsável.
     * @param carrinho Itens já escolhidos.
     */
    Venda(Cliente* cliente, Vendedor* vendedor, const Carrinho& carrinho);

    /**
     * @brief Finaliza a venda com a forma de pagamento escolhida.
     * @param pagamento Forma de pagamento usada.
     * @param estoque Estoque de onde os itens são retirados.
     * @param percentualDesconto Desconto pedido sobre o total, de 0 a 100 (0 se não houver).
     * @param gerente Gerente que aprova o desconto, ou nullptr se não precisar de aprovação.
     * @throws PagamentoInvalidoException se o pagamento não cobrir o total ou faltar item no estoque.
     * @throws PermissaoNegadaException se o desconto passar do limite e não houver gerente aprovando.
     */
    void finalizar(FormaPagamento* pagamento, Estoque& estoque, double percentualDesconto, Gerente* gerente);

    /**
     * @brief Cancela uma venda já concluída: devolve os itens ao estoque e zera a comissão.
     * @param estoque Estoque para onde os itens voltam.
     * @throws PagamentoInvalidoException se a venda ainda não tiver sido concluída, ou já estiver cancelada.
     */
    void cancelar(Estoque& estoque);

    /** @brief Texto com os itens comprados e o valor total, para mostrar ao cliente. */
    std::string gerarComprovante() const;

    /** @brief Converte a venda em uma linha de texto, para salvar em arquivo. */
    std::string toLinha() const;

    /** @brief Valor final da venda (0 antes de finalizar). */
    double getValorFinal() const;

    /** @brief Comissão calculada para o vendedor (0 antes de finalizar ou após cancelar). */
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

#endif
