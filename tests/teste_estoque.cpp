#include "doctest.h"
#include "Estoque.hpp"

#include <climits>
#include <stdexcept>

TEST_CASE("Estoque: adicionar e buscar produto") {
    Estoque estoque;
    estoque.adicionarProduto(1, "Pneu", 10);

    CHECK(estoque.buscarProdutoPorId(1) == 10);
    CHECK(estoque.getDescricaoProduto(1) == "Pneu");
    CHECK(estoque.getTotalItens() == 10);
}

TEST_CASE("Estoque: adicionar produto existente repoe a quantidade") {
    Estoque estoque;
    estoque.adicionarProduto(1, "Pneu", 10);
    estoque.adicionarProduto(1, "Pneu", 5);

    // repoe e soma no msm id
    CHECK(estoque.buscarProdutoPorId(1) == 15);
    CHECK(estoque.listarIds().size() == 1);
}

TEST_CASE("Estoque: adicionarProduto rejeita argumentos invalidos") {
    Estoque estoque;

    SUBCASE("ID zero ou negativo") {
        CHECK_THROWS_AS(estoque.adicionarProduto(0, "Pneu", 1), std::invalid_argument);
        CHECK_THROWS_AS(estoque.adicionarProduto(-3, "Pneu", 1), std::invalid_argument);
    }
    SUBCASE("Descricao vazia") {
        CHECK_THROWS_AS(estoque.adicionarProduto(1, "", 1), std::invalid_argument);
    }
    SUBCASE("Descricao com ponto e virgula ou quebra de linha") {
        // o separador caga a formatacao do arquivo, tem q barrar
        CHECK_THROWS_AS(estoque.adicionarProduto(1, "Pneu;Roda", 1), std::invalid_argument);
        CHECK_THROWS_AS(estoque.adicionarProduto(1, "Pneu\nRoda", 1), std::invalid_argument);
    }
    SUBCASE("Quantidade zero ou negativa") {
        CHECK_THROWS_AS(estoque.adicionarProduto(1, "Pneu", 0), std::invalid_argument);
        CHECK_THROWS_AS(estoque.adicionarProduto(1, "Pneu", -1), std::invalid_argument);
    }
    SUBCASE("Mesmo ID com outra descricao") {
        estoque.adicionarProduto(1, "Pneu", 1);
        CHECK_THROWS_AS(estoque.adicionarProduto(1, "Roda", 1), std::invalid_argument);
        CHECK(estoque.buscarProdutoPorId(1) == 1); // saldo nao muda
    }
    SUBCASE("Soma que estoura o limite de int") {
        estoque.adicionarProduto(1, "Pneu", INT_MAX);
        CHECK_THROWS_AS(estoque.adicionarProduto(1, "Pneu", 1), std::overflow_error);
        CHECK(estoque.buscarProdutoPorId(1) == INT_MAX);
    }
    SUBCASE("Nada foi cadastrado nos casos invalidos") {
        CHECK_THROWS(estoque.adicionarProduto(0, "Pneu", 1));
        CHECK(estoque.listarIds().empty());
    }
}

TEST_CASE("Estoque: produto inexistente lanca out_of_range") {
    Estoque estoque;
    CHECK_THROWS_AS(estoque.buscarProdutoPorId(99), std::out_of_range);
    CHECK_THROWS_AS(estoque.getDescricaoProduto(99), std::out_of_range);
    CHECK_THROWS_AS(estoque.darBaixaQuantidade(99, 1), std::out_of_range);
    CHECK_THROWS_AS(estoque.alertarProdutoEsgotado(99), std::out_of_range);
}

TEST_CASE("Estoque: dar baixa na quantidade") {
    Estoque estoque;
    estoque.adicionarProduto(1, "Pneu", 10);

    SUBCASE("Baixa valida diminui o saldo") {
        estoque.darBaixaQuantidade(1, 4);
        CHECK(estoque.buscarProdutoPorId(1) == 6);
    }
    SUBCASE("Baixa do saldo inteiro esgota o produto") {
        CHECK_FALSE(estoque.alertarProdutoEsgotado(1));
        estoque.darBaixaQuantidade(1, 10);
        CHECK(estoque.buscarProdutoPorId(1) == 0);
        CHECK(estoque.alertarProdutoEsgotado(1));
    }
    SUBCASE("Baixa maior que o saldo e recusada sem alterar o estoque") {
        CHECK_THROWS_AS(estoque.darBaixaQuantidade(1, 11), std::runtime_error);
        CHECK(estoque.buscarProdutoPorId(1) == 10);
    }
    SUBCASE("Quantidade zero ou negativa e recusada") {
        CHECK_THROWS_AS(estoque.darBaixaQuantidade(1, 0), std::invalid_argument);
        CHECK_THROWS_AS(estoque.darBaixaQuantidade(1, -2), std::invalid_argument);
        CHECK(estoque.buscarProdutoPorId(1) == 10);
    }
}

TEST_CASE("Estoque: total de itens e lista de IDs") {
    Estoque estoque;
    CHECK(estoque.getTotalItens() == 0);
    CHECK(estoque.listarIds().empty());

    estoque.adicionarProduto(5, "Roda", 4);
    estoque.adicionarProduto(2, "Pneu", 6);
    estoque.adicionarProduto(9, "Farol", 1);

    CHECK(estoque.getTotalItens() == 11);
    
    auto ids = estoque.listarIds();
    REQUIRE(ids.size() == 3);
    CHECK(ids[0] == 2);
    CHECK(ids[1] == 5);
    CHECK(ids[2] == 9);
}