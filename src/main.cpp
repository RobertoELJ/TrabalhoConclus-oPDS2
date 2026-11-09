#include <iostream>
#include <string>
#include <limits>

#include "CadastroVeiculo.hpp"
#include "Veiculo.hpp"
#include "GerenciamentoDeVendedores.hpp"
#include "GerenciamentoDeClientes.hpp"
#include "Estoque.hpp"
#include "Carrinho.hpp"
#include "Venda.hpp"
#include "Caixa.hpp"
#include "Dinheiro.hpp"
#include "GerenciadorDeArquivos.hpp"

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

void menuVendedores(GerenciamentoDeVendedores& gerenciamento) {
    int opcao = -1;

    do {
        cout << "\n===== GERENCIAR VENDEDORES =====\n";
        cout << "1 - Cadastrar vendedor\n";
        cout << "2 - Listar vendedores\n";
        cout << "3 - Mostrar dados das vendas\n";
        cout << "4 - Filtrar vendas por vendedor\n";
        cout << "0 - Voltar\n";
        cout << "Escolha uma opcao: ";

        if (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcao invalida!\n";
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1: {
                string nome, id;
                double percentualComissao;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Nome do vendedor: ";
                getline(cin, nome);

                cout << "ID do vendedor: ";
                getline(cin, id);

                cout << "Percentual de comissao: ";
                if (!(cin >> percentualComissao)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Percentual invalido!\n";
                    break;
                }

                if (nome.empty() || id.empty() ||
                    percentualComissao < 0 || percentualComissao > 100) {
                    cout << "Dados do vendedor invalidos!\n";
                    break;
                }

                Vendedor vendedor(nome, id, percentualComissao);
                gerenciamento.adicionarVendedor(vendedor);

                cout << "Vendedor cadastrado com sucesso!\n";
                break;
            }

            case 2:
                gerenciamento.mostrarVendedores();
                break;

            case 3:
                gerenciamento.mostrarDadosVendas();
                break;

            case 4:
                gerenciamento.filtraDados();
                break;

            case 0:
                cout << "Voltando ao menu principal...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
                break;
        }

    } while (opcao != 0);
}

