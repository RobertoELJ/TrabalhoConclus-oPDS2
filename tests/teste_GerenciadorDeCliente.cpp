#include "GerenciamentoDeClientes.hpp"
#include "doctest.h"

TEST_CASE("Cadastrar cliente") {
    GerenciamentoDeClientes Cliente;
    CHECK_NOTHROW(Cliente.cadastrarCliente("João", "joao@email.com", "12345678901"));

    SUBCASE("Cadastrar cliente com email inválido") {
    GerenciamentoDeClientes Cliente;
    CHECK_THROWS(Cliente.cadastrarCliente("João", "joaoemail.com", "12345678901"));
    }

    SUBCASE("Cadastrar cliente com CPF inválido") {
    GerenciamentoDeClientes Cliente;
    CHECK_THROWS(Cliente.cadastrarCliente("João", "joao@email.com", "012345678911"));
    }

    SUBCASE("Cadastrar cliente com email e CPF inválidos") {
    GerenciamentoDeClientes Cliente;
    CHECK_THROWS(Cliente.cadastrarCliente("João", "joaoemail.com", "012345678911"));
    }
}

TEST_CASE("Alterar o nome do cliente") {
    GerenciamentoDeClientes Cliente;
    Cliente.cadastrarCliente("João", "joao@email.com", "12345678911");
    CHECK_NOTHROW(Cliente.alterarNomeCliente(1, "João Silva"));
}

TEST_CASE("Alterar o email do cliente") {
    GerenciamentoDeClientes Cliente;
    Cliente.cadastrarCliente("João", "joao@email.com", "12345678911");
    CHECK_NOTHROW(Cliente.alterarEmailCliente(1, "joao.silva@email.com"));

    SUBCASE("Alterar o email do cliente para um email inválido") {
    GerenciamentoDeClientes Cliente;
    Cliente.cadastrarCliente("João", "joao@email.com", "12345678911");
    CHECK_THROWS(Cliente.alterarEmailCliente(1, "joao.sila.com"));
    
    }
}

TEST_CASE("Mostrar clientes") `{
    GerenciamentoDeClientes Cliente;
    Cliente.cadastrarCliente("João", "joao@email.com", "12345678911");
    CHECK_NOTHROW(Cliente.mostrarClientes());
}