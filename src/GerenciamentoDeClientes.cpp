#include "GerenciamentoDeClientes.hpp"
#include <iostream>
#include <stdexcept>
#include <cctype>

bool GerenciamentoDeClientes::validarEmail(const std::string& email) const {
    if (email.empty()) return false;
    if (email.front() == '@') return false;
    if (email.find('@') == std::string::npos) return false;
    if (email.find('.') == std::string::npos) return false;
    if (email.find('@') > email.rfind('.')) return false;
    if (email.find(' ') != std::string::npos) return false;
    return true;
}

bool GerenciamentoDeClientes::validarCPF(const std::string& CPF) const {
    if (CPF.length() != 11) return false;
    for (char c : CPF) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

void GerenciamentoDeClientes::cadastrarCliente(const std::string& nome, const std::string& email, const std::string& cpf) {
    if (nome.empty()) {
        throw std::invalid_argument("Nome invalido.");
    }
    if (!validarEmail(email)) {
        throw std::invalid_argument("Email invalido.");
    }
    if (!validarCPF(cpf)) {
        throw std::invalid_argument("CPF invalido.");
    }
    
    for (const auto& cliente : clientes_) {
        if (cliente.getCpf() == cpf) {
            throw std::invalid_argument("CPF ja cadastrado.");
        }
    }

    clientes_.push_back(Cliente(nome, cpf, email));
}

int GerenciamentoDeClientes::getQuantidadeClientes() const {
    return static_cast<int>(clientes_.size());
}

void GerenciamentoDeClientes::mostrarClientes() const {
    if (clientes_.empty()) {
        std::cout << "Nenhum cliente cadastrado." << std::endl;
        return;
    }

    for (size_t i = 0; i < clientes_.size(); ++i) {
        std::cout << "ID: " << i + 1 << std::endl;
        std::cout << "Nome: " << clientes_[i].getNome() << std::endl;
        std::cout << "Email: " << clientes_[i].getEmail() << std::endl;
        std::cout << "CPF: " << clientes_[i].getCpf() << std::endl;
    }
}

void GerenciamentoDeClientes::alterarNomeCliente(int id, const std::string& novoNome) {
    if (id < 1 || id > static_cast<int>(clientes_.size())) {
        throw std::out_of_range("ID invalido.");
    }
    if (novoNome.empty()) {
        throw std::invalid_argument("Nome invalido.");
    }
    clientes_[id - 1].alteraNome(novoNome);
}

void GerenciamentoDeClientes::alterarEmailCliente(int id, const std::string& novoEmail) {
    if (id < 1 || id > static_cast<int>(clientes_.size())) {
        throw std::out_of_range("ID invalido.");
    }
    if (!validarEmail(novoEmail)) {
        throw std::invalid_argument("Email invalido.");
    }
    clientes_[id - 1].alteraEmail(novoEmail);
}