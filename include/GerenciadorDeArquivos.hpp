#ifndef GERENCIADOR_DE_ARQUIVOS_HPP
#define GERENCIADOR_DE_ARQUIVOS_HPP

#include <string>
#include <vector>

#include "Estoque.hpp"

/**
 * @brief Classe responsavel por ler e salvar o estoque no txt.
 */
class GerenciadorDeArquivos {
private:
    /** @brief caminho do txt do estoque */
    std::string caminhoArquivoEstoque_;

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
};

#endif