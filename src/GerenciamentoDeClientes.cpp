#include "GerenciamentoDeClientes.hpp"
#include "GerenciamentoDeVendedores.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

GerenciamentoDeClientes::~GerenciamentoDeClientes() {}

void GerenciamentoDeClientes::validarId(int id) const {
    // garante q o id ta dentro das posicoes validas do vetor
    if (id < 1 || id > static_cast<int>(clientes_.size())) {
        throw std::out_of_range("ID invalido.");
    }
}

void GerenciamentoDeClientes::cadastrarCliente(const std::string& nome, const std::string& email, const std::string& cpf) {
    // busca pra ver se ja tem alguem com o cpf antes de tentar criar
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
   
    clientes_[id - 1].setNome(novoNome);
}

void GerenciamentoDeClientes::alterarEmailCliente(int id, const std::string& novoEmail) {
    validarId(id);
    
    clientes_[id - 1].setEmail(novoEmail);
}

std::vector<std::string> GerenciamentoDeClientes::paraLinhas() const {
    std::vector<std::string> linhas;
    // formata pra id;cpf;email usando auto
    for (const auto& cliente : clientes_) {
        linhas.push_back(cliente.getNome() + ";" + cliente.getCpf() + ";" + cliente.getEmail());
    }
    return linhas;
}

void GerenciamentoDeClientes::carregarDeLinhas(
    const std::vector<std::string>& linhas,
    const GerenciamentoDeVendedores& gerenciamentoVendedores
) {
        if (gerenciamentoVendedores.possuiVendas()) {
        throw std::invalid_argument(
            "Nao e possivel recarregar clientes enquanto houver vendas registradas."
        );
    }
    GerenciamentoDeClientes temporario(*this); // copia de backup
    
    int numeroLinha = 1;
    for (const auto& linha : linhas) {
        std::string onde = "Linha " + std::to_string(numeroLinha) + " de clientes: ";
        
        std::vector<std::string> campos;
        std::stringstream ss(linha);
        std::string pedaco;
        
        while (std::getline(ss, pedaco, ';')) {
            campos.push_back(pedaco);
        }

        if (campos.size() != 3) {
            throw std::invalid_argument(onde + "formato invalido (esperado nome;cpf;email).");
        }
        
        try {
            // assinatura eh (nome, email, cpf) e txt eh (0=nome, 1=cpf, 2=email)
            temporario.cadastrarCliente(campos[0], campos[2], campos[1]);
        } catch (const std::invalid_argument& erro) {
            throw std::invalid_argument(onde + erro.what());
        }
        numeroLinha++;
    }
    
    // se nao quebrou em nenhuma linha, efetiva a mudanca
    clientes_.swap(temporario.clientes_);
}

void GerenciamentoDeClientes::removerCliente(
    int id,
    const GerenciamentoDeVendedores& gerenciamentoVendedores
) {
    validarId(id);

    if (gerenciamentoVendedores.possuiVendas()) {
        throw std::invalid_argument(
            "Nao e possivel remover clientes enquanto houver vendas registradas."
        );
    }

    clientes_.erase(clientes_.begin() + (id - 1));
}

Cliente* GerenciamentoDeClientes::buscarCliente(int id) {
    validarId(id);
    // retorna o ponteiro para o cliente; índice id - 1
    return &clientes_[id - 1];
}