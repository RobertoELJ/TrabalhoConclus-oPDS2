#include "doctest.h"
#include "Boleto.hpp"
#include "PagamentoInvalidoException.hpp"

TEST_CASE("Boleto: nao altera o preco") {
    Boleto b(3, 800.0);
    CHECK(b.calcularValorFinal(800.0) == doctest::Approx(800.0));
}

TEST_CASE("Boleto: valor exato e aceito") {
    Boleto b(3, 800.0);
    CHECK_NOTHROW(b.validarPagamento(800.0));
}

TEST_CASE("Boleto: valor diferente do total lanca excecao") {
    Boleto b(3, 700.0);
    CHECK_THROWS_AS(b.validarPagamento(800.0), PagamentoInvalidoException);
}

TEST_CASE("Boleto: nunca tem troco") {
    Boleto b(3, 800.0);
    CHECK(b.calcularTroco(800.0) == doctest::Approx(0.0));
}

TEST_CASE("Boleto: zero dias para vencimento lanca excecao") {
    CHECK_THROWS_AS(Boleto(0, 100.0), PagamentoInvalidoException);
}

TEST_CASE("Boleto: dias negativos para vencimento lancam excecao") {
    CHECK_THROWS_AS(Boleto(-5, 100.0), PagamentoInvalidoException);
}

TEST_CASE("Boleto: valor pago negativo lanca excecao") {
    CHECK_THROWS_AS(Boleto(3, -1.0), PagamentoInvalidoException);
}

TEST_CASE("Boleto: getters devolvem o que foi informado") {
    Boleto b(7, 450.0);
    CHECK(b.getDiasParaVencimento() == 7);
    CHECK(b.getValorPago() == doctest::Approx(450.0));
}

TEST_CASE("Boleto: descricao menciona boleto e o prazo") {
    Boleto b(3, 800.0);
    CHECK(b.descricao().find("Boleto") != std::string::npos);
    CHECK(b.descricao().find("3") != std::string::npos);
}
