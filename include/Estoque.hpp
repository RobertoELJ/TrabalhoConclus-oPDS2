#ifndef ESTOQUE_HPP
#define ESTOQUE_HPP


class Estoque {

    //aqui é o conhecimento, os meus atributos/dados
    private: 
    int qtd_total_de_itens; 

    //aqui é a realização, as minhas ações/métodos
    public:
    void adicionarProduto();
    void buscarProdutoPorId(int id);
    void darBaixaQuantidade(int id, int quantidadeComprada);
    bool alertarProdutoEsgotado(int id);

    // Adicionados pelo Marco (Vendas e Pagamentos): a Venda precisa checar
    // se tem quantidade antes de vender, e devolver o item se a venda for cancelada.
    bool verificarDisponibilidade(int id, int quantidadeDesejada);
    void devolverQuantidade(int id, int quantidadeDevolvida);
};

#endif 