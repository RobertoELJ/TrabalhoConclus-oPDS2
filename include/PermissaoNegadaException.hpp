#ifndef PERMISSAO_NEGADA_EXCEPTION_HPP
#define PERMISSAO_NEGADA_EXCEPTION_HPP

#include <stdexcept>
#include <string>

/**
 * @file PermissaoNegadaException.hpp
 * @brief Erro lançado quando uma operação é recusada por falta de autorização.
 */

/**
 * @brief Avisa que uma operação foi recusada por falta de autorização.
 *
 * Usada quando um desconto passa do limite permitido e não há aprovação do
 * gerente. Quem chama (o Caixa) captura este erro e mostra a mensagem sem
 * fechar o programa.
 */
class PermissaoNegadaException : public std::runtime_error {
public:
    /**
     * @brief Cria o erro com uma mensagem clara para o usuário.
     * @param mensagem Explica qual operação foi recusada e por quê.
     */
    explicit PermissaoNegadaException(const std::string& mensagem);
};

#endif
