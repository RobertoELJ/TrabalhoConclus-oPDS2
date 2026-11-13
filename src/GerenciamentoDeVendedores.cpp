#include "GerenciamentoDeVendedores.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

void GerenciamentoDeVendedores::adicionarVendedor(
    const Vendedor& vendedor
) {
    vendedores.push_back(vendedor);
} 

void GerenciamentoDeVendedores::adicionarVenda(
    const Venda& venda
) {
    vendas.push_back(venda);
}

void GerenciamentoDeVendedores::mostrarVendedores() {
    if (vendedores.empty()) {
        std::cout << "Nenhum vendedor cadastrado.\n";
        return;
    }

    std::cout << "\n===== VENDEDORES CADASTRADOS =====\n";

    for (const Vendedor& vendedor : vendedores) {
        std::cout << "Nome: " << vendedor.getNome() << "\n";
        std::cout << "ID: " << vendedor.getId() << "\n";
        std::cout << "Comissao: "
                  << vendedor.getPercentualComissao()
                  << "%\n";
        std::cout << "-----------------------------\n";
    }
}

void GerenciamentoDeVendedores::mostrarDadosVendas() {
    if (vendas.empty()) {
        std::cout << "Nenhuma venda cadastrada.\n";
        return;
    }

    std::cout << "\n===== DADOS DAS VENDAS =====\n";

    for (const Venda& venda : vendas) {
        std::cout << "Vendedor ID: " << venda.getIdVendedor() << "\n";
        std::cout << "Cliente CPF: " << venda.getCpfCliente() << "\n";
        std::cout << "Data: " << venda.getData() << "\n";
        std::cout << "Valor: R$ " << venda.getValorFinal() << "\n";
        std::cout << "Comissao: R$ " << venda.getComissao() << "\n";

        std::cout << "Situacao: ";

        if (venda.estaCancelada()) {
            std::cout << "Cancelada\n";
        } else if (venda.estaConcluida()) {
            std::cout << "Concluida\n";
        } else {
            std::cout << "Pendente\n";
        }

        std::cout << "-----------------------------\n";
    }
}

void GerenciamentoDeVendedores::filtraDados() {
    std::string idVendedor;

    std::cout << "\n===== FILTRAR VENDAS =====\n";
    std::cout << "Digite o ID do vendedor: ";
    std::cin >> idVendedor;

    bool encontrou = false;

    for (const Venda& venda : vendas) {
        if (venda.getIdVendedor() == idVendedor) {
            std::cout << "\nData: " << venda.getData() << "\n";
            std::cout << "Valor: R$ "
                      << venda.getValorFinal() << "\n";
            std::cout << "Comissao: R$ "
                      << venda.getComissao() << "\n";
            std::cout << "-----------------------------\n";

            encontrou = true;
        }
    }

    if (!encontrou) {
        std::cout << "Nenhuma venda encontrada para esse vendedor.\n";
    }
}

Vendedor* GerenciamentoDeVendedores::buscarVendedor(
    const std::string& id
) {
    for (Vendedor& vendedor : vendedores) {
        if (vendedor.getId() == id) {
            return &vendedor;
        }
    }

    return nullptr;
}

bool GerenciamentoDeVendedores::clientePossuiVendas(
    const std::string& cpf
) const {
    for (const Venda& venda : vendas) {
        if (venda.getCpfCliente() == cpf) {
            return true;
        }
    }

    return false;

  }

bool GerenciamentoDeVendedores::possuiVendas() const {
    return !vendas.empty();
}
std::vector<std::string> GerenciamentoDeVendedores::paraLinhas() const {
    std::vector<std::string> linhas;

    for (const Vendedor& vendedor : vendedores) {
        std::string linha =
            vendedor.getNome() + ";" +
            vendedor.getId() + ";" +
            std::to_string(vendedor.getPercentualComissao());

        linhas.push_back(linha);
    }

    return linhas;
}
void GerenciamentoDeVendedores::carregarDeLinhas(
    const std::vector<std::string>& linhas
) {
    if (possuiVendas()) {
        throw std::invalid_argument(
            "Nao e possivel recarregar vendedores enquanto houver vendas registradas."
        );
    }

    GerenciamentoDeVendedores temporario;

    int numeroLinha = 1;

    for (const std::string& linha : linhas) {
        std::stringstream ss(linha);
        std::vector<std::string> campos;
        std::string campo;

        while (std::getline(ss, campo, ';')) {
            campos.push_back(campo);
        }

        if (campos.size() != 3) {
            throw std::invalid_argument(
                "Linha " + std::to_string(numeroLinha) +
                ": formato invalido de vendedor."
            );
        }

        double percentual = 0.0;

        try {
            std::size_t usados = 0;
            percentual = std::stod(campos[2], &usados);

            if (usados != campos[2].size()) {
                throw std::invalid_argument("Percentual invalido.");
            }
        } catch (const std::exception&) {
            throw std::invalid_argument(
                "Linha " + std::to_string(numeroLinha) +
                ": percentual de comissao invalido."
            );
        }

        if (temporario.buscarVendedor(campos[1]) != nullptr) {
            throw std::invalid_argument(
                "Linha " + std::to_string(numeroLinha) +
                ": ID de vendedor duplicado."
            );
        }

        Vendedor vendedor(campos[0], campos[1], percentual);
        temporario.adicionarVendedor(vendedor);

        numeroLinha++;
    }

    vendedores.swap(temporario.vendedores);
}
std::vector<std::string> GerenciamentoDeVendedores::vendasParaLinhas() const {
    std::vector<std::string> linhas;

    for (const Venda& venda : vendas) {
        linhas.push_back(venda.toLinha());
    }

    return linhas;
}