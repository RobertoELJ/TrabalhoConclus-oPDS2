#ifndef ESTOQUE_HPP
#define ESTOQUE_HPP

#include <string>
//suzane ferreira 
/**
 @brief Classe responsável por gerenciar o estoque de produtos da loja.
 
Armazena e controla a quantidade dos itens, permitindo adicionar,
buscar e dar baixa em produtos, além de alertar sobre estoque esgotado.
 */
class Estoque {
private:
    /**
     @brief Quantidade total de itens atualmente no estoque.
     */
    int quantidadeTotalItens;

public:
    /**
     @brief Adiciona um novo produto à lista do estoque.
     */
    void adicionarProduto();

    /**
     @brief Busca um produto específico utilizando o seu identificador.
     @param id Identificador único (ID) numérico do produto procurado.
     */
    void buscarProdutoPorId(int id);

    /**
     @brief Diminui a quantidade de um produto no estoque após uma venda.
     @param id Identificador único (ID) numérico do produto vendido.
     @param quantidadeComprada Quantidade de itens que foram comprados e devem ser debitados.
     */
    void darBaixaQuantidade(int id, int quantidadeComprada);

    /**
     @brief Verifica se um produto está com a quantidade zerada (esgotado).
     @param id Identificador único (ID) do produto a ser verificado.
     @return true se o produto estiver esgotado, false caso ainda haja estoque.
     */
    bool alertarProdutoEsgotado(int id);
};

#endif