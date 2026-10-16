#ifndef GERENCIAMENTODECLIENTES_HPP
#define GERENCIAMENTODECLIENTES_HPP
#include <iostream>
#include <string>

   
    class GerenciamentoDeClientes {
        private:
    int idCliente = 0;
    std::string nome;
    std::string email;
    std::string cpf;

        private:
        GerenciamentoDeClientes(std::string nome, std::string email, std::string cpf){
            idCliente++;
            // trocar pra integração do Cliente.hpp depois 
            //this->nome = nome;
           //this->email = email;s
            //this->cpf = cpf;
        };
        ~GerenciamentoDeClientes();
/** 
 * @brief getIdCliente é um método que retorna o ID do cliente.
*/
        void getIdCliente() const {
            std::cout << "ID: " << idCliente << std::endl;
        };
/**
* @brief mostrarClientes é um método que imprime uma lista com todos os clientes cadastrados no sistema.
*/      void mostrarClientes() const;
    
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

        bool validarEmail(std::string email);

        bool validarCPF(std::string CPF);

};

#endif