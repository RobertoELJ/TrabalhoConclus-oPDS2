#include "GerenciamentoDeClientes.hpp"

#include <iostream>
#include <stdexcept>
#include <cctype>


bool GerenciamentoDeClientes::nomeValido(const std::string& nome) const {
    return !nome.empty() && nome.find_first_of(";\r\n") == std::string::npos;
}

void GerenciamentoDeClientes::validarId(int id) const {
    // garante q o id ta dentro das posicoes validas do vetor
    if (id < 1 || id > static_cast<int>(clientes_.size())) {
        throw std::out_of_range("ID invalido.");
    }
}

bool GerenciamentoDeClientes::validarEmail(const std::string& email) const {
    if (email.empty()) return false;
    
    // nao pode comecar com @ nem terminar com ponto
    if (email.front() == '@' || email.back() == '.') return false;
    if (email.find(' ') != std::string::npos) return false;
    if (email.find_first_of(";\r\n\t") != std::string::npos) return false;
    
    // checa se tem arroba
    auto pos_arroba = email.find('@');
    if (pos_arroba == std::string::npos) return false;
    
    // checa se tem MAIS DE UM arroba
    if (email.find('@', pos_arroba + 1) != std::string::npos) return false;
    
    // checa se tem ponto dps do arroba
    auto pos_ponto = email.rfind('.');
    if (pos_ponto == std::string::npos) return false;
    if (pos_ponto <= pos_arroba + 1) return false;
    
    return true;
}

bool GerenciamentoDeClientes::validarCPF(const std::string& cpf) const {
    if (cpf.length() != 11) return false;
    
    for (char c : cpf) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

void GerenciamentoDeClientes::cadastrarCliente(const std::string& nome, const std::string& email, const std::string& cpf) {
    if (!nomeValido(nome)) throw std::invalid_argument("Nome invalido.");
    if (!validarEmail(email)) throw std::invalid_argument("Email invalido.");
    if (!validarCPF(cpf)) throw std::invalid_argument("CPF invalido.");
    
    // busca pra ver se ja tem alguem com o cpf
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
        std::cout << "Nenhum cliente cadastrado.\n";
        return;
    }

    // printa os clientes com contador bonitinho
    int id = 1;
    for (const auto& cliente : clientes_) {
        std::cout << "ID: " << id++ << "\n"
                  << "Nome: " << cliente.getNome() << "\n"
                  << "Email: " << cliente.getEmail() << "\n"
                  << "CPF: " << cliente.getCpf() << "\n";
    }
}

void GerenciamentoDeClientes::alterarNomeCliente(int id, const std::string& novoNome) {
    validarId(id);
    if (!nomeValido(novoNome)) throw std::invalid_argument("Nome invalido.");
    
    clientes_[id - 1].alteraNome(novoNome);
}

void GerenciamentoDeClientes::alterarEmailCliente(int id, const std::string& novoEmail) {
    validarId(id);
    if (!validarEmail(novoEmail)) throw std::invalid_argument("Email invalido.");
    
    clientes_[id - 1].alteraEmail(novoEmail);
}

