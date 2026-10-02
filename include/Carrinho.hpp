#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <vector>
#include "ItemCarrinho.hpp"
#include "Veiculo.hpp"

/**
 * @file Carrinho.hpp
 * @brief Carrinho de compras, com os itens escolhidos antes de fechar a venda.
 */

/**
 * @brief Guarda os itens (veículos e produtos) escolhidos para uma venda.
 *
 * A Venda só lê o total e a lista de itens daqui; quem adiciona e remove
 * itens é o Caixa, durante o atendimento.
 */
class Carrinho {
public:
    /** @brief Cria um carrinho vazio. */
    Carrinho();

    /**
     * @brief Adiciona um veículo ao carrinho.
     * @param veiculo Veículo escolhido (o preço vem de veiculo.getPreco()).
     * @param quantidade Quantidade de unidades, normalmente 1 para veículo.
     * @throws PagamentoInvalidoException se a quantidade não for maior que zero.
     */
    void adicionarVeiculo(const Veiculo& veiculo, int quantidade = 1);

    // Quando a classe Produto existir (área de Veículos/Estoque), entra aqui
    // um adicionarProduto(const Produto& produto, int quantidade), do mesmo jeito.

    /**
     * @brief Remove um item do carrinho pela posição.
     * @param indice Posição do item na lista (começando em 0).
     * @throws std::out_of_range se o índice não existir.
     */
    void removerItem(std::size_t indice);

    /** @brief Soma o subtotal de todos os itens. */
    double calcularTotal() const;

    /** @brief Esvazia o carrinho. Chamado depois que a venda é concluída. */
    void esvaziar();

    /** @brief Diz se o carrinho não tem nenhum item. */
    bool estaVazio() const;

    /** @brief Lista dos itens escolhidos. */
    const std::vector<ItemCarrinho>& getItens() const;

private:
    std::vector<ItemCarrinho> itens_;
};

#endif
