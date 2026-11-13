#include "GerenciadorDeArquivos.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {

// corta a string usando o ponto e virgula
std::vector<std::string> dividirCampos(const std::string& linha) {
    std::vector<std::string> campos;
    std::stringstream ss(linha);
    std::string pedaco;
    
    while (std::getline(ss, pedaco, ';')) {
        campos.push_back(pedaco);
    }
    // lida com o caso do ultimo campo ser vazio (ex: "1;Pneu;")
    if (!linha.empty() && linha.back() == ';') {
        campos.push_back("");
    }
    return campos;
}

// formata a mensagem de erro da linha
std::string descreverLinha(const std::string& caminho, int numeroLinha) {
    return "Arquivo '" + caminho + "', linha " + std::to_string(numeroLinha) + ": ";
}

// converte string pra int garantindo que toda a string foi consumida
int converterInteiro(const std::string& texto, const std::string& onde) {
    std::size_t usados = 0;
    int valor = 0;
    try {
        valor = std::stoi(texto, &usados);
    } catch (const std::exception&) {
        throw std::runtime_error(onde + "id ou quantidade nao e um numero inteiro valido.");
    }
    if (usados != texto.size()) {
        throw std::runtime_error(onde + "id ou quantidade nao e um numero inteiro valido.");
    }
    return valor;
}

}  // namespace

GerenciadorDeArquivos::GerenciadorDeArquivos(const std::string& pastaDados) {
    if (pastaDados.empty()) {
        throw std::invalid_argument("A pasta de dados nao pode ser vazia.");
    }
    
    // garante que o caminho tenha formatacao correta
    std::string barra = (pastaDados.back() == '/' || pastaDados.back() == '\\') ? "" : "/";
    caminhoArquivoEstoque_ = pastaDados + barra + "estoque.txt";
    caminhoArquivoVeiculos_ = pastaDados + barra + "veiculos.txt";
    caminhoArquivoClientes_ = pastaDados + barra + "clientes.txt";
    caminhoArquivoVendedores_ = pastaDados + barra + "vendedores.txt";
}

void GerenciadorDeArquivos::criarArquivoCasoNaoExista(const std::string& caminho) const {
    if (caminho.empty()) {
        throw std::invalid_argument("O caminho do arquivo nao pode ser vazio.");
    }
    
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
        // limpa o '\r' do windows se existir
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

    // trabalha num backup temporario pra preservar a integridade do estoque caso falhe
    Estoque temporario = estoque;
    int numeroLinha = 1;
    
    for (const auto& linha : linhas) {
        std::string onde = descreverLinha(caminhoArquivoEstoque_, numeroLinha);
        auto campos = dividirCampos(linha);
        
        if (campos.size() != 3) {
            throw std::runtime_error(onde + "formato invalido (esperado id;descricao;quantidade).");
        }
        
        int id = converterInteiro(campos[0], onde);
        int quantidade = converterInteiro(campos[2], onde);
        
        try {
            temporario.adicionarProduto(id, campos[1], quantidade);
        } catch (const std::exception& erro) {
            throw std::runtime_error(onde + erro.what());
        }
        
        numeroLinha++;
    }
    estoque = temporario;
}

void GerenciadorDeArquivos::gravarVeiculos(const CadastroVeiculos& cadastro) const {
    std::vector<std::string> linhas;

    for (const Veiculo& veiculo : cadastro.listarVeiculos()) {
        std::ostringstream linha;

        linha << veiculo.getMarca() << ';'
              << veiculo.getModelo() << ';'
              << veiculo.getPlaca() << ';'
              << veiculo.getAno() << ';'
              << veiculo.getPreco() << ';'
              << (veiculo.estaDisponivel() ? 1 : 0);

        linhas.push_back(linha.str());
    }

    gravarLinhas(caminhoArquivoVeiculos_, linhas);
}

void GerenciadorDeArquivos::lerVeiculos(CadastroVeiculos& cadastro) const {
    criarArquivoCasoNaoExista(caminhoArquivoVeiculos_);

    auto linhas = lerLinhas(caminhoArquivoVeiculos_);

    // Carrega primeiro em um cadastro temporario.
    CadastroVeiculos temporario;

    int numeroLinha = 1;

    for (const auto& linha : linhas) {
        std::string onde = descreverLinha(caminhoArquivoVeiculos_, numeroLinha);
        auto campos = dividirCampos(linha);

        if (campos.size() != 6) {
            throw std::runtime_error(
                onde + "formato invalido (esperado marca;modelo;placa;ano;preco;disponivel)."
            );
        }

        int ano = converterInteiro(campos[3], onde);
        int disponibilidade = converterInteiro(campos[5], onde);

        if (disponibilidade != 0 && disponibilidade != 1) {
            throw std::runtime_error(onde + "disponibilidade deve ser 0 ou 1.");
        }

        double preco = 0.0;

        try {
            std::size_t usados = 0;
            preco = std::stod(campos[4], &usados);

            if (usados != campos[4].size()) {
                throw std::invalid_argument("Preco invalido");
            }
        } catch (const std::exception&) {
            throw std::runtime_error(onde + "preco invalido.");
        }

        Veiculo veiculo(
            campos[0],
            campos[1],
            campos[2],
            ano,
            preco
        );

        veiculo.setDisponivel(disponibilidade == 1);

        if (!temporario.cadastrarVeiculo(veiculo)) {
            throw std::runtime_error(
                onde + "veiculo invalido ou placa duplicada."
            );
        }

        numeroLinha++;
    }

    cadastro = temporario;
}
void GerenciadorDeArquivos::gravarClientes(
    const GerenciamentoDeClientes& clientes
) const {
    gravarLinhas(caminhoArquivoClientes_, clientes.paraLinhas());
}
void GerenciadorDeArquivos::lerClientes(
    GerenciamentoDeClientes& clientes,
    const GerenciamentoDeVendedores& vendedores
) const {
    criarArquivoCasoNaoExista(caminhoArquivoClientes_);

    std::vector<std::string> linhas = lerLinhas(caminhoArquivoClientes_);

    clientes.carregarDeLinhas(linhas, vendedores);
}
void GerenciadorDeArquivos::gravarVendedores(
    const GerenciamentoDeVendedores& vendedores
) const {
    gravarLinhas(caminhoArquivoVendedores_, vendedores.paraLinhas());
}
void GerenciadorDeArquivos::lerVendedores(
    GerenciamentoDeVendedores& vendedores
) const {
    criarArquivoCasoNaoExista(caminhoArquivoVendedores_);

    std::vector<std::string> linhas =
        lerLinhas(caminhoArquivoVendedores_);

    vendedores.carregarDeLinhas(linhas);
}