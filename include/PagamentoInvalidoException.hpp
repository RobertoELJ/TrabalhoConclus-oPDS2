#pragma once

#include <stdexcept>
#include <string>

/** @brief Erro de pagamento: dados errados ou valor pago que não cobre o total. */
class PagamentoInvalidoException : public std::runtime_error {
public:
    /** @brief Cria o erro com a mensagem que será mostrada ao usuário. */
    explicit PagamentoInvalidoException(const std::string& mensagem);
};
