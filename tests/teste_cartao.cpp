#include "doctest.h"
#include "Cartao.hpp"
#include "PagamentoInvalidoException.hpp"

TEST_CASE("Cartao: aplica os juros uma vez sobre o preco") {
    Cartao c(3, 5.0);
    CHECK(c.calcularValorFinal(1000.0) == doctest::Approx(1050.0));
}

TEST_CASE("Cartao: sem juros o valor final e o preco") {
    Cartao c(1, 0.0);
    CHECK(c.calcularValorFinal(1000.0) == doctest::Approx(1000.0));
}

TEST_CASE("Cartao: valor da parcela divide o valor final pelas parcelas") {
    Cartao c(3, 5.0);
    CHECK(c.valorDaParcela(1000.0) == doctest::Approx(350.0));
}

TEST_CASE("Cartao: aceita de 1 ate o maximo de parcelas") {
    CHECK_NOTHROW(Cartao(1, 0.0));
    CHECK_NOTHROW(Cartao(Cartao::MAX_PARCELAS, 0.0));
}

TEST_CASE("Cartao: zero parcelas lanca excecao") {
    CHECK_THROWS_AS(Cartao(0, 0.0), PagamentoInvalidoException);
}

TEST_CASE("Cartao: parcelas negativas lancam excecao") {
    CHECK_THROWS_AS(Cartao(-2, 0.0), PagamentoInvalidoException);
}

TEST_CASE("Cartao: acima do maximo de parcelas lanca excecao") {
    CHECK_THROWS_AS(Cartao(Cartao::MAX_PARCELAS + 1, 0.0), PagamentoInvalidoException);
}

TEST_CASE("Cartao: juros negativos lancam excecao") {
    CHECK_THROWS_AS(Cartao(3, -1.0), PagamentoInvalidoException);
}

TEST_CASE("Cartao: a validacao do pagamento sempre passa") {
    Cartao c(3, 5.0);
    CHECK_NOTHROW(c.validarPagamento(1050.0));
}

TEST_CASE("Cartao: nunca tem troco") {
    Cartao c(3, 5.0);
    CHECK(c.calcularTroco(1050.0) == doctest::Approx(0.0));
}

TEST_CASE("Cartao: getters devolvem o que foi informado") {
    Cartao c(6, 2.5);
    CHECK(c.getNumeroParcelas() == 6);
    CHECK(c.getTaxaJuros() == doctest::Approx(2.5));
}

TEST_CASE("Cartao: descricao mostra o numero de parcelas") {
    Cartao c(3, 5.0);
    CHECK(c.descricao().find("3x") != std::string::npos);
}
