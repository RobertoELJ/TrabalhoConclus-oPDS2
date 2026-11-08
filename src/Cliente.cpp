#include "Cliente.hpp"
#include <stdexcept>
#include <cctype>

// O Construtor delega a atribuição para os Setters. 
// Isso garante que a validação rode já na criação do objeto!
Cliente::Cliente(const std::string& nome, const std::string& cpf, const std::string& email) {
    setNome(nome);
    setCPF(cpf);
    setEmail(email);
}

std::string Cliente::getNome() const { return nome_; }
std::string Cliente::getCpf() const { return cpf_; } 
std::string Cliente::getEmail() const { return email_; }

void Cliente::setNome(const std::string& novoNome) {
    // Barricada: impede nomes vazios ou com quebra de linha/ponto e vírgula
    if (novoNome.empty() || novoNome.find_first_of(";\r\n") != std::string::npos) {
        throw std::invalid_argument("Nome invalido.");
    }
    this->nome_ = novoNome;
}

void Cliente::setCPF(const std::string& novoCPF) {
    // Garante que o CPF tenha 11 digitos e que só tenha números
    if (novoCPF.length() != 11) {
        throw std::invalid_argument("CPF deve ter exatamente 11 dígitos.");
    }
    for (char c : novoCPF) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            throw std::invalid_argument("CPF deve conter apenas dígitos.");
        }
    }
    this->cpf_ = novoCPF;
}

void Cliente::setEmail(const std::string& novoEmail) {
    // Barricada: validações rigorosas de formato de e-mail
    if (novoEmail.empty()) {
        throw std::invalid_argument("Email não pode ser vazio.");
    }
    if (novoEmail.front() == '@' || novoEmail.back() == '.') {
        throw std::invalid_argument("Email com formato inicial/final inválido.");
    }
    if (novoEmail.find(' ') != std::string::npos || novoEmail.find_first_of(";\r\n\t") != std::string::npos) {
        throw std::invalid_argument("Email contém caracteres não permitidos.");
    }
    
    auto pos_arroba = novoEmail.find('@');
    if (pos_arroba == std::string::npos || novoEmail.find('@', pos_arroba + 1) != std::string::npos) {
        throw std::invalid_argument("Email deve conter exatamente um '@'.");
    }
    
    auto pos_ponto = novoEmail.rfind('.');
    if (pos_ponto == std::string::npos || pos_ponto <= pos_arroba + 1) {
        throw std::invalid_argument("Email deve conter um domínio válido após o '@'.");
    }

    this->email_ = novoEmail; 
}