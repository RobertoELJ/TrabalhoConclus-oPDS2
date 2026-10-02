#ifndef VENDEDOR_HPP
#define VENDEDOR_HPP

#include <string>
#include "CadastroVeiculo.hpp"

/**
 * @file Vendedor.hpp
 * @brief Vendedor da loja: cadastra veículos e recebe comissão sobre vendas.
 */

/**
 * @brief Representa um vendedor.
 *
 * Reconstruído aqui porque o conteúdo original deste arquivo havia sido
 * sobrescrito por engano com a classe Caixa (mesmo include guard CAIXA_HPP
 * usado em include/caixa.hpp, fazendo um dos dois sumir ao incluir os dois
 * juntos). Mantidos os métodos de cadastro de veículo já escritos pelo
 * Matheus, e acrescentada a comissão, que a Venda precisa.
 */
class Vendedor {
public:
    /**
     * @brief Cria um vendedor.
     * @param nome Nome do vendedor.
     * @param id Identificação do vendedor.
     * @param percentualComissao Percentual de comissão sobre cada venda (ex.: 5 significa 5%).
     */
    Vendedor(const std::string& nome, const std::string& id, double percentualComissao);

    /** @brief Nome do vendedor. */
    std::string getNome() const;

    /** @brief Identificação do vendedor. */
    std::string getId() const;

    /** @brief Percentual de comissão do vendedor. */
    double getPercentualComissao() const;

    /** @brief Cadastra um veículo no cadastro informado. */
    bool cadastrarVeiculo(Cadastro_Veiculos& cadastro, const Veiculo& veiculo);

    /** @brief Consulta um veículo pela placa. */
    const Veiculo* consultarVeiculo(const Cadastro_Veiculos& cadastro, const std::string& placa) const;

    /** @brief Atualiza os dados de um veículo já cadastrado. */
    bool atualizarVeiculo(Cadastro_Veiculos& cadastro, const std::string& placa, const Veiculo& novosDados);

    /**
     * @brief Calcula a comissão do vendedor sobre o valor de uma venda.
     * @param valorVenda Valor final da venda.
     * @return Comissão a receber (percentualComissao% de valorVenda).
     */
    double calcularComissao(double valorVenda) const;

private:
    std::string nome_;
    std::string id_;
    double percentualComissao_;
};

#endif
