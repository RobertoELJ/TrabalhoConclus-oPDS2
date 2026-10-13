#pragma once

#include <string>
#include "CadastroVeiculo.hpp"

/** @brief Vendedor da loja: cadastra veículos e recebe comissão sobre as vendas. */
class Vendedor {
public:
    /** @brief Cria o vendedor com a comissão em percentual (5 é 5%). */
    Vendedor(const std::string& nome, const std::string& id, double percentualComissao);

    /** @brief Nome do vendedor. */
    std::string getNome() const;

    /** @brief Identificação do vendedor. */
    std::string getId() const;

    /** @brief Percentual de comissão. */
    double getPercentualComissao() const;

    /** @brief Cadastra um veículo no cadastro informado. */
    bool cadastrarVeiculo(Cadastro_Veiculos& cadastro, const Veiculo& veiculo);

    /** @brief Consulta um veículo pela placa. */
    const Veiculo* consultarVeiculo(const Cadastro_Veiculos& cadastro, const std::string& placa) const;

    /** @brief Atualiza os dados de um veículo já cadastrado. */
    bool atualizarVeiculo(Cadastro_Veiculos& cadastro, const std::string& placa, const Veiculo& novosDados);

    /** @brief Comissão sobre o valor de uma venda. */
    double calcularComissao(double valorVenda) const;

private:
    std::string nome_;
    std::string id_;
    double percentualComissao_;
};
