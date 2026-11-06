#include "GerenciadorDeArquivos.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

// namespace anonimo pra esconder os helpers
namespace {

// joga a string num stream e corta pelo ponto e virgula
std::vector<std::string> dividirCampos(const std::string& linha) {
    std::vector<std::string> campos;
    std::stringstream ss(linha);
    std::string pedaco;
    
    while (std::getline(ss, pedaco, ';')) {
        campos.push_back(pedaco);
    }
    return campos;
}

// formata a mensagem de erro bonitinha
std::string descreverLinha(const std::string& caminho, int numeroLinha) {
    return "Arquivo '" + caminho + "', linha " + std::to_string(numeroLinha) + ": ";
}

} // namespace

GerenciadorDeArquivos::GerenciadorDeArquivos(const std::string& pastaDados) {
    if (pastaDados.empty()) {
        throw std::invalid_argument("a pasta nao pode ser vazia.");
    }
    
    // resolve o BO das barras
    std::string barra = (pastaDados.back() == '/' || pastaDados.back() == '\\') ? "" : "/";
    caminhoArquivoEstoque_ = pastaDados + barra + "estoque.txt";
    caminhoArquivoClientes_ = pastaDados + barra + "clientes.txt";
}

void GerenciadorDeArquivos::criarArquivoCasoNaoExista(const std::string& caminho) const {
    if (caminho.empty()) throw std::invalid_argument("caminho vazio.");
    
    // ja usa string direto (c++11)
    std::ifstream existente(caminho);
    if (existente.good()) return;
    
    std::ofstream novo(caminho);
    if (!novo.is_open()) {
        throw std::runtime_error("erro ao criar arquivo: " + caminho);
    }
}

std::vector<std::string> GerenciadorDeArquivos::lerLinhas(const std::string& caminho) {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) throw std::runtime_error("erro ao abrir: " + caminho);
    
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(arquivo, linha)) {
        // limpa o '\r' chato do windows
        if (!linha.empty() && linha.back() == '\r') {
            linha.pop_back();
        }
        if (!linha.empty()) {
            linhas.push_back(linha);
        }
    }
    return linhas;
}

void GerenciadorDeArquivos::gravarLinhas(const std::string& caminho, const std::vector<std::string>& linhas) {
    std::ofstream arquivo(caminho, std::ios::trunc);
    if (!arquivo.is_open()) throw std::runtime_error("erro ao gravar: " + caminho);
    
    // usando auto ao invez de loop com index
    for (const auto& linha : linhas) {
        arquivo << linha << '\n';
    }
}

void GerenciadorDeArquivos::salvarEstoque(const Estoque& estoque) const {
    std::vector<std::string> linhas;
    auto ids = estoque.listarIds();
    
    for (int id : ids) {
        std::ostringstream linha;
        linha << id << ';' << estoque.getDescricaoProduto(id) << ';' << estoque.buscarProdutoPorId(id);
        linhas.push_back(linha.str());
    }
    gravarLinhas(caminhoArquivoEstoque_, linhas);
}

void GerenciadorDeArquivos::carregarEstoque(Estoque& estoque) const {
    criarArquivoCasoNaoExista(caminhoArquivoEstoque_);
    auto linhas = lerLinhas(caminhoArquivoEstoque_);

    Estoque temporario = estoque; // faz backup caso quebre no meio
    
    int numeroLinha = 1;
    for (const auto& linha : linhas) {
        std::string onde = descreverLinha(caminhoArquivoEstoque_, numeroLinha);
        auto campos = dividirCampos(linha);
        
        if (campos.size() != 3) {
            throw std::runtime_error(onde + "formato errado (tem q ser id;nome;qtd).");
        }
        
        try {
            // std::stoi eh muito melhor que aquele strtol tenebroso
            int id = std::stoi(campos[0]);
            int qtd = std::stoi(campos[2]);
            temporario.adicionarProduto(id, campos[1], qtd);
        } catch (const std::invalid_argument&) {
            throw std::runtime_error(onde + "id ou quantidade nao sao numeros.");
        } catch (const std::out_of_range&) {
            throw std::runtime_error(onde + "numero extrapolou o limite do int.");
        } catch (const std::exception& erro) {
            // pega regras de negocio do adicionarProduto
            throw std::runtime_error(onde + erro.what());
        }
        numeroLinha++;
    }
    estoque = temporario;
}

void GerenciadorDeArquivos::salvarClientes(const GerenciamentoDeClientes& clientes) const {
    gravarLinhas(caminhoArquivoClientes_, clientes.paraLinhas());
}

void GerenciadorDeArquivos::carregarClientes(GerenciamentoDeClientes& clientes) const {
    criarArquivoCasoNaoExista(caminhoArquivoClientes_);
    auto linhas = lerLinhas(caminhoArquivoClientes_);
    try {
        clientes.carregarDeLinhas(linhas);
    } catch (const std::exception& erro) {
        throw std::runtime_error("erro no " + caminhoArquivoClientes_ + ": " + erro.what());
    }
}

void GerenciadorDeArquivos::lerDadosAoIniciar(Estoque& estoque, GerenciamentoDeClientes& clientes) const {
    carregarEstoque(estoque);
    carregarClientes(clientes);
}

void GerenciadorDeArquivos::gravarListasAntesDeFechar(const Estoque& estoque, const GerenciamentoDeClientes& clientes) const {
    salvarEstoque(estoque);
    salvarClientes(clientes);
}