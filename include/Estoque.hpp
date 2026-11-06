#ifndef ESTOQUE_HPP
#define ESTOQUE_HPP

#include <map>
#include <string>
#include <vector>

/**
 * @brief Controla o estoque de produtos da loja.
 */
class Estoque {
private:
    /** @brief struct pra guardar os dados de cada produto */
    struct Produto {
        std::string descricao;
        int quantidade;
    };

    /** @brief mapa de produtos, indexado pelo id (ordem crescente) */
    std::map<int, Produto> produtos_;

    /**
     * @brief Busca um produto no mapa e garante q ele existe.
     * @param id id do produto.
     * @return referencia constante pro produto.
     * @throws std::out_of_range se nao achar o id.
     */
    const Produto& obterProduto(int id) const;

public:
    /** @brief Cria um estoque zerado. */
    Estoque();

    /**
     * @brief Adiciona um produto novo ou soma a quantidade se ja existir.
     * @param id id do produto (maior q zero).
     * @param descricao nome do produto (sem ; ou quebra de linha).
     * @param quantidade qtd a adicionar (maior q zero).
     * @throws std::invalid_argument se passar dado invalido ou a descricao nao bater.
     * @throws std::overflow_error se a quantidade estourar o limite do int.
     */
    void adicionarProduto(int id, const std::string& descricao, int quantidade);

    /**
     * @brief Pega a quantidade disponivel de um produto.
     * @param id id do produto.
     * @return quantidade atual no estoque.
     * @throws std::out_of_range se o produto nao existir.
     */
    int buscarProdutoPorId(int id) const;

    /**
     * @brief Retorna o nome do produto.
     * @param id id do produto.
     * @throws std::out_of_range se o produto nao existir.
     */
    std::string getDescricaoProduto(int id) const;

    /**
     * @brief Desconta a quantidade apos uma venda.
     * @param id id do produto.
     * @param quantidadeComprada quantidade vendida.
     * @throws std::invalid_argument se a qtd nao for positiva.
     * @throws std::out_of_range se o produto nao existir.
     * @throws std::runtime_error se tentar vender mais do q tem no saldo.
     */
    void darBaixaQuantidade(int id, int quantidadeComprada);

    /**
     * @brief Checa se o estoque de um item zerou.
     * @param id id do produto.
     * @return true se a quantidade for zero, false se ainda tem.
     * @throws std::out_of_range se o produto nao existir.
     */
    bool alertarProdutoEsgotado(int id) const;

    /** @brief Retorna o total de itens (soma das quantidades). */
    long long getTotalItens() const;

    /** @brief Retorna os ids dos produtos cadastrados (em ordem). */
    std::vector<int> listarIds() const;
};

#endif