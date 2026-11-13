#ifndef GERENCIAMENTODECLIENTES_HPP
#define GERENCIAMENTODECLIENTES_HPP

#include <string>
#include <vector>
#include <deque>
#include "Cliente.hpp"

/**
 * @brief Classe responsavel por gerenciar a colecao de clientes do sistema.
 */
class GerenciamentoDeVendedores;
class GerenciamentoDeClientes {
private:
    /** @brief vetor com todos os clientes cadastrados */
     std::deque<Cliente> clientes_;

    /**
     * @brief checa se o id passado realmente existe no vetor
     * @param id identificador numérico do cliente (baseado em 1)
     * @throws std::out_of_range se o id for menor que 1 ou maior que o tamanho do vetor
     */
    void validarId(int id) const;

public:
    // Construtor e Destrutor padrão
    GerenciamentoDeClientes() = default;
    ~GerenciamentoDeClientes();

    /**
     * @brief cadastra um cliente novo
     * @param nome nome do cliente
     * @param email email do cliente
     * @param cpf cpf do cliente
     * @throws std::invalid_argument se algum dado for invalido ou se o cpf ja existir
     */
    void cadastrarCliente(const std::string& nome, const std::string& email, const std::string& cpf);

    /**
     * @brief retorna o total de clientes cadastrados
     */
    int getQuantidadeClientes() const;

    /**
     * @brief printa todos os clientes na tela
     */
    void mostrarClientes() const;
    
    /**
     * @brief muda o nome do cliente. Delega a validacao para a classe Cliente.
     * @param id id do cliente (posicao do vetor + 1)
     * @param novoNome novo nome que vai ficar
     * @throws std::out_of_range se o id nao existir
     * @throws std::invalid_argument se o nome novo for invalido
     */
    void alterarNomeCliente(int id, const std::string& novoNome);
    
    /**
     * @brief muda o email do cliente. Delega a validacao para a classe Cliente.
     * @param id id do cliente (posicao do vetor + 1)
     * @param novoEmail novo email que vai ficar
     * @throws std::out_of_range se o id nao existir
     * @throws std::invalid_argument se o email novo for invalido
     */
    void alterarEmailCliente(int id, const std::string& novoEmail);

    /**
     * @brief transforma os clientes em strings (nome;cpf;email) pra salvar no txt
     */
    std::vector<std::string> paraLinhas() const;

    /**
     * @brief le o vetor de strings vindo do txt e cadastra 
     */
    void carregarDeLinhas(
    const std::vector<std::string>& linhas,
    const GerenciamentoDeVendedores& gerenciamentoVendedores
);

    /**
     * @brief remove um cliente do vetor
     * @param id id do cliente (posicao do vetor + 1)
     */
    void removerCliente(
    int id,
    const GerenciamentoDeVendedores& gerenciamentoVendedores
);

    /**
     * @brief busca um cliente pelo id
     * @param id id do cliente (posicao do vetor + 1)
     * @return ponteiro para o cliente encontrado
     */
    Cliente* buscarCliente(int id);


    /** @brief Busca um cliente pelo CPF. Retorna nullptr se nao encontrar. */
Cliente* buscarClientePorCpf(const std::string& cpf);

};

#endif