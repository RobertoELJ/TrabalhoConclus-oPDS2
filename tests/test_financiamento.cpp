#include "doctest.h"
#include "Financiamento.hpp"
#include "PagamentoInvalidoException.hpp"

TEST_CASE("Financiamento: valor final e entrada mais saldo com juros simples") {
    // preco 1000, entrada 200, 10 meses, 2% ao mes: saldo 800, juros 160
    Financiamento f(200.0, 10, 2.0);
    CHECK(f.calcularValorFinal(1000.0) == doctest::Approx(1160.0));
}

TEST_CASE("Financiamento: sem juros o valor final e o preco") {
    Financiamento f(200.0, 10, 0.0);
    CHECK(f.calcularValorFinal(1000.0) == doctest::Approx(1000.0));
}

TEST_CASE("Financiamento: parcela divide o saldo financiado pelo prazo") {
    Financiamento f(200.0, 10, 2.0);
    CHECK(f.valorDaParcela(1000.0) == doctest::Approx(96.0));
}

TEST_CASE("Financiamento: entrada igual ao preco nao financia nada") {
    Financiamento f(1000.0, 12, 3.0);
    CHECK(f.calcularValorFinal(1000.0) == doctest::Approx(1000.0));
    CHECK(f.valorDaParcela(1000.0) == doctest::Approx(0.0));
}

TEST_CASE("Financiamento: entrada maior que o preco lanca excecao") {
    Financiamento f(1500.0, 10, 2.0);
    CHECK_THROWS_AS(f.calcularValorFinal(1000.0), PagamentoInvalidoException);
}

TEST_CASE("Financiamento: prazo zero lanca excecao") {
    CHECK_THROWS_AS(Financiamento(100.0, 0, 2.0), PagamentoInvalidoException);
}

TEST_CASE("Financiamento: prazo negativo lanca excecao") {
    CHECK_THROWS_AS(Financiamento(100.0, -3, 2.0), PagamentoInvalidoException);
}

TEST_CASE("Financiamento: entrada negativa lanca excecao") {
    CHECK_THROWS_AS(Financiamento(-1.0, 10, 2.0), PagamentoInvalidoException);
}

TEST_CASE("Financiamento: taxa negativa lanca excecao") {
    CHECK_THROWS_AS(Financiamento(100.0, 10, -0.5), PagamentoInvalidoException);
}

TEST_CASE("Financiamento: a validacao do pagamento sempre passa") {
    Financiamento f(200.0, 10, 2.0);
    CHECK_NOTHROW(f.validarPagamento(1160.0));
}

TEST_CASE("Financiamento: nunca tem troco") {
    Financiamento f(200.0, 10, 2.0);
    CHECK(f.calcularTroco(1160.0) == doctest::Approx(0.0));
}

TEST_CASE("Financiamento: getters devolvem o que foi informado") {
    Financiamento f(300.0, 24, 1.5);
    CHECK(f.getEntrada() == doctest::Approx(300.0));
    CHECK(f.getPrazoMeses() == 24);
    CHECK(f.getTaxaMensal() == doctest::Approx(1.5));
}

TEST_CASE("Financiamento: descricao mostra o prazo") {
    Financiamento f(300.0, 24, 1.5);
    CHECK(f.descricao().find("24x") != std::string::npos);
}
