#include <stdexcept>
#include "doctest.h"
#include "Carrinho.hpp"
#include "PagamentoInvalidoException.hpp"
#include "Veiculo.hpp"

namespace {
Veiculo civic() { return Veiculo("Honda", "Civic", "ABC1234", 2024, 150000.0); }
Veiculo uno() { return Veiculo("Fiat", "Uno", "XYZ9876", 2020, 40000.0); }
}

TEST_CASE("Carrinho: novo carrinho esta vazio e com total zero") {
    Carrinho c;
    CHECK(c.estaVazio());
    CHECK(c.calcularTotal() == doctest::Approx(0.0));
    CHECK(c.getItens().empty());
}

TEST_CASE("Carrinho: adicionar um veiculo tira o carrinho do estado vazio") {
    Carrinho c;
    c.adicionarVeiculo(civic());
    CHECK_FALSE(c.estaVazio());
    CHECK(c.getItens().size() == 1);
}

TEST_CASE("Carrinho: o total de um veiculo e o preco dele") {
    Carrinho c;
    c.adicionarVeiculo(civic());
    CHECK(c.calcularTotal() == doctest::Approx(150000.0));
}

TEST_CASE("Carrinho: a quantidade multiplica o preco no total") {
    Carrinho c;
    c.adicionarVeiculo(civic(), 2);
    CHECK(c.calcularTotal() == doctest::Approx(300000.0));
}

TEST_CASE("Carrinho: o total soma veiculos diferentes") {
    Carrinho c;
    c.adicionarVeiculo(civic());
    c.adicionarVeiculo(uno(), 2);
    CHECK(c.calcularTotal() == doctest::Approx(230000.0));
    CHECK(c.getItens().size() == 2);
}

TEST_CASE("Carrinho: a descricao do item e marca e modelo") {
    Carrinho c;
    c.adicionarVeiculo(civic());
    CHECK(c.getItens()[0].getDescricao() == "Honda Civic");
}

TEST_CASE("Carrinho: quantidade zero lanca excecao e nada e adicionado") {
    Carrinho c;
    CHECK_THROWS_AS(c.adicionarVeiculo(civic(), 0), PagamentoInvalidoException);
    CHECK(c.estaVazio());
}

TEST_CASE("Carrinho: quantidade negativa lanca excecao") {
    Carrinho c;
    CHECK_THROWS_AS(c.adicionarVeiculo(civic(), -1), PagamentoInvalidoException);
}

TEST_CASE("Carrinho: remover um item atualiza o total") {
    Carrinho c;
    c.adicionarVeiculo(civic());
    c.adicionarVeiculo(uno());
    c.removerItem(0);
    CHECK(c.getItens().size() == 1);
    CHECK(c.calcularTotal() == doctest::Approx(40000.0));
}

TEST_CASE("Carrinho: remover o item do meio mantem a ordem dos outros") {
    Carrinho c;
    c.adicionarVeiculo(civic());
    c.adicionarVeiculo(uno());
    c.adicionarVeiculo(civic(), 2);
    c.removerItem(1);
    REQUIRE(c.getItens().size() == 2);
    CHECK(c.getItens()[0].getQuantidade() == 1);
    CHECK(c.getItens()[1].getQuantidade() == 2);
}

TEST_CASE("Carrinho: remover indice inexistente lanca out_of_range") {
    Carrinho c;
    c.adicionarVeiculo(civic());
    CHECK_THROWS_AS(c.removerItem(1), std::out_of_range);
}

TEST_CASE("Carrinho: remover de um carrinho vazio lanca out_of_range") {
    Carrinho c;
    CHECK_THROWS_AS(c.removerItem(0), std::out_of_range);
}

TEST_CASE("Carrinho: esvaziar deixa o carrinho vazio e com total zero") {
    Carrinho c;
    c.adicionarVeiculo(civic());
    c.adicionarVeiculo(uno());
    c.esvaziar();
    CHECK(c.estaVazio());
    CHECK(c.calcularTotal() == doctest::Approx(0.0));
}

TEST_CASE("Carrinho: depois de esvaziar da pra adicionar de novo") {
    Carrinho c;
    c.adicionarVeiculo(civic());
    c.esvaziar();
    c.adicionarVeiculo(uno());
    CHECK(c.calcularTotal() == doctest::Approx(40000.0));
}
