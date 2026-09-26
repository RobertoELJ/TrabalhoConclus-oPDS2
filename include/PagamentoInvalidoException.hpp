#ifndef PAGAMENTO_INVALIDO_EXCEPTION_HPP
#define PAGAMENTO_INVALIDO_EXCEPTION_HPP

#include <stdexcept>
#include <string>

/**
 * @file PagamentoInvalidoException.hpp
 * @brief Erro lançado quando os dados de um pagamento estão errados.
 */

/**
 * @brief Avisa que um pagamento é inválido.
 *
 * Usada para valores negativos, percentuais fora do limite, número de parcelas
 * inválido e também quando o valor pago não cobre o total da venda. Quem chama
 * (o Caixa) captura este erro e mostra a mensagem sem fechar o programa.
 */
class PagamentoInvalidoException : public std::runtime_error {
public:
    /**
     * @brief Cria o erro com uma mensagem clara para o usuário.
     * @param mensagem Explica o que está errado no pagamento.
     */
    explicit PagamentoInvalidoException(const std::string& mensagem);
};

#endif
