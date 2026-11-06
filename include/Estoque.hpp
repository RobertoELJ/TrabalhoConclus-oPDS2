#ifndef ESTOQUE_HPP
#define ESTOQUE_HPP

#include <map>
#include <string>
#include <vector>

/**
 * @brief classe responsável por gerenciar o estoque de produtos
 */
class Estoque {
private:
    struct Produto {
        std::string descricao;
        int quantidade;
    };

    std::map<int, Produto> produtos_;

    const Produto& obterProduto(int id) const;

public:
    Estoque();

    /**
     * @brief 
     * @param id ID do produto, deve ser > 0
     * @param descricao Nome do produto 
     * @param quantidade Quantidade a adicionar
     */
    void adicionarProduto(int id, const std::string& descricao, int quantidade);

    /**
     * @brief 
     * @param id ID do produto
     * @return Quantidade atual no estoque
     */
    int buscarProdutoPorId(int id) const;

    /**
     * @brief 
     * @param id ID do produto
     */
    std::string getDescricaoProduto(int id) const;

    /**
     * @brief 
     * @param id ID do produto
     * @param qtd Quantidade vendida 
     */
    void darBaixaQuantidade(int id, int qtd);

    /**
     * @brief 
     * @param id ID do produto
     * @param qtd Quantidade devolvida
     */
    void devolverQuantidade(int id, int qtd);

    // vai verificar se o estoque do produto zerou
    bool alertarProdutoEsgotado(int id) const;

    long long getTotalItens() const;

    std::vector<int> listarIds() const;
};

#endif