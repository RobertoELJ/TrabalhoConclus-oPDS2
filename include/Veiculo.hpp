#ifndef VEICULO_HPP
#define VEICULO_HPP

#include <string>

/** 
 * @file Veiculo.hpp
 * @brief Declara a classe que representa um veiculo da loja
 */

/**
 * @class Veiculo
 * @brief Armazena e gerencia os dados de um determinado veiculo
 * 
 * Contém informações de identificação (como marca e ano), preço e disponibildade
 * Permite consultar, alterar e validar os dados documentados
 */

class Veiculo{
private:
    std::string marca;
    std::string modelo;
    std::string placa;
    int ano;
    double preco;
    bool disponivel;

public:
    /**
     * @brief Armazena um veículo com os dados informados
     * @param marca Marca do veículo
     * @param modelo Modelo do veículo
     * @param placa Placa de identificação do veículo
     * @param ano Ano de lançamento do veículo
     * @param preco Preço do veículo
     */
    Veiculo(const std::string& marca, const std::string& modelo, const std::string& placa, int ano, double preco);

    /** @brief Retorna a marca do veículo */
    std::string getMarca() const;

    /** @brief Retorna o modelo do veículo */
    std::string getModelo() const;

    /** @brief Retorna a placa de identificação do veículo */
    std::string getPlaca() const;

    /** @brief Retorna o ano de lançamento do veículo */
    int getAno() const;

    /** @brief Retorna o preço do veículo */
    double getPreco() const;

    /** @brief Consulta a disponibilidade do veículo 
     * @return true caso o veículo esteja disponível, false caso o veículo não esteja disponível
    */
    bool Disponivel() const;

    /**
     * @brief Altera a marca do veículo
     * @param newMarca Nova marca
     */
    std::string setMarca(const std::string& newMarca);

    /**
     * @brief Altera o modelo do veículo
     * @param newModelo Novo modelo
     */
    std::string setModelo(const std::string& newModelo);

    /**
     * @brief Altera o ano do veículo
     * @param newAno Novo ano de lançamento
     */
    int setAno(int newAno);

    /**
     * @brief Altera o preço do veículo
     * @param newPreco Novo preço
     */
    double setPreco(double newPreco);

    /**
     * @brief Altera a disponibilidade do veículo
     * @param disp Estado de disponibilidade do veículo
     */
    bool setDisponivel(bool disp);

    /**
     * @brief Verifica a validade dos dados do veículo 
     * @return true caso os dados sejam válidos, false caso contrário
     */
    bool validarDados() const;
};

#endif
