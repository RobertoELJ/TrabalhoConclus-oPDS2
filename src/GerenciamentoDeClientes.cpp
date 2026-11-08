#include "GerenciamentoDeClientes.hpp"

#include <iostream>
#include <stdexcept>
#include <cctype>

<<<<<<< HEAD
GerenciamentoDeClientes::~GerenciamentoDeClientes() {}

namespace {

// fatiador de string padrao usando stringstream
std::vector<std::string> dividirCampos(const std::string& linha) {
    std::vector<std::string> campos;
    std::stringstream ss(linha);
    std::string pedaco;
    
    // corta no ponto e virgula
    while (std::getline(ss, pedaco, ';')) {
        campos.push_back(pedaco);
    }
    return campos;
}

}  // namespace
=======
>>>>>>> 2bee1a0d942f3d931169c670642cb3b331e67cdb

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

<<<<<<< HEAD
std::vector<std::string> GerenciamentoDeClientes::paraLinhas() const {
    std::vector<std::string> linhas;
    // formata pra id;cpf;email usando auto
    for (const auto& cliente : clientes_) {
        linhas.push_back(cliente.getNome() + ";" + cliente.getCpf() + ";" + cliente.getEmail());
    }
    return linhas;
}

void GerenciamentoDeClientes::carregarDeLinhas(const std::vector<std::string>& linhas) {
    GerenciamentoDeClientes temporario(*this); // copia de backup
    
    int numeroLinha = 1;
    for (const auto& linha : linhas) {
        std::string onde = "Linha " + std::to_string(numeroLinha) + " de clientes: ";
        
        auto campos = dividirCampos(linha);
        if (campos.size() != 3) {
            throw std::invalid_argument(onde + "formato invalido (esperado nome;cpf;email).");
        }
        
        try {
            // arrumado! assinatura eh (nome, email, cpf) e txt eh (0=nome, 1=cpf, 2=email)
            temporario.cadastrarCliente(campos[0], campos[2], campos[1]);
        } catch (const std::invalid_argument& erro) {
            throw std::invalid_argument(onde + erro.what());
        }
        numeroLinha++;
    }
    
    // se nao quebrou em nenhuma linha, efetiva a mudanca
    clientes_.swap(temporario.clientes_);
}

void GerenciamentoDeClientes::removerCliente(int id) {
    validarId(id);
    clientes_.erase(clientes_.begin() + (id - 1));
}

Cliente* GerenciamentoDeClientes::buscarCliente(int id) {
    validarId(id);
    // retorna o ponteiro para o cliente; índice id - 1
    return &clientes_[id - 1];
}
=======
>>>>>>> 2bee1a0d942f3d931169c670642cb3b331e67cdb
