#include <iostream>
#include <string>
#include <limits>

#include "CadastroVeiculo.hpp"
#include "Veiculo.hpp"

using namespace std;

void menuVeiculos(CadastroVeiculos& cadastro) {
    int opcao;

    do {
        cout << "\n===== GERENCIAR VEICULOS =====\n";
        cout << "1 - Cadastrar veiculo\n";
        cout << "2 - Buscar veiculo\n";
        cout << "3 - Atualizar veiculo\n";
        cout << "4 - Listar veiculos\n";
        cout << "0 - Voltar\n";
        cout << "Escolha uma opcao: ";

        if (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcao invalida!\n";
            continue;
        }

        switch (opcao) {
            case 1: {
                string marca, modelo, placa;
                int ano;
                double preco;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Marca: ";
                getline(cin, marca);

                cout << "Modelo: ";
                getline(cin, modelo);

                cout << "Placa: ";
                getline(cin, placa);

                cout << "Ano: ";
                if (!(cin >> ano)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ano invalido!\n";
                    break;
                }

                cout << "Preco: ";
                if (!(cin >> preco)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Preco invalido!\n";
                    break;
                }

                Veiculo veiculo(marca, modelo, placa, ano, preco);

                if (cadastro.cadastrarVeiculo(veiculo)) {
                    cout << "Veiculo cadastrado com sucesso!\n";
                } else {
                    cout << "Erro ao cadastrar veiculo.\n";
                }

                break;
            }

      case 2: {
    string placa;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Digite a placa do veiculo: ";
    getline(cin, placa);

    const Veiculo* veiculo = cadastro.buscarVeiculo(placa);

    if (veiculo != nullptr) {
        cout << "\n===== VEICULO ENCONTRADO =====\n";
        cout << "Marca: " << veiculo->getMarca() << "\n";
        cout << "Modelo: " << veiculo->getModelo() << "\n";
        cout << "Placa: " << veiculo->getPlaca() << "\n";
        cout << "Ano: " << veiculo->getAno() << "\n";
        cout << "Preco: R$ " << veiculo->getPreco() << "\n";
        cout << "Disponibilidade: "
             << (veiculo->estaDisponivel() ? "Disponivel" : "Indisponivel")
             << "\n";
    } else {
        cout << "Veiculo nao encontrado!\n";
    }

    break;
}

case 3: {
    string placa;
    string marca, modelo, novaPlaca;
    int ano;
    double preco;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Digite a placa do veiculo que deseja atualizar: ";
    getline(cin, placa);

    if (cadastro.buscarVeiculo(placa) == nullptr) {
        cout << "Veiculo nao encontrado!\n";
        break;
    }

    cout << "Nova marca: ";
    getline(cin, marca);

    cout << "Novo modelo: ";
    getline(cin, modelo);

    cout << "Nova placa: ";
    getline(cin, novaPlaca);

    cout << "Novo ano: ";
    if (!(cin >> ano)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ano invalido!\n";
        break;
    }

    cout << "Novo preco: ";
    if (!(cin >> preco)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Preco invalido!\n";
        break;
    }

    Veiculo novosDados(marca, modelo, novaPlaca, ano, preco);

    if (cadastro.atualizarVeiculo(placa, novosDados)) {
        cout << "Veiculo atualizado com sucesso!\n";
    } else {
        cout << "Nao foi possivel atualizar o veiculo.\n";
    }

    break;
}

case 4: {
    const vector<Veiculo>& veiculos = cadastro.listarVeiculos();

    if (veiculos.empty()) {
        cout << "Nenhum veiculo cadastrado.\n";
    } else {
        cout << "\n===== VEICULOS CADASTRADOS =====\n";

        for (const Veiculo& veiculo : veiculos) {
            cout << "\nMarca: " << veiculo.getMarca() << "\n";
            cout << "Modelo: " << veiculo.getModelo() << "\n";
            cout << "Placa: " << veiculo.getPlaca() << "\n";
            cout << "Ano: " << veiculo.getAno() << "\n";
            cout << "Preco: R$ " << veiculo.getPreco() << "\n";
            cout << "Disponibilidade: "
                 << (veiculo.estaDisponivel() ? "Disponivel" : "Indisponivel")
                 << "\n";
            cout << "-----------------------------\n";
        }
    }

    break;
}

            case 0:
                cout << "Voltando ao menu principal...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);
}

int main() {
    CadastroVeiculos cadastroVeiculos;
    int opcao;

    do {
        cout << "\n====================================\n";
        cout << "   SISTEMA DE LOJA DE CARROS\n";
        cout << "====================================\n";
        cout << "1 - Gerenciar veiculos\n";
        cout << "2 - Gerenciar estoque\n";
        cout << "3 - Gerenciar clientes\n";
        cout << "4 - Gerenciar vendedores\n";
        cout << "5 - Realizar venda\n";
        cout << "6 - Acessar caixa\n";
        cout << "7 - Relatorios\n";
        cout << "0 - Sair\n";
        cout << "====================================\n";
        cout << "Escolha uma opcao: ";

        if (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcao invalida!\n";
            continue;
        }

        switch (opcao) {
            case 1:
                menuVeiculos(cadastroVeiculos);
                break;

                        case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                cout << "Funcionalidade sera implementada em seguida.\n";
                break;

            case 0:
                cout << "Encerrando o sistema...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);

    return 0;
}