#ifndef GERENCIAMENTODECLIENTES_HPP
#define GERENCIAMENTODECLIENTES_HPP
#include <iostream>
#include <string>

   
    class GerenciamentoDeClientes {
        private:
    int idCliente;

        public:
        GerenciamentoDeClientes(std::string nome, std::string email, std::string cpf);
        ~GerenciamentoDeClientes();
/**
* @brief mostrarClientes é um método que imprime uma lista com todos os clientes cadastrados no sistema.
*/      void mostrarClientes();
    
/**
* @brief cadastrarCliente é um método que cadastra um novo cliente no sistema e valida o email e CPF do cliente antes de adicioná-lo ao sistema.
*/
        void cadastrarCliente(std::string nome, std::string email, std::string cpf);
/**
* @brief alterarNomeCliente é um método que altera o nome de um cliente existente.
*/
        void alterarNomeCliente(int id, std::string novoNome);
        /**
* @brief alterarEmailCliente é um método que altera o email de um cliente existente.
*/
        void alterarEmailCliente(int id, std::string novoEmail);

    };

#endif