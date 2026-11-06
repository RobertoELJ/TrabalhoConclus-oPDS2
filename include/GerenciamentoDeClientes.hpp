#ifndef GERENCIAMENTODECLIENTES_HPP
#define GERENCIAMENTODECLIENTES_HPP

#include <string>
#include <vector>
#include "Cliente.hpp"

/**
 * @brief Classe responsavel por gerenciar os clientes do sistema.
 */
class GerenciamentoDeClientes {
private:
    /** @brief vetor com todos os clientes cadastrados */
    std::vector<Cliente> clientes_;

    /**
     * @brief valida se o email ta no formato certo (tem q ter @ e ponto, sem espaco)
     * @param email email pra validar
     * @return true se for valido, false se nao
     */
    bool validarEmail(const std::string& email) const;

    /**
     * @brief valida se o cpf tem exatamente 11 numeros
     * @param cpf cpf pra validar
     * @return true se o cpf for valido
     */
    bool validarCPF(const std::string& cpf) const;

    /**
     * @brief checa se o id passado realmente existe no vetor
     * @param id identificador do cliente
     * @throws std::out_of_range se o id for menor q 1 ou maior q o tamanho do vetor
     */
    void validarId(int id) const;

    /**
     * @brief checa se o nome nao ta vazio ou com caracteres zuados (tipo ; ou quebra de linha)
     * @param nome nome pra validar
     * @return true se o nome for de boa
     */
    bool nomeValido(const std::string& nome) const;

public:
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
     * @return inteiro com o tamanho do vetor de clientes
     */
    int getQuantidadeClientes() const;

    /**
     * @brief printa todos os clientes na tela
     */
    void mostrarClientes() const;
    
    /**
     * @brief muda o nome do cliente
     * @param id id do cliente (posicao do vetor + 1)
     * @param novoNome novo nome que vai ficar
     * @throws std::out_of_range se o id nao existir
     * @throws std::invalid_argument se o nome novo for vazio
     */
    void alterarNomeCliente(int id, const std::string& novoNome);
    
    /**
     * @brief muda o email do cliente
     * @param id id do cliente (posicao do vetor + 1)
     * @param novoEmail novo email que vai ficar
     * @throws std::out_of_range se o id nao existir
     * @throws std::invalid_argument se o email novo for invalido
     */
    void alterarEmailCliente(int id, const std::string& novoEmail);

    /**
     * @brief transforma os clientes em strings (nome;cpf;email) pra salvar no txt
     * @return vetor com as linhas formatadas
     */
    std::vector<std::string> paraLinhas() const;

    /**
     * @brief le o vetor de strings vindo do txt e cadastra a galera toda
     * @param linhas linhas lidas do txt
     * @throws std::invalid_argument se alguma linha tiver bugada (mostra o numero da linha no erro)
     */
    void carregarDeLinhas(const std::vector<std::string>& linhas);
};

#endif