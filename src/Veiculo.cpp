#include "Veiculo.hpp"

Veiculo::Veiculo(const std::string& marca, const std::string& modelo, const std::string& placa, int ano, double preco)
    : marca(marca), modelo(modelo), placa(placa), ano(ano), preco(preco), disponivel(true) {}

std::string Veiculo::getMarca() const {
    return marca;
}

std::string Veiculo::getModelo() const {
    return modelo;
}

std::string Veiculo::getPlaca() const {
    return placa;
}

int Veiculo::getAno() const {
    return ano;
}

double Veiculo::getPreco() const {
    return preco;
}

bool Veiculo::Disponivel() const {
    return disponivel;
}

std::string Veiculo::setMarca(const std::string& newMarca) {
    marca = newMarca;
    return marca;
}

std::string Veiculo::setModelo(const std::string& newModelo) {
    modelo = newModelo;
    return modelo;
}

int Veiculo::setAno(int newAno) {
    ano = newAno;
    return ano;
}

double Veiculo::setPreco(double newPreco) {
    preco = newPreco;
    return preco;
}

bool Veiculo::setDisponivel(bool newDisponivel) {
    disponivel = newDisponivel;
    return disponivel;
}

bool Veiculo::validarDados() const {
    if (marca.empty() || modelo.empty() || placa.empty()) {
        return false;
    }
    if (ano <= 0) { 
        return false;
    }
    if (preco < 0) {
        return false;
    }
    return true;
}