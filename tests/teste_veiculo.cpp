#include "doctest.h"
#include "Veiculo.hpp"

TEST_CASE("Consultar Marca"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    CHECK(v.getMarca() == "Marca");
}

TEST_CASE("Consultar Modelo"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    CHECK(v.getModelo() == "Modelo");
}

TEST_CASE("Consultar Placa"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    CHECK(v.getPlaca() == "ABC1D23");
}

TEST_CASE("Consultar Ano"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    CHECK(v.getAno() == 2026);
}

TEST_CASE("Consultar Preco"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    CHECK(v.getPreco() == 75000);
}

TEST_CASE("Consultar Disponibilidade"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    v.setDisponivel(true);
    CHECK(v.Disponivel() == true);
}

TEST_CASE("Alterar Marca"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    v.setMarca("NovaMarca");
    CHECK(v.getMarca() == "NovaMarca");
}

TEST_CASE("Alterar Modelo"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    v.setModelo("NovoModelo");
    CHECK(v.getModelo() == "NovoModelo");
}

TEST_CASE("Alterar Ano"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    v.setAno(2023);
    CHECK(v.getAno() == 2023);
}

TEST_CASE("Alterar Preco"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    v.setPreco(85000);
    CHECK(v.getPreco() == 85000);
}

TEST_CASE("Alterar Disponibilidade"){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    v.setDisponivel(false);
    CHECK(v.Disponivel() == false);
}

TEST_CASE(Validar os dados do veiculo){
    Veiculo v("Marca", "Modelo", "ABC1D23", 2026, 75000);
    CHECK(v.validarDados() == true);
}