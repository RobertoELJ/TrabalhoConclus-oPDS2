#pragma once

#include <stdexcept>
#include <string>

/** @brief Erro de permissão: operação recusada por falta de aprovação do gerente. */
class PermissaoNegadaException : public std::runtime_error {
public:
    /** @brief Cria o erro com a mensagem que será mostrada ao usuário. */
    explicit PermissaoNegadaException(const std::string& mensagem);
};
