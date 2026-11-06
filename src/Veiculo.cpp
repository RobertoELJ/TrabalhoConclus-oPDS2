#include "Veiculo.hpp"
#include <stdexcept>


Veiculo::Veiculo(const std::string& marca, const std::string& modelo, const std::string& placa, int ano, double preco)
    : marca(marca), modelo(modelo), placa(placa), ano(ano), preco(preco), disponivel(true) {

        if(!validarDados()) {
            throw std::invalid_argument("Dados invalidos para criar o veiculo.");
        }
    }

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

bool Veiculo::estaDisponivel() const {
    return disponivel;
}

std::string Veiculo::setMarca(const std::string& newMarca) {

    if (newMarca.empty()) {
        throw std::invalid_argument("Marca invalida");
    }

    marca = newMarca;
    return marca;
}

std::string Veiculo::setModelo(const std::string& newModelo) {

    if (newModelo.empty()) {
        throw std::invalid_argument("Modelo invalido");
    }

    modelo = newModelo;
    return modelo;
}

int Veiculo::setAno(int newAno) {

    if (newAno <=0) {
        throw std::invalid_argument("Ano invalido");
    }

    ano = newAno;
    return ano;
}

double Veiculo::setPreco(double newPreco) {

    if (newPreco < 0) {
        throw std::invalid_argument("Preco invalido");
    }

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