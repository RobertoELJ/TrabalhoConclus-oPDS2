#ifndef GERENCIAMENTODECLIENTES_CPP
#define GERENCIAMENTODECLIENTES_CPP
#include "GerenciamentoDeClientes.hpp"

bool validarEmail(std::string email) {
    if(email.find('@') == std::string::npos) {
        std::cout << "Email inválido." << std::endl;
        return 1;
    } else if(email.find('.') == std::string::npos) {
        std::cout << "Email inválido." << std::endl;
        return 1;
    } else if(email.find('@') > email.rfind('.')) {
        std::cout << "Email inválido." << std::endl;
        return 1;
    } else if(email.find(' ') != std::string::npos) {
        std::cout << "Email inválido." << std::endl;
        return 1;
    } else return 0;
}

bool validarCPF(std::string CPF) {
    if(CPF.length() != 11) {
        std::cout << "CPF inválido." << std::endl;
        return 1;
    } else return 0;
}

void GerenciamentoDeClientes::cadastrarCliente(std::string nome, std::string email, std::string cpf) {
    this->nome = nome;

    if(GerenciamentoDeClientes::validarEmail(email)) {
        this->email = email;
    }
    if(GerenciamentoDeClientes::validarCPF(cpf)){
        this->cpf = cpf;
    }

}

void GerenciamentoDeClientes::mostrarClientes() const {
   int IdCliente = idCliente;
   
    while(idCliente > 0) {
       std::cout << "ID: " << idCliente << std::endl;
       std::cout << "Nome: " << nome << std::endl;
       std::cout << "Email: " << email << std::endl;
       std::cout << "CPF: " << cpf << std::endl;
       IdCliente--;
   }
}

void GerenciamentoDeClientes::alterarNomeCliente(int id, std::string novoNome) {
    this->nome = novoNome;
}

void GerenciamentoDeClientes::alterarEmailCliente(int id, std::string novoEmail) {
    if(validarEmail(novoEmail)) {
       this->email = novoEmail; 
}
}


#endif