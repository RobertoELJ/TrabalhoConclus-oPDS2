#ifndef ITEM_CARRINHO_HPP
#define ITEM_CARRINHO_HPP

#include <string>

/**
 * @file ItemCarrinho.hpp
 * @brief Um item dentro do carrinho de compras (veículo ou produto).
 */

/**
 * @brief Representa um item já colocado no carrinho.
 *
 * Guarda só o necessário para a venda (descrição, preço unitário e
 * quantidade), sem depender diretamente de Veiculo ou Produto. Assim o
 * Carrinho não precisa conhecer as duas classes por dentro; quem monta o
 * ItemCarrinho é quem sabe se veio de um veículo ou de um produto.
 */
class ItemCarrinho {
public:
    /**
     * @brief Cria um item do carrinho.
     * @param descricao Texto para mostrar ao usuário (ex.: "Civic 2024").
     * @param precoUnitario Preço de uma unidade do item.
     * @param quantidade Quantidade escolhida.
     * @throws PagamentoInvalidoException se o preço ou a quantidade não forem maiores que zero.
     */
    ItemCarrinho(const std::string& descricao, double precoUnitario, int quantidade);

    /** @brief Preço unitário vezes a quantidade. */
    double calcularSubtotal() const;

    /** @brief Texto para mostrar ao usuário. */
    std::string getDescricao() const;

    /** @brief Preço de uma unidade. */
    double getPrecoUnitario() const;

    /** @brief Quantidade escolhida. */
    int getQuantidade() const;

private:
    std::string descricao_;
    double precoUnitario_;
    int quantidade_;
};

#endif
