#include "doctest.h"
#include "Boleto.hpp"
#include "PagamentoInvalidoException.hpp"

TEST_CASE("Boleto: nao altera o preco") {
    Boleto b(3, 5);
    CHECK(b.calcularValorFinal(900.0) == doctest::Approx(900.0));
}

TEST_CASE("Boleto: cada parcela e o preco dividido pelas parcelas") {
    Boleto b(3, 5);
    CHECK(b.valorDaParcela(900.0) == doctest::Approx(300.0));
}

TEST_CASE("Boleto: com 1 parcela e a vista") {
    Boleto b(1, 5);
    CHECK(b.valorDaParcela(900.0) == doctest::Approx(900.0));
}

TEST_CASE("Boleto: aceita de 1 ate o maximo de parcelas") {
    CHECK_NOTHROW(Boleto(1, 5));
    CHECK_NOTHROW(Boleto(Boleto::MAX_PARCELAS, 5));
}

TEST_CASE("Boleto: parcelas fora do limite lancam excecao") {
    CHECK_THROWS_AS(Boleto(0, 5), PagamentoInvalidoException);
    CHECK_THROWS_AS(Boleto(-1, 5), PagamentoInvalidoException);
    CHECK_THROWS_AS(Boleto(Boleto::MAX_PARCELAS + 1, 5), PagamentoInvalidoException);
}

TEST_CASE("Boleto: prazo zero ou negativo lanca excecao") {
    CHECK_THROWS_AS(Boleto(3, 0), PagamentoInvalidoException);
    CHECK_THROWS_AS(Boleto(3, -5), PagamentoInvalidoException);
}

TEST_CASE("Boleto: a validacao do pagamento sempre passa") {
    Boleto b(3, 5);
    CHECK_NOTHROW(b.validarPagamento(900.0));
}

TEST_CASE("Boleto: nunca tem troco") {
    Boleto b(3, 5);
    CHECK(b.calcularTroco(900.0) == doctest::Approx(0.0));
}

TEST_CASE("Boleto: getters devolvem o que foi informado") {
    Boleto b(6, 10);
    CHECK(b.getNumeroParcelas() == 6);
    CHECK(b.getDiasParaVencimento() == 10);
}

TEST_CASE("Boleto: descricao mostra as parcelas e o prazo") {
    Boleto b(3, 5);
    CHECK(b.descricao().find("3x") != std::string::npos);
    CHECK(b.descricao().find("5 dias") != std::string::npos);
}
