#include "doctest.h"
#include "ItemCarrinho.hpp"
#include "PagamentoInvalidoException.hpp"

TEST_CASE("ItemCarrinho: subtotal e preco unitario vezes a quantidade") {
    ItemCarrinho item("Honda Civic", 150000.0, 2);
    CHECK(item.calcularSubtotal() == doctest::Approx(300000.0));
}

TEST_CASE("ItemCarrinho: com quantidade 1 o subtotal e o proprio preco") {
    ItemCarrinho item("Fiat Uno", 40000.0, 1);
    CHECK(item.calcularSubtotal() == doctest::Approx(40000.0));
}

TEST_CASE("ItemCarrinho: getters devolvem o que foi informado") {
    ItemCarrinho item("Honda Civic", 150000.0, 3);
    CHECK(item.getDescricao() == "Honda Civic");
    CHECK(item.getPrecoUnitario() == doctest::Approx(150000.0));
    CHECK(item.getQuantidade() == 3);
}

TEST_CASE("ItemCarrinho: preco zero lanca excecao") {
    CHECK_THROWS_AS(ItemCarrinho("Carro", 0.0, 1), PagamentoInvalidoException);
}

TEST_CASE("ItemCarrinho: preco negativo lanca excecao") {
    CHECK_THROWS_AS(ItemCarrinho("Carro", -100.0, 1), PagamentoInvalidoException);
}

TEST_CASE("ItemCarrinho: quantidade zero lanca excecao") {
    CHECK_THROWS_AS(ItemCarrinho("Carro", 100.0, 0), PagamentoInvalidoException);
}

TEST_CASE("ItemCarrinho: quantidade negativa lanca excecao") {
    CHECK_THROWS_AS(ItemCarrinho("Carro", 100.0, -1), PagamentoInvalidoException);
}
