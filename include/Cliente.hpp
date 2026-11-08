#pragma once

#include <string>

/** @brief Cliente cadastrado na loja, identificado pelo CPF. */
class Cliente {
public:
    /** @brief Cria o cliente com nome, CPF e e-mail. */
    Cliente(const std::string& nome, const std::string& cpf, const std::string& email);

    /** @brief Nome do cliente. */
    std::string getNome() const;

    /** @brief CPF do cliente. */
    std::string getCpf() const;

    /** @brief E-mail do cliente. */
    std::string getEmail() const;

    /** @brief Troca o nome, por exemplo para corrigir erro de digitação. */
    void setNome(const std::string& novoNome);

    /** @brief Troca o e-mail cadastrado. */
    void setEmail(const std::string& novoEmail);

    /** @brief Troca o CPF cadastrado. */
    void setCPF(const std::string& novoCPF);

private:
    std::string nome_;
    std::string cpf_;
    std::string email_;
    int id_;
};
