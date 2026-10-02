#ifndef CADASTRO_VEICULOS_HPP
#define CADASTRO_VEICULOS_HPP

#include <string>
#include <vector>
#include "Veiculo.hpp"

class Cadastro_Veiculos{
private:
  std::vector<Veiculo> veiculos;

public:
  bool cadastrar_Veiculo(const Veiculo& veiculo);
  bool placa_Cadastrada(const std::string& placa) const;
  const Veiculo* buscar_Veiculos(const std::string& placa) const;
  bool atualizar_Veiculo(const std::string& placa, const Veiculo& new_Dados);
  const std::vector<Veiculo>& listar_Veiculos() const;
};

#endif
