#include "Veiculo.hpp"
#include <stdexcept>
#include <cmath>

namespace{
    bool textoValido(const std::string& texto) {
        return texto.find_first_not_of(" \t\n\r") != std::string::npos;
    }

    bool anoValido(int ano) {
        return ano >= 1886 && ano < 2027;
    }

    bool precoValido(double preco) {
        return std::isfinite(preco) && preco >= 0;
    }
}

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

    if (!textoValido(newMarca)) {
        throw std::invalid_argument("Marca invalida");
    }

    marca = newMarca;
    return marca;
}

std::string Veiculo::setModelo(const std::string& newModelo) {

    if (!textoValido(newModelo)) {
        throw std::invalid_argument("Modelo invalido");
    }

    modelo = newModelo;
    return modelo;
}

int Veiculo::setAno(int newAno) {

    if (!anoValido(newAno)) {
        throw std::invalid_argument("Ano invalido");
    }

    ano = newAno;
    return ano;
}

double Veiculo::setPreco(double newPreco) {

    if (!precoValido(newPreco)) {
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

    if(!textoValido(marca) || !textoValido(modelo) || !textoValido(placa)) {
        return false;
    }

    if (!anoValido(ano)) { 
        return false;
    }

    if (!precoValido(preco)) {
        return false;
    }
    return true;
}