#include <stdexcept>
#include <string>
#include "doctest.h"
#include "PagamentoInvalidoException.hpp"
#include "PermissaoNegadaException.hpp"

TEST_CASE("PagamentoInvalidoException: guarda a mensagem informada") {
    PagamentoInvalidoException e("valor invalido");
    CHECK(std::string(e.what()) == "valor invalido");
}

TEST_CASE("PagamentoInvalidoException: pode ser capturada como excecao padrao") {
    CHECK_THROWS_AS(throw PagamentoInvalidoException("erro"), std::runtime_error);
    CHECK_THROWS_AS(throw PagamentoInvalidoException("erro"), std::exception);
}

TEST_CASE("PermissaoNegadaException: guarda a mensagem informada") {
    PermissaoNegadaException e("desconto sem aprovacao");
    CHECK(std::string(e.what()) == "desconto sem aprovacao");
}

TEST_CASE("PermissaoNegadaException: pode ser capturada como excecao padrao") {
    CHECK_THROWS_AS(throw PermissaoNegadaException("erro"), std::runtime_error);
    CHECK_THROWS_AS(throw PermissaoNegadaException("erro"), std::exception);
}
