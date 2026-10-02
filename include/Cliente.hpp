#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <vector>

    ///Cliente é uma classe que gerencia os clientes cadastrados no sistema. Ela possui métodos para validar o email e o CPF dos clientes, além de permitir a alteração do nome de um cliente.
class Cliente {
private:
    std::vector<Cliente> clientes;
public:     
    void validaEmail();
    void validaCPF();
    void alteraNome();
    void alteraEmail();
    void altera();
    void vinculaHistorico();
};

#endif
