#include "GerenciamentoDeClientes.hpp"
#include "doctest.h"
#include <stdexcept>

TEST_CASE("Cadastrar cliente") {
    GerenciamentoDeClientes gerenciador;
    CHECK_NOTHROW(gerenciador.cadastrarCliente("João", "joao@email.com", "12345678901"));

    SUBCASE("E-mail com formato irregular é rejeitado") {
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("A", "a@.com", "12345678902"), std::invalid_argument);
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("B", "a@b.", "12345678903"), std::invalid_argument);
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("C", "a@@b.com", "12345678904"), std::invalid_argument);
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("D", "@b.com", "12345678905"), std::invalid_argument);
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("E", "a b@c.com", "12345678906"), std::invalid_argument);
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("F", "a.b@c", "12345678907"), std::invalid_argument);
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("G", "joaoemail.com", "12345678908"), std::invalid_argument);
    }

    SUBCASE("CPF inválido ou repetido") {
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("João", "joao@email.com", "012345678911"), std::invalid_argument);
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("Maria", "maria@email.com", "1234567890a"), std::invalid_argument);
        
        gerenciador.cadastrarCliente("Clone", "clone@email.com", "11122233344");
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("Clone2", "clone2@email.com", "11122233344"), std::invalid_argument);
    }

    SUBCASE("Nome vazio e persistência de quantidade") {
        int qtdeAntes = gerenciador.getQuantidadeClientes();
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("", "maria@email.com", "12345678903"), std::invalid_argument);
        CHECK(gerenciador.getQuantidadeClientes() == qtdeAntes);
    }
}

TEST_CASE("Alterar o nome do cliente") {
    GerenciamentoDeClientes gerenciador;
    gerenciador.cadastrarCliente("João", "joao@email.com", "12345678911");
    
    SUBCASE("Alteração válida") {
        CHECK_NOTHROW(gerenciador.alterarNomeCliente(1, "João Silva"));
    }

    SUBCASE("Alterar nome com ID inválido ou nome vazio lança exceção") {
        CHECK_THROWS_AS(gerenciador.alterarNomeCliente(0, "X"), std::out_of_range);
        CHECK_THROWS_AS(gerenciador.alterarNomeCliente(-1, "X"), std::out_of_range);
        CHECK_THROWS_AS(gerenciador.alterarNomeCliente(99, "X"), std::out_of_range);
        CHECK_THROWS_AS(gerenciador.alterarNomeCliente(1, ""), std::invalid_argument);
    }
}

TEST_CASE("Alterar o email do cliente") {
    GerenciamentoDeClientes gerenciador;
    gerenciador.cadastrarCliente("João", "joao@email.com", "12345678911");
    
    SUBCASE("Alteração válida") {
        CHECK_NOTHROW(gerenciador.alterarEmailCliente(1, "joao.silva@email.com"));
    }

    SUBCASE("E-mail sem domínio final é rejeitado") {
        CHECK_THROWS_AS(gerenciador.alterarEmailCliente(1, "joao.sila.com"), std::invalid_argument);
    }

    SUBCASE("Alterar e-mail com ID fora do limite (out_of_range) lança exceção") {
        CHECK_THROWS_AS(gerenciador.alterarEmailCliente(0, "a@b.com"), std::out_of_range);
        CHECK_THROWS_AS(gerenciador.alterarEmailCliente(99, "x@y.com"), std::out_of_range);
    }
}

TEST_CASE("Mostrar clientes") {
    GerenciamentoDeClientes gerenciador;
    
    SUBCASE("Lista vazia") {
        CHECK_NOTHROW(gerenciador.mostrarClientes());
    }

    SUBCASE("Com clientes cadastrados") {
        gerenciador.cadastrarCliente("João", "joao@email.com", "12345678911");
        CHECK_NOTHROW(gerenciador.mostrarClientes());
    }
}