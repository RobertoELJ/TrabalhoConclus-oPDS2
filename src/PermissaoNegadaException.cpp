#include "PermissaoNegadaException.hpp"

PermissaoNegadaException::PermissaoNegadaException(const std::string& mensagem)
    : std::runtime_error(mensagem) {}
