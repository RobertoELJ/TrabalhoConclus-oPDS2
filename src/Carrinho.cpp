#include "Carrinho.hpp"

#include <stdexcept>

Carrinho::Carrinho() {}

void Carrinho::adicionarVeiculo(const Veiculo& veiculo, int quantidade) {
    itens_.push_back(ItemCarrinho(veiculo.getMarca() + " " + veiculo.getModelo(),
                                  veiculo.getPreco(), quantidade));
}

void Carrinho::removerItem(std::size_t indice) {
    if (indice >= itens_.size()) {
        throw std::out_of_range("Nao existe item nessa posicao do carrinho.");
    }
    itens_.erase(itens_.begin() + indice);
}

double Carrinho::calcularTotal() const {
    double total = 0.0;
    for (const ItemCarrinho& item : itens_) {
        total += item.calcularSubtotal();
    }
    return total;
}

void Carrinho::esvaziar() {
    itens_.clear();
}

bool Carrinho::estaVazio() const {
    return itens_.empty();
}

const std::vector<ItemCarrinho>& Carrinho::getItens() const {
    return itens_;
}
