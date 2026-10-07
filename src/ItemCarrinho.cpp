#include "ItemCarrinho.hpp"

#include "PagamentoInvalidoException.hpp"

ItemCarrinho::ItemCarrinho(const std::string& descricao, double precoUnitario, int quantidade)
    : descricao_(descricao), precoUnitario_(precoUnitario), quantidade_(quantidade) {
    if (precoUnitario <= 0.0) {
        throw PagamentoInvalidoException("O preco do item deve ser maior que zero.");
    }
    if (quantidade <= 0) {
        throw PagamentoInvalidoException("A quantidade do item deve ser maior que zero.");
    }
}

double ItemCarrinho::calcularSubtotal() const {
    return precoUnitario_ * quantidade_;
}

std::string ItemCarrinho::getDescricao() const {
    return descricao_;
}

double ItemCarrinho::getPrecoUnitario() const {
    return precoUnitario_;
}

int ItemCarrinho::getQuantidade() const {
    return quantidade_;
}
