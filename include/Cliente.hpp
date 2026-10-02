#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>

/**
 * @file Cliente.hpp
 * @brief Cliente cadastrado na loja.
 */

/**
 * @brief Representa um cliente.
 *
 * Reescrito aqui porque a versão anterior guardava um std::vector<Cliente>
 * dentro da própria classe Cliente (um cliente contendo uma lista de
 * clientes) e não tinha nenhum atributo de identificação (nome, CPF,
 * e-mail), o que a Venda precisa para associar a venda a um cliente.
 */
class Cliente {
public:
    /**
     * @brief Cria um cliente.
     * @param nome Nome do cliente.
     * @param cpf CPF do cliente, usado para identificá-lo.
     * @param email E-mail do cliente.
     */
    Cliente(const std::string& nome, const std::string& cpf, const std::string& email);

    /** @brief Nome do cliente. */
    std::string getNome() const;

    /** @brief CPF do cliente. */
    std::string getCpf() const;

    /** @brief E-mail do cliente. */
    std::string getEmail() const;

    /** @brief Altera o nome, por exemplo para corrigir erro de digitação. */
    void alteraNome(const std::string& novoNome);

    /** @brief Altera o e-mail cadastrado. */
    void alteraEmail(const std::string& novoEmail);

    /** @brief Confere se o e-mail cadastrado tem um formato válido. */
    bool validaEmail() const;

    /** @brief Confere se o CPF cadastrado tem um formato válido. */
    bool validaCPF() const;

private:
    std::string nome_;
    std::string cpf_;
    std::string email_;
};

#endif
