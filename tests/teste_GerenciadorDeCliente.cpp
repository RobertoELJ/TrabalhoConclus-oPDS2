#include "GerenciamentoDeClientes.hpp"
#include "doctest.h"
#include <stdexcept>

TEST_CASE("Cadastrar cliente") {
    GerenciamentoDeClientes gerenciador;
    CHECK_NOTHROW(gerenciador.cadastrarCliente("João", "joao@email.com", "12345678901"));

    SUBCASE("Cadastrar cliente com email inválido") {
        // Usa um CPF diferente para garantir que a falha ocorra apenas devido ao e-mail
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("João", "joaoemail.com", "12345678902"), std::invalid_argument);
    }

    SUBCASE("Cadastrar cliente com CPF inválido") {
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("João", "joao@email.com", "012345678911"), std::invalid_argument);
    }

    SUBCASE("Cadastrar cliente com email e CPF inválidos") {
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("João", "joaoemail.com", "012345678911"), std::invalid_argument);
    }
    
    SUBCASE("Cadastrar cliente com nome vazio") {
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("", "maria@email.com", "12345678903"), std::invalid_argument);
    }

    SUBCASE("Cadastrar cliente com CPF contendo letras") {
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("Maria", "maria@email.com", "1234567890a"), std::invalid_argument);
    }

    SUBCASE("Cadastrar o mesmo CPF duas vezes lança exceção") {
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("João Clone", "joaoclone@email.com", "12345678901"), std::invalid_argument);
    }

    SUBCASE("Quantidade de clientes se mantém após cadastro inválido") {
        int quantidadeAntes = gerenciador.getQuantidadeClientes();
        CHECK_THROWS_AS(gerenciador.cadastrarCliente("Erro", "email.errado", "123"), std::invalid_argument);
        CHECK(gerenciador.getQuantidadeClientes() == quantidadeAntes);
    }
}

TEST_CASE("Alterar o nome do cliente") {
    GerenciamentoDeClientes gerenciador;
    gerenciador.cadastrarCliente("João", "joao@email.com", "12345678911");
    
    SUBCASE("Alteração válida") {
        CHECK_NOTHROW(gerenciador.alterarNomeCliente(1, "João Silva"));
    }

    SUBCASE("Alterar nome em ID fora do limite (out_of_range)") {
        CHECK_THROWS_AS(gerenciador.alterarNomeCliente(99, "X"), std::out_of_range);
    }
}

TEST_CASE("Alterar o email do cliente") {
    GerenciamentoDeClientes gerenciador;
    gerenciador.cadastrarCliente("João", "joao@email.com", "12345678911");
    
    SUBCASE("Alteração válida") {
        CHECK_NOTHROW(gerenciador.alterarEmailCliente(1, "joao.silva@email.com"));
    }

    SUBCASE("Alterar o email do cliente para um email inválido") {
        CHECK_THROWS_AS(gerenciador.alterarEmailCliente(1, "joao.sila.com"), std::