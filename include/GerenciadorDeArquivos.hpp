#ifndef GERENCIADOR_DE_ARQUIVOS_HPP
#define GERENCIADOR_DE_ARQUIVOS_HPP

#include <string>
#include <vector>
#include "Estoque.hpp"
#include "CadastroVeiculo.hpp"
#include "GerenciamentoDeClientes.hpp"
#include "GerenciamentoDeVendedores.hpp"

/**
 * @brief Classe responsavel por ler e salvar o estoque no txt.
 */
class GerenciadorDeArquivos {
private:
    /** @brief caminho do txt do estoque */
    std::string caminhoArquivoEstoque_;
/** @brief Caminho do arquivo de cadastro dos veiculos. */
    std::string caminhoArquivoVeiculos_;
    /** @brief Caminho do arquivo de cadastro dos clientes. */
std::string caminhoArquivoClientes_;
/** @brief Caminho do arquivo de cadastro dos vendedores. */
std::string caminhoArquivoVendedores_;
public:
    /**
     * @brief Construtor do gerenciador.
     * @param pastaDados pasta onde fica o arquivo (padrao: "data").
     * @throws std::invalid_argument se a pasta for vazia.
     */
    explicit GerenciadorDeArquivos(const std::string& pastaDados = "data");

    /**
     * @brief Cria um arquivo vazio se ele ainda nao existir.
     * @param caminho caminho do arquivo.
     * @throws std::invalid_argument se o caminho for vazio.
     * @throws std::runtime_error se nao der pra criar.
     */
    void criarArquivoCasoNaoExista(const std::string& caminho) const;

    /**
     * @brief Le todas as linhas do txt.
     * @param caminho caminho do arquivo.
     * @return vetor com as linhas do arquivo.
     * @throws std::runtime_error se nao der pra abrir o arquivo.
     */
    static std::vector<std::string> lerLinhas(const std::string& caminho);

    /**
     * @brief Salva as linhas no arquivo, sobrescrevendo tudo.
     * @param caminho caminho do arquivo.
     * @param linhas linhas pra gravar.
     * @throws std::runtime_error se nao der pra abrir ou gravar.
     */
    static void gravarLinhas(const std::string& caminho, const std::vector<std::string>& linhas);

    /**
     * @brief Carrega o estoque a partir do txt.
     * @param estoque referencia pro estoque.
     * @throws std::runtime_error se o arquivo nao abrir ou tiver linha zuada.
     */
    void lerDadosAoIniciar(Estoque& estoque) const;

    /**
     * @brief Salva todo o estoque atual no txt antes do programa fechar.
     * @param estoque estoque pra salvar.
     * @throws std::runtime_error se falhar ao gravar.
     */
    void gravarListasAntesDeFechar(const Estoque& estoque) const;
    /**
 * @brief Salva os veiculos cadastrados no arquivo veiculos.txt.
 * @param cadastro Cadastro de veiculos da loja.
 */
void gravarVeiculos(const CadastroVeiculos& cadastro) const;


/**
 * @brief Carrega os veiculos salvos no arquivo veiculos.txt.
 * @param cadastro Cadastro de veiculos que recebera os dados.
 */
void lerVeiculos(CadastroVeiculos& cadastro) const;
/**
 * @brief Salva os clientes cadastrados no arquivo clientes.txt.
 * @param clientes Gerenciamento de clientes da loja.
 */
void gravarClientes(const GerenciamentoDeClientes& clientes) const;
/**
 * @brief Carrega os clientes salvos no arquivo clientes.txt.
 * @param clientes Gerenciamento de clientes que recebera os dados.
 * @param vendedores Gerenciamento de vendedores usado para proteger
 *                   as referencias das vendas existentes.
 */
void lerClientes(
    GerenciamentoDeClientes& clientes,
    const GerenciamentoDeVendedores& vendedores
) const;
/**
 * @brief Salva os vendedores cadastrados no arquivo vendedores.txt.
 * @param vendedores Gerenciamento de vendedores da loja.
 */
    void gravarVendedores(
        const GerenciamentoDeVendedores& vendedores
    ) const;

    /**
     * @brief Carrega os vendedores salvos no arquivo vendedores.txt.
     * @param vendedores Gerenciamento de vendedores que recebera os dados.
     */
    void lerVendedores(
        GerenciamentoDeVendedores& vendedores
    ) const;
};

#endif