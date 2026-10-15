#include "doctest.h"
#include "Vendedor.hpp"

TEST_CASE("Consultar nome do vendedor") {
    Vendedor sale("Nome", "123", 7);
    CHECK(sale.getNome() == "Nome");
}

TEST_CASE("Consultar ID do vendedor") {
    Vendedor sale("Nome", "123", 7);
    CHECK(sale.getId() == "123");
}

TEST_CASE("Consultar percentual de comissão do vendedor") {
    Vendedor sale("Nome", "123", 7);
    CHECK(sale.getPercentualComissao() == 7);
}

TEST_CASE("Cadastrar veiculo pelo vendedor"){
    Vendedor sale("Nome", "123", 7);
    Cadastro_Veiculos register;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    CHECK(sale.cadastrarVeiculo(register, v) == true);
}

TEST_CASE("Consultar veiculo pelo vendedor"){
    Vendedor sale("Nome", "123", 7);
    Cadastro_Veiculos register;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    sale.cadastrar_Veiculo(v);
    const Veiculo* find = sale.consultarVeiculo(register, "ABC1D23");
    REQUIRE(find != nullptr);
    CHECK(find->getPlaca() == "ABC1D23");
}

TEST_CASE("Atualizar veiculo pelo vendedor"){
    Vendedor sale("Nome", "123", 7);
    Cadastro_Veiculos register;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    Veiculo newData("NovaMarca", "NovoModelo", "ABC1D23", 2023, 85000);
    sale.cadastrar_Veiculo(v);
    CHECK(sale.atualizarVeiculo(register, "ABC1D23", newData) == true);
}

TEST_CASE("Calcular comissão do vendedor") {
    Vendedor sale("Nome", "123", 7);
    double valorVenda = 1000.0;
    double expectedComissao = valorVenda * (sale.getPercentualComissao() / 100.0);
    CHECK(sale.calcularComissao(valorVenda) == expectedComissao);
}