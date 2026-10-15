#include "doctest.h"
#include "Pix.hpp"
#include "PagamentoInvalidoException.hpp"

TEST_CASE("Pix: nao altera o preco") {
    Pix p(300.0);
    CHECK(p.calcularValorFinal(300.0) == doctest::Approx(300.0));
}

TEST_CASE("Pix: valor exato e aceito") {
    Pix p(300.0);
    CHECK_NOTHROW(p.validarPagamento(300.0));
}

TEST_CASE("Pix: valor menor que o total lanca excecao") {
    Pix p(299.0);
    CHECK_THROWS_AS(p.validarPagamento(300.0), PagamentoInvalidoException);
}

TEST_CASE("Pix: valor maior que o total tambem lanca excecao") {
    Pix p(301.0);
    CHECK_THROWS_AS(p.validarPagamento(300.0), PagamentoInvalidoException);
}

TEST_CASE("Pix: nunca tem troco") {
    Pix p(300.0);
    CHECK(p.calcularTroco(300.0) == doctest::Approx(0.0));
}

TEST_CASE("Pix: valor pago negativo lanca excecao") {
    CHECK_THROWS_AS(Pix(-1.0), PagamentoInvalidoException);
}

TEST_CASE("Pix: getter devolve o valor pago") {
    Pix p(120.0);
    CHECK(p.getValorPago() == doctest::Approx(120.0));
}

TEST_CASE("Pix: descricao menciona PIX") {
    Pix p(120.0);
    CHECK(p.descricao().find("PIX") != std::string::npos);
}
