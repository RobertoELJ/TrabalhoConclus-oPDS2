#ifndef GERENCIAMENTODECLIENTES_HPP
#define GERENCIAMENTODECLIENTES_HPP

#include <string>
#include <vector>
#include "Cliente.hpp"

class GerenciamentoDeClientes {
private:
    std::vector<Cliente> clientes_;

    bool validarEmail(const std::string& email) const;

    bool validarCPF(const std::string& CPF) const;

public:
    /**
     * @brief cadastrarCliente é um método que cadastra um novo cliente no sistema e valida o email e CPF do cliente antes de adicioná-lo ao sistema.
     * @param nome Nome do cliente a ser cadastrado.
     * @param email Email do cliente a ser validado e cadastrado.
     * @param cpf CPF do cliente a ser validado e cadastrado.
     * @throws std::invalid_argument Se o formato do email ou do CPF for inválido.
     */
    void cadastrarCliente(const std::string& nome, const std::string& email, const std::string& cpf);

    /**
     * @brief Retorna a quantidade total de clientes cadastrados, útil para substituir o antigo getIdCliente.
     * @return Número inteiro representando o total de clientes no vetor.
     */
    int getQuantidadeClientes() const;

    /**
     * @brief mostrarClientes é um método que imprime uma lista com todos os clientes cadastrados no sistema.
     */
    void mostrarClientes() const;
    
    /**
     * @brief alterarNomeCliente é um método que altera o nome de um cliente existente.
     * @param id Identificador do cliente (posição + 1).
     * @param novoNome Novo nome que substituirá o atual.
     * @throws std::out_of_range Se o ID informado não corresponder a nenhum cliente existente.
     */
    void alterarNomeCliente(int id, const std::string& novoNome);
    
    /**
     * @brief alterarEmailCliente é um método que altera o email de um cliente existente.
     * @param id Identificador do cliente (posição + 1).
     * @param novoEmail Novo email que substituirá o atual.
     * @throws std::out_of_range Se o ID informado não existir.
     * @throws std::invalid_argument Se o novo email não tiver um formato válido.
     */
    void alterarEmailCliente(int id, const std::string& novoEmail);
};

#endif