void menuClientes(
    GerenciamentoDeClientes& gerenciamento,
    const GerenciamentoDeVendedores& gerenciamentoVendedores
) {
    int opcao = -1;

    do {
        cout << "\n===== GERENCIAR CLIENTES =====\n";
        cout << "1 - Cadastrar cliente\n";
        cout << "2 - Listar clientes\n";
        cout << "3 - Alterar nome do cliente\n";
        cout << "4 - Alterar email do cliente\n";
        cout << "5 - Remover cliente\n";
        cout << "0 - Voltar\n";
        cout << "Escolha uma opcao: ";

        if (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcao invalida!\n";
            opcao = -1;
            continue;
        }

        switch (opcao) {
          case 1: {
    string nome, email, cpf;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nome do cliente: ";
    getline(cin, nome);

    cout << "Email do cliente: ";
    getline(cin, email);

    cout << "CPF do cliente: ";
    getline(cin, cpf);

    try {
        gerenciamento.cadastrarCliente(nome, email, cpf);
        cout << "Cliente cadastrado com sucesso!\n";
    } catch (const std::exception& erro) {
        cout << "Erro ao cadastrar cliente: " << erro.what() << "\n";
    }

    break;
}

  case 3: {
    int id;
    string novoNome;

    cout << "Digite o ID do cliente: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ID invalido!\n";
        break;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Digite o novo nome: ";
    getline(cin, novoNome);

    try {
        gerenciamento.alterarNomeCliente(id, novoNome);
        cout << "Nome alterado com sucesso!\n";
    } catch (const std::exception& erro) {
        cout << "Erro ao alterar nome: " << erro.what() << "\n";
    }

    break;
}

case 4: {
    int id;
    string novoEmail;

    cout << "Digite o ID do cliente: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ID invalido!\n";
        break;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Digite o novo email: ";
    getline(cin, novoEmail);

    try {
        gerenciamento.alterarEmailCliente(id, novoEmail);
        cout << "Email alterado com sucesso!\n";
    } catch (const std::exception& erro) {
        cout << "Erro ao alterar email: " << erro.what() << "\n";
    }

    break;
}

case 5: {
    int id;

    cout << "Digite o ID do cliente que deseja remover: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ID invalido!\n";
        break;
    }

    try {
     gerenciamento.removerCliente(id, gerenciamentoVendedores);
        cout << "Cliente removido com sucesso!\n";
    } catch (const std::exception& erro) {
        cout << "Erro ao remover cliente: " << erro.what() << "\n";
    }

    break;
}

            case 2:
                gerenciamento.mostrarClientes();
                break;

            case 0:
                cout << "Voltando ao menu principal...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
                break;
        }

    } while (opcao != 0);
}
void menuEstoque(Estoque& estoque) {
    int opcao = -1;

    do {
        cout << "\n===== GERENCIAR ESTOQUE =====\n";
        cout << "1 - Adicionar produto\n";
        cout << "2 - Consultar produto por ID\n";
        cout << "3 - Listar produtos\n";
        cout << "4 - Dar baixa na quantidade\n";
        cout << "5 - Verificar produto esgotado\n";
        cout << "6 - Mostrar total de itens\n";
        cout << "0 - Voltar\n";
        cout << "Escolha uma opcao: ";

        if (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcao invalida!\n";
            opcao = -1;
            continue;
        }

        switch (opcao) {
      case 1: {
    int id, quantidade;
    string descricao;

    cout << "Digite o ID do produto: ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ID invalido!\n";
        break;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Digite a descricao do produto: ";
    getline(cin, descricao);

    cout << "Digite a quantidade: ";
    if (!(cin >> quantidade)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Quantidade invalida!\n";
        break;
    }

    try {
        estoque.adicionarProduto(id, descricao, quantidade);
        cout << "Produto adicionado ao estoque com sucesso!\n";
    } catch (const std::exception& erro) {
        cout << "Erro ao adicionar produto: " << erro.what() << "\n";
    }

    break;
}

case 2: {
    int id;

    cout << "Digite o ID do produto: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ID invalido!\n";
        break;
    }

    try {
        cout << "\n===== PRODUTO ENCONTRADO =====\n";
        cout << "ID: " << id << "\n";
        cout << "Descricao: " << estoque.getDescricaoProduto(id) << "\n";
        cout << "Quantidade: " << estoque.buscarProdutoPorId(id) << "\n";

    } catch (const std::exception& erro) {
        cout << "Erro ao consultar produto: " << erro.what() << "\n";
    }

    break;
}

case 3: {
    vector<int> ids = estoque.listarIds();

    if (ids.empty()) {
        cout << "Nenhum produto cadastrado no estoque.\n";
        break;
    }

    cout << "\n===== PRODUTOS EM ESTOQUE =====\n";

    for (int id : ids) {
        cout << "ID: " << id << "\n";
        cout << "Descricao: " << estoque.getDescricaoProduto(id) << "\n";
        cout << "Quantidade: " << estoque.buscarProdutoPorId(id) << "\n";
        cout << "-----------------------------\n";
    }

    break;
}

case 4: {
    int id, quantidade;

    cout << "Digite o ID do produto: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ID invalido!\n";
        break;
    }

    cout << "Digite a quantidade que deseja retirar: ";

    if (!(cin >> quantidade)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Quantidade invalida!\n";
        break;
    }

    try {
        estoque.darBaixaQuantidade(id, quantidade);
        cout << "Baixa realizada com sucesso!\n";
        cout << "Quantidade restante: "
             << estoque.buscarProdutoPorId(id) << "\n";

    } catch (const std::exception& erro) {
        cout << "Erro ao dar baixa: " << erro.what() << "\n";
    }

    break;
}

case 5: {
    int id;

    cout << "Digite o ID do produto: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ID invalido!\n";
        break;
    }

    try {
        if (estoque.alertarProdutoEsgotado(id)) {
            cout << "ATENCAO: Produto esgotado!\n";
        } else {
            cout << "Produto disponivel no estoque.\n";
            cout << "Quantidade: "
                 << estoque.buscarProdutoPorId(id) << "\n";
        }

    } catch (const std::exception& erro) {
        cout << "Erro ao verificar produto: " << erro.what() << "\n";
    }

    break;
}

case 6: {
    long long total = estoque.getTotalItens();

    cout << "\n===== TOTAL DO ESTOQUE =====\n";
    cout << "Total de unidades em estoque: " << total << "\n";

    break;
}

            case 0:
                cout << "Voltando ao menu principal...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
                break;
        }

    } while (opcao != 0);
}
void menuVendas(
    CadastroVeiculos& cadastroVeiculos,
    GerenciamentoDeClientes& gerenciamentoClientes,
    GerenciamentoDeVendedores& gerenciamentoVendedores
) {
    int opcao = -1;

    do {
        cout << "\n===== REALIZAR VENDA =====\n";
        cout << "1 - Iniciar nova venda\n";
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
    int idCliente;

    cout << "\nDigite o ID do cliente: ";

    if (!(cin >> idCliente)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ID invalido!\n";
        break;
    }

    try {
    Cliente* cliente = gerenciamentoClientes.buscarCliente(idCliente);

    cout << "\nCliente encontrado!\n";
    cout << "Nome: " << cliente->getNome() << "\n";
    cout << "CPF: " << cliente->getCpf() << "\n";
    string idVendedor;

cout << "\nDigite o ID do vendedor: ";
cin >> idVendedor;

Vendedor* vendedor = gerenciamentoVendedores.buscarVendedor(idVendedor);

if (vendedor == nullptr) {
    cout << "Vendedor nao encontrado!\n";
    break;
}

cout << "\nVendedor encontrado!\n";
cout << "Nome: " << vendedor->getNome() << "\n";
cout << "ID: " << vendedor->getId() << "\n";
string placa;

cout << "\nDigite a placa do veiculo: ";
cin >> placa;

const Veiculo* veiculo = cadastroVeiculos.buscarVeiculo(placa);

if (veiculo == nullptr) {
    cout << "Veiculo nao encontrado!\n";
    break;
}

if (!veiculo->estaDisponivel()) {
    cout << "Este veiculo nao esta disponivel para venda!\n";
    break;
}

cout << "\nVeiculo encontrado!\n";
cout << "Marca: " << veiculo->getMarca() << "\n";
cout << "Modelo: " << veiculo->getModelo() << "\n";
cout << "Placa: " << veiculo->getPlaca() << "\n";
cout << "Preco: R$ " << veiculo->getPreco() << "\n";
Carrinho carrinho;

carrinho.adicionarVeiculo(*veiculo);

cout << "\n===== RESUMO DO CARRINHO =====\n";
cout << "Veiculo: " << veiculo->getMarca()
     << " " << veiculo->getModelo() << "\n";
cout << "Placa: " << veiculo->getPlaca() << "\n";
cout << "Total: R$ " << carrinho.calcularTotal() << "\n";
Venda venda(cliente, vendedor, carrinho);

cout << "\nVenda preparada com sucesso!\n";
cout << "Aguardando pagamento...\n";
double valorPago;

cout << "\n===== PAGAMENTO EM DINHEIRO =====\n";
cout << "Total da venda: R$ " << carrinho.calcularTotal() << "\n";
cout << "Digite o valor pago pelo cliente: R$ ";

if (!(cin >> valorPago)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Valor de pagamento invalido!\n";
    break;
}

if (valorPago < carrinho.calcularTotal()) {
    cout << "Pagamento insuficiente! Venda nao finalizada.\n";
    break;
}

cout << "Valor recebido: R$ " << valorPago << "\n";
Dinheiro pagamento(0.0, valorPago);

cout << "\nForma de pagamento: "
     << pagamento.descricao() << "\n";
     Caixa caixa;

caixa.iniciarVenda(&venda);
caixa.selecionarFormaPagamento(&pagamento);
caixa.finalizarVenda();
if (!venda.estaConcluida()) {
    cout << "Venda nao concluida. O veiculo continua disponivel.\n";
    break;
}

cout << "\nPagamento confirmado! Venda concluida.\n";
Veiculo veiculoAtualizado = *veiculo;
veiculoAtualizado.setDisponivel(false);

if (!cadastroVeiculos.atualizarVeiculo(placa, veiculoAtualizado)) {
    cout << "ERRO: Nao foi possivel atualizar o veiculo!\n";
    break;
}

cout << "Veiculo marcado como vendido!\n";
gerenciamentoVendedores.adicionarVenda(venda);

cout << "Venda registrada no historico com sucesso!\n";
cout << "Valor final: R$ " << venda.getValorFinal() << "\n";
cout << "Comissao do vendedor: R$ " << venda.getComissao() << "\n";


} catch (const std::exception& erro) {
    cout << "Erro ao buscar cliente: " << erro.what() << "\n";
}

    break;
}

            case 0:
                cout << "Voltando ao menu principal...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
                break;
        }

    } while (opcao != 0);
}

int main() {
    CadastroVeiculos cadastroVeiculos;
    GerenciamentoDeVendedores gerenciamentoVendedores;
    GerenciamentoDeClientes gerenciamentoClientes;
    Estoque estoque;

    GerenciadorDeArquivos arquivos("data");
    try {
        arquivos.lerDadosAoIniciar(estoque);
    } catch (const std::exception& erro) {
        cout << "Erro ao iniciar leitura dos dados: " << erro.what() << "\n";
    }

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
                menuEstoque(estoque);
                break;
            
            case 5:
                menuVendas(
                    cadastroVeiculos,
                    gerenciamentoClientes,
                    gerenciamentoVendedores
                );
                break;

            case 6:
            case 7:
                cout << "Funcionalidade sera implementada em seguida.\n";
                break;

            case 3:
                menuClientes(gerenciamentoClientes, gerenciamentoVendedores);
                break;
            
            case 4:
                menuVendedores(gerenciamentoVendedores);
                break;

            case 0:
                cout << "Encerrando o sistema...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
                break;
        }

    } while (opcao != 0);

    //salva o estoque antes de encerrar no return 0
    try {
        arquivos.gravarListasAntesDeFechar(estoque);
    } catch (const std::exception& erro) {
        cout << "Erro ao gravar dados antes de fechar: " << erro.what() << "\n";
    }

    return 0;
}