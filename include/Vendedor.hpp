#ifndef VENDEDOR_HPP
#define VENDEDOR_HPP

#include <string>
#include "CadastroVeiculo.hpp"

class Vendedor{
private:
  std::string nome;
  std::string id;

public:
  Vendedor(const std::string& nome, const std::string& id);
  std::string getNome() const;
  std::string getId() const;
  bool cadastrar_Veiculo(Cadastro_Veiculos& cadastro, const Veiculo& veiculo);
  const Veiculo* consultar_Veiculo(const Cadastro_Veiculos& cadastro, const std::string& placa) const;
  bool atualizar_Veiculo(Cadastro_Veiculos& cadastro, const std::string& placa, const Veiculo& newDados);
};

#endif
