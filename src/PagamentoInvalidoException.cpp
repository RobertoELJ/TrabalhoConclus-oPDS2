#include "PagamentoInvalidoException.hpp"

PagamentoInvalidoException::PagamentoInvalidoException(const std::string& mensagem)
    : std::runtime_error(mensagem) {}
