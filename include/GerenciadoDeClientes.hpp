#ifndef GERENCIADORDECLIENTES_HPP
#define GERENCIADORDECLIENTES_HPP

#include <vector>


///GerenciadorDeClientes é uma classe que gerencia os clientes cadastrados no sistema. Ela possui métodos para validar o email e o CPF dos clientes, além de permitir a alteração do nome de um cliente.
class GerenciadorDeClientes {
private:
    std::vector<Cliente> clientes;
public:     
    void validaEmail(const std::string& email);
    void validaCPF(const std::string& cpf);
    void alteraNome(const std::string& nome)
};
