#ifndef GERENCIADOR_DE_ARQUIVOS_HPP
#define GERENCIADOR_DE_ARQUIVOS_HPP

#include <string>
#include <vector>

#include "Estoque.hpp"
#include "GerenciamentoDeClientes.hpp"

/**
 * @brief Classe responsavel por ler e gravar os dados em txt.
 */
class GerenciadorDeArquivos {
private:
    /** @brief caminho do txt do estoque */
    std::string caminhoArquivoEstoque_;

    /** @brief caminho do txt dos clientes */
    std::string caminhoArquivoClientes_;

public:
    /**
     * @brief Construtor do gerenciador.
     * @param pastaDados pasta onde ficam os arquivos (padrao: "data").
     * @throws std::invalid_argument se a pasta for vazia.
     */
    explicit GerenciadorDeArquivos(const std::string& pastaDados = "data");

    /**
     * @brief Cria um arquivo vazio se ele ainda nao existir.
     * @param caminho caminho do arquivo.
     * @throws std::invalid_argument se o caminho for vazio.
     * @throws std::runtime_error se falhar ao criar o arquivo.
     */
    void criarArquivoCasoNaoExista(const std::string& caminho) const;

    /**
     * @brief Le todas as linhas do txt.
     * @param caminho caminho do arquivo.
     * @return vetor de strings com as linhas do txt.
     * @throws std::runtime_error se nao conseguir abrir o arquivo.
     */
    static std::vector<std::string> lerLinhas(const std::string& caminho);

    /**
     * @brief Sobrescreve o arquivo com o conteudo novo.
     * @param caminho caminho do arquivo.
     * @param linhas linhas pra gravar.
     * @throws std::runtime_error se der erro na gravacao.
     */
    static void gravarLinhas(const std::string& caminho, const std::vector<std::string>& linhas);

    /**
     * @brief Salva o estoque no txt (id;descricao;quantidade).
     * @throws std::runtime_error em caso de erro na gravacao.
     */
    void salvarEstoque(const Estoque& estoque) const;

    /**
     * @brief Carrega os dados do txt pro estoque.
     * @throws std::runtime_error se o arquivo nao abrir ou tiver linha invalida.
     */
    void carregarEstoque(Estoque& estoque) const;

    /**
     * @brief Salva os clientes no txt (nome;cpf;email).
     * @throws std::runtime_error em caso de erro na gravacao.
     */
    void salvarClientes(const GerenciamentoDeClientes& clientes) const;

    /**
     * @brief Carrega os dados do txt pra lista de clientes.
     * @throws std::runtime_error se o arquivo nao abrir ou tiver linha invalida.
     */
    void carregarClientes(GerenciamentoDeClientes& clientes) const;

    /**
     * @brief Puxa os dados (estoque e clientes) logo q o programa abre.
     * @throws std::runtime_error se os arquivos estiverem corrompidos.
     */
    void lerDadosAoIniciar(Estoque& estoque, GerenciamentoDeClientes& clientes) const;

    /**
     * @brief Grava tudo nos txts antes do programa fechar.
     * @throws std::runtime_error se falhar ao gravar algo.
     */
    void gravarListasAntesDeFechar(const Estoque& estoque, const GerenciamentoDeClientes& clientes) const;
};

#endif