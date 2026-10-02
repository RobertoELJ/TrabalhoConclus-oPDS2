#ifndef VEICULO_HPP
#define VEICULO_HPP

#include <string>

class Veiculo{
private:
    std::string marca;
    std::string modelo;
    std::string placa;
    int ano;
    double preco;
    bool disponivel;

public:
    Veiculo(const std::string& marca, const std::string& modelo, const std::string& placa, int ano, double preco);
    std::string getMarca() const;
    std::string getModelo() const;
    std::string getPlaca() const;
    int getAno() const;
    double getPreco() const;
    bool Disponivel() const;

    std::string setMarca(const std::string& newMarca);
    std::string setModelo(const std::string& newModelo);
    int setAno(int newAno);
    double setPreco(double newPreco);
    bool setDisponivel(bool disp);

    bool validarDados() const;
};

#endif
