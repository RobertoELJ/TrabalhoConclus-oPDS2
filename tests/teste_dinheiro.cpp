#include "doctest.h"
#include "Dinheiro.hpp"
#include "PagamentoInvalidoException.hpp"

TEST_CASE("Dinheiro: aplica o desconto a vista sobre o preco") {
    Dinheiro d(10.0, 1000.0);
    CHECK(d.calcularValorFinal(1000.0) == doctest::Approx(900.0));
}

TEST_CASE("Dinheiro: desconto zero nao altera o preco") {
    Dinheiro d(0.0, 500.0);
    CHECK(d.calcularValorFinal(500.0) == doctest::Approx(500.0));
}

TEST_CASE("Dinheiro: desconto de 100 por cento zera o valor") {
    Dinheiro d(100.0, 0.0);
    CHECK(d.calcularValorFinal(500.0) == doctest::Approx(0.0));
}

TEST_CASE("Dinheiro: calcula o troco quando o cliente entrega mais que o total") {
    Dinheiro d(10.0, 1000.0);
    double final = d.calcularValorFinal(1000.0);
    CHECK(d.calcularTroco(final) == doctest::Approx(100.0));
}

TEST_CASE("Dinheiro: sem troco quando o valor entregue e exato") {
    Dinheiro d(0.0, 500.0);
    CHECK(d.calcularTroco(500.0) == doctest::Approx(0.0));
}

TEST_CASE("Dinheiro: pagamento que cobre o total e aceito") {
    Dinheiro d(0.0, 500.0);
    CHECK_NOTHROW(d.validarPagamento(500.0));
}

TEST_CASE("Dinheiro: pagamento menor que o total lanca excecao") {
    Dinheiro d(0.0, 400.0);
    CHECK_THROWS_AS(d.validarPagamento(500.0), PagamentoInvalidoException);
}

TEST_CASE("Dinheiro: desconto negativo lanca excecao") {
    CHECK_THROWS_AS(Dinheiro(-1.0, 100.0), PagamentoInvalidoException);
}

TEST_CASE("Dinheiro: desconto acima de 100 lanca excecao") {
    CHECK_THROWS_AS(Dinheiro(100.1, 100.0), PagamentoInvalidoException);
}

TEST_CASE("Dinheiro: valor pago negativo lanca excecao") {
    CHECK_THROWS_AS(Dinheiro(5.0, -10.0), PagamentoInvalidoException);
}

TEST_CASE("Dinheiro: getters devolvem o que foi informado") {
    Dinheiro d(5.0, 250.0);
    CHECK(d.getPercentualDesconto() == doctest::Approx(5.0));
    CHECK(d.getValorPago() == doctest::Approx(250.0));
}

TEST_CASE("Dinheiro: descricao menciona dinheiro") {
    Dinheiro d(5.0, 250.0);
    CHECK(d.descricao().find("Dinheiro") != std::string::npos);
}
