#ifndef CLIENTE_CPP
#define CLIENTE_CPP
#include "Cliente.hpp"


std::string Cliente::getNome() const {
    return nome_;
}

std::string Cliente::getCpf() const {
    return cpf_;
} 

std::string Cliente::getEmail() const {
    return email_;
}

void Cliente::alteraNome(const std::string& novoNome) {
    this->nome_ = novoNome;
}

void Cliente::alteraEmail(const std::string& novoEmail) {
    this->email_ = novoEmail;
}

bool Cliente::validaCPF() const {
    
}


#endif