#include "doctest.h"
#include "CadastroVeiculo.hpp"

TEST_CASE("Cadastrar veiculo") {
    CadastroVeiculos registro;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    CHECK(registro.cadastrarVeiculo(v) == true);
}

TEST_CASE("Verificar placa cadastrada") {
    CadastroVeiculos registro;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    registro.cadastrarVeiculo(v);
    CHECK(registro.placaCadastrada("ABC1D23") == true);
}

TEST_CASE("Buscar veiculo por placa") {
    CadastroVeiculos registro;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    registro.cadastrarVeiculo(v);
    const Veiculo* find = registro.buscarVeiculo("ABC1D23");
    REQUIRE(find != nullptr);
    CHECK(find->getPlaca() == "ABC1D23");
}

TEST_CASE("Atualizar veiculo") {
    CadastroVeiculos registro;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    Veiculo newData("NovaMarca", "NovoModelo", "ABC1D23", 2023, 85000);
    registro.cadastrarVeiculo(v);
    CHECK(registro.atualizarVeiculo("ABC1D23", newData) == true);

    const Veiculo* updated = registro.buscarVeiculo("ABC1D23");
    REQUIRE(updated != nullptr);
    CHECK(updated->getPreco() == 85000);
}

TEST_CASE("Listar veiculos") {
    CadastroVeiculos registro;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    registro.cadastrarVeiculo(v);
    CHECK(registro.listarVeiculos().size() == 1);
}