#include "doctest.h"
#include "CadastroVeiculo.hpp"

TEST_CASE("Cadastrar veiculo") {
    Cadastro_Veiculos registro;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    CHECK(registro.cadastrar_Veiculo(v) == true);
}

TEST_CASE("Verificar placa cadastrada") {
    Cadastro_Veiculos registro;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    registro.cadastrar_Veiculo(v);
    CHECK(registro.placa_Cadastrada("ABC1D23") == true);
}

TEST_CASE("Buscar veiculo por placa") {
    Cadastro_Veiculos registro;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    registro.cadastrar_Veiculo(v);
    const Veiculo* find = registro.buscar_Veiculos("ABC1D23");
    REQUIRE(find != nullptr);
    CHECK(find->getPlaca() == "ABC1D23");
}

TEST_CASE("Atualizar veiculo") {
    Cadastro_Veiculos registro;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    Veiculo newData("NovaMarca", "NovoModelo", "ABC1D23", 2023, 85000);
    registro.cadastrar_Veiculo(v);
    CHECK(registro.atualizar_Veiculo("ABC1D23", newData) == true);

    const Veiculo* updated = registro.buscar_Veiculos("ABC1D23");
    REQUIRE(updated != nullptr);
    CHECK(updated->getPreco() == 85000);
}

TEST_CASE("Listar veiculos") {
    Cadastro_Veiculos registro;
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    registro.cadastrar_Veiculo(v);
    CHECK(registro.listar_Veiculos().size() == 1);
}