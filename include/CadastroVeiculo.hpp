#ifndef CADASTRO_VEICULOS_HPP
#define CADASTRO_VEICULOS_HPP

#include <string>
#include <vector>
#include "Veiculo.hpp"

/**
 * @file CasdastroVeiculo.hpp
 * @brief Declara a classe responsável pelo cadastro dos veículos
 */

/**
 * @class Cadastro_Veiculos
 * @brief Gerenciamento dos veículos da loja
 * 
 * Permite cadastrar, consultar, atualizar e listar os veículos da loja.
 * O cadastro utiliza a placa como identificador,
 * impedindo o cadastro de veículos com a mesma placa.
 */

class Cadastro_Veiculos{
private:
  std::vector<Veiculo> veiculos;

public:
  /**
   * @brief Cadastra um novo veículo
   * @param veiculo Veiculo que será cadastrado
   * @return true se o cadastro for realizado, false caso contrário ou caso os dados sejam inválidos
   */
  bool cadastrar_Veiculo(const Veiculo& veiculo);

  /**
   * @brief Cadastra a placa do veículo
   * @param placa Placa que será consultada
   * @return true se a placa existir, false caso contrário
   */
  bool placa_Cadastrada(const std::string& placa) const;

  /**
   * @brief Consulta os veículos cadastrados por sua placa
   * @param placa Utiliza a placa para conferir se o veículo está cadastrado
   * @return Ponteiro constante para o veículo encontrado ou nullptr caso não exista
   */
  const Veiculo* buscar_Veiculos(const std::string& placa) const;

  /**
   * @brief Atualiza os dados de um veículo cadastrado
   * @param placa Placa que identifica o veículo
   * @param new_Dados Os novos dados que serão cadastrados/atualizados
   * @return true se a atualização seja feita, false caso o veículo não exista ou se os dados forem inválidos
   */
  bool atualizar_Veiculo(const std::string& placa, const Veiculo& new_Dados);

  /**
   * @brief Retorna os veículos cadastrados
   * @return Referência constante para o vetor de veículos
   */
  const std::vector<Veiculo>& listar_Veiculos() const;
};

#endif
