#ifndef GERENCIAMENTODECLIENTES_HPP
#define GERENCIAMENTODECLIENTES_HPP

#include <string>
#include <vector>
#include "Cliente.hpp"

/**
 * @brief Classe responsável por gerenciar os clientes cadastrados no sistema.
 */
class GerenciamentoDeClientes {
private:
    /** @brief Vetor que armazena todos os clientes cadastrados. */
    std::vector<Cliente> clientes_;

    /**
     * @brief Valida o formato do e-mail (apenas um @, ponto após @ com caractere intermediário, sem espaços).
     * @param email E-mail a ser validado.
     * @return true se o e-mail for válido, false caso contrário.
     */
    bool validarEmail(const std::string& email) const;

    /**
     * @brief Valida o formato do CPF (exatamente 11 dígitos numéricos).
     * @param cpf CPF a ser validado.
     * @return true se o CPF for válido, false caso contrário.
     */
    bool validarCPF(const std::string& cpf) const;

    /**
     * @brief Valida se um ID corresponde a uma posição existente no vetor.
     * @param id Identificador do cliente.
     * @throws std::out_of_range Se o ID for menor que 1 ou maior que o tamanho da lista.
     */
    void validarId(int id) const;

public:
    /**
     * @brief Cadastra um novo cliente no sistema.
     * @param nome Nome do cliente.
     * @param email Email do cliente.
     * @param cpf CPF do cliente.
     * @throws std::invalid_argument Se nome, email ou cpf forem inválidos, ou se o CPF já existir.
     */
    void cadastrarCliente(const std::string& nome, const std::string& email, const std::string& cpf);

    /**
     * @brief Retorna a quantidade total de clientes cadastrados.
     * @return Número inteiro com o total de clientes.
     */
    int getQuantidadeClientes() const;

    /**
     * @brief Imprime no terminal a lista com todos os clientes cadastrados.
     */
    void mostrarClientes() const;
    
    /**
     * @brief Altera o nome de um cliente existente.
     * @param id Identificador do cliente (posição + 1).
     * @param novoNome Novo nome que substituirá o atual.
     * @throws std::out_of_range Se o ID informado for inválido.
     * @throws std::invalid_argument Se o novo nome for vazio.
     */
    void alterarNomeCliente(int id, const std::string& novoNome);
    
    /**
     * @brief Altera o email de um cliente existente.
     * @param id Identificador do cliente (posição + 1).
     * @param novoEmail Novo email que substituirá o atual.
     * @throws std::out_of_range Se o ID informado for inválido.
     * @throws std::invalid_argument Se o novo email for inválido.
     */
    void alterarEmailCliente(int id, const std::string& novoEmail);
};

#endif