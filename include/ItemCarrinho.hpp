#pragma once

#include <string>

/** @brief Um item dentro do carrinho: descrição, preço de uma unidade e quantidade. */
class ItemCarrinho {
public:
    /** @brief Cria o item. Lança PagamentoInvalidoException se o preço ou a quantidade não forem maiores que zero. */
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
