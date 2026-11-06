#include "GerenciadorDeArquivos.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

// namespace anonimo pra esconder os helpers do main
namespace {

// corta a string usando o ponto e virgula
std::vector<std::string> dividirCampos(const std::string& linha) {
    std::vector<std::string> campos;
    std::stringstream ss(linha);
    std::string pedaco;
    
    while (std::getline(ss, pedaco, ';')) {
        campos.push_back(pedaco);
    }
    return campos;
}

// formata a mensagem de erro da linha
std::string descreverLinha(const std::string& caminho, int numeroLinha) {
    return "Arquivo '" + caminho + "', linha " + std::to_string(numeroLinha) + ": ";
}

}  // namespace

GerenciadorDeArquivos::GerenciadorDeArquivos(const std::string& pastaDados) {
    if (pastaDados.empty()) {
        throw std::invalid_argument("A pasta de dados nao pode ser vazia.");
    }
    caminhoArquivoEstoque_ = pastaDados + "/estoque.txt";
}

void GerenciadorDeArquivos::criarArquivoCasoNaoExista(const std::string& caminho) const {
    if (caminho.empty()) {
        throw std::invalid_argument("O caminho do arquivo nao pode ser vazio.");
    }
    
    // c++11 ja aceita a string direto, n precisa do c_str()
    std::ifstream existente(caminho);
    if (existente.good()) {
        return;
    }
    std::ofstream novo(caminho);
    if (!novo.is_open()) {
        throw std::runtime_error("Nao foi possivel criar o arquivo: " + caminho);
    }
}

std::vector<std::string> GerenciadorDeArquivos::lerLinhas(const std::string& caminho) {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo para leitura: " + caminho);
    }
    
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(arquivo, linha)) {
        // limpa o '\r' chato do windows se tiver
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
    if (!arquivo.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo para gravacao: " + caminho);
    }
    
    for (const auto& linha : linhas) {
        arquivo << linha << '\n';
    }
    arquivo.flush();
    if (!arquivo.good()) {
        throw std::runtime_error("Falha ao gravar os dados no arquivo: " + caminho);
    }
}

void GerenciadorDeArquivos::gravarListasAntesDeFechar(const Estoque& estoque) const {
    std::vector<std::string> linhas;
    // montando o formato id;descricao;quantidade
    for (int id : estoque.listarIds()) {
        std::ostringstream linha;
        linha << id << ';' << estoque.getDescricaoProduto(id) << ';' << estoque.buscarProdutoPorId(id);
        linhas.push_back(linha.str());
    }
    gravarLinhas(caminhoArquivoEstoque_, linhas);
}

void GerenciadorDeArquivos::lerDadosAoIniciar(Estoque& estoque) const {
    criarArquivoCasoNaoExista(caminhoArquivoEstoque_);
    auto linhas = lerLinhas(caminhoArquivoEstoque_);

    // backup pro caso de dar pau na metade da leitura do txt
    Estoque temporario = estoque;
    int numeroLinha = 1;
    
    for (const auto& linha : linhas) {
        std::string onde = descreverLinha(caminhoArquivoEstoque_, numeroLinha);
        auto campos = dividirCampos(linha);
        
        if (campos.size() != 3) {
            throw std::runtime_error(onde + "formato invalido (esperado id;descricao;quantidade).");
        }
        
        try {
            // std::stoi eh a forma padrao do c++ (melhor que strtol)
            int id = std::stoi(campos[0]);
            int quantidade = std::stoi(campos[2]);
            temporario.adicionarProduto(id, campos[1], quantidade);
        } catch (const std::invalid_argument&) {
            throw std::runtime_error(onde + "id ou quantidade nao e um numero inteiro valido.");
        } catch (const std::out_of_range&) {
            // manter a mesma mensagem se o stoi estourar pra n quebrar os testes do vpl
            throw std::runtime_error(onde + "id ou quantidade nao e um numero inteiro valido."); 
        } catch (const std::exception& erro) {
            // repassa os erros de negocio
            throw std::runtime_error(onde + erro.what());
        }
        numeroLinha++;
    }
    estoque = temporario;
}