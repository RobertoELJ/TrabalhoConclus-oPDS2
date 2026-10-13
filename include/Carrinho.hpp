#pragma once

#include <vector>
#include "ItemCarrinho.hpp"

class Veiculo;

/** @brief Carrinho de compras: guarda os itens escolhidos antes de fechar a venda. */
class Carrinho {
public:
    /** @brief Cria um carrinho vazio. */
    Carrinho();

    /** @brief Adiciona um veículo; a descrição do item fica "marca modelo". Lança PagamentoInvalidoException se a quantidade não for maior que zero. */
    void adicionarVeiculo(const Veiculo& veiculo, int quantidade = 1);

    /** @brief Remove o item da posição indicada (começa em 0). Lança std::out_of_range se não existir. */
    void removerItem(std::size_t indice);

    /** @brief Soma o subtotal de todos os itens. */
    double calcularTotal() const;

    /** @brief Esvazia o carrinho, depois que a venda é concluída. */
    void esvaziar();

    /** @brief Diz se o carrinho não tem nenhum item. */
    bool estaVazio() const;

    /** @brief Lista dos itens escolhidos. */
    const std::vector<ItemCarrinho>& getItens() const;

private:
    std::vector<ItemCarrinho> itens_;
};
