#include "Estoque.hpp"

#include <climits>
#include <stdexcept>
#include <utility>

Estoque::Estoque() {}

const Estoque::Produto& Estoque::obterProduto(int id) const {
    auto it = produtos_.find(id);
    if (it == produtos_.end()) {
        throw std::out_of_range("Produto nao encontrado no estoque.");
    }
    return it->second;
}

void Estoque::adicionarProduto(int id, const std::string& descricao, int quantidade) {
    if (id <= 0) {
        throw std::invalid_argument("O ID do produto deve ser maior que zero.");
    }
    if (descricao.empty()) {
        throw std::invalid_argument("A descricao do produto nao pode ser vazia.");
    }
    if (descricao.find_first_of(";\r\n") != std::string::npos) {
        throw std::invalid_argument("A descricao nao pode conter ';' nem quebra de linha.");
    }
    if (quantidade <= 0) {
        throw std::invalid_argument("A quantidade deve ser maior que zero.");
    }

    auto it = produtos_.find(id);
    
    // se for novo, ja insere direto
    if (it == produtos_.end()) {
        produtos_[id] = {descricao, quantidade};
        return;
    }

    // se ja tem, confere o nome pra nao sobrescrever errado
    if (it->second.descricao != descricao) {
        throw std::invalid_argument("Ja existe um produto com esse ID e outra descricao.");
    }
    
    // segura o overflow do c++ pra nao crashar o int
    if (it->second.quantidade > INT_MAX - quantidade) {
        throw std::overflow_error("A quantidade em estoque ultrapassaria o limite permitido.");
    }
    it->second.quantidade += quantidade;
}

int Estoque::buscarProdutoPorId(int id) const {
    return obterProduto(id).quantidade;
}

std::string Estoque::getDescricaoProduto(int id) const {
    return obterProduto(id).descricao;
}

void Estoque::darBaixaQuantidade(int id, int quantidadeComprada) {
    if (quantidadeComprada <= 0) {
        throw std::invalid_argument("A quantidade comprada deve ser maior que zero.");
    }
    
    auto it = produtos_.find(id);
    if (it == produtos_.end()) {
        throw std::out_of_range("Produto nao encontrado no estoque.");
    }
    
    if (quantidadeComprada > it->second.quantidade) {
        throw std::runtime_error("Estoque insuficiente para essa quantidade.");
    }
    it->second.quantidade -= quantidadeComprada;
}

bool Estoque::alertarProdutoEsgotado(int id) const {
    return obterProduto(id).quantidade == 0;
}

long long Estoque::getTotalItens() const {
    long long total = 0;
    // iterando com auto e for-range em vez de iterador gigante
    for (const auto& par : produtos_) {
        total += par.second.quantidade;
    }
    return total;
}

std::vector<int> Estoque::listarIds() const {
    std::vector<int> ids;
    for (const auto& par : produtos_) {
        ids.push_back(par.first);
    }
    return ids;
}