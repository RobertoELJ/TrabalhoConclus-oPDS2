#ifndef GERENCIADOR_DE_ARQUIVOS_HPP
#define GERENCIADOR_DE_ARQUIVOS_HPP

#include <string>
//suzane ferreira
/**
 @brief Classe responsável pela persistência dos dados do sistema.

Realiza a leitura e gravação dos dados de clientes, produtos e veículos
em arquivos de texto (.txt) para que nenhuma informação seja perdida ao fechar o programa.
 */
class GerenciadorDeArquivos {
private:
    /** @brief Caminho para o arquivo de texto onde os dados dos clientes são salvos. */
    std::string caminhoArquivoClientes;
    
    /** @brief Caminho para o arquivo de texto onde os dados dos produtos são salvos. */
    std::string caminhoArquivoProdutos;
    
    /** @brief Caminho para o arquivo de texto onde os dados dos veículos são salvos. */
    std::string caminhoArquivoVeiculos;
    
    /** @brief Status atual do arquivo (ex: aberto, fechado, erro de leitura). */
    std::string statusArquivo;

public:
    /**
    @brief Lê os dados armazenados nos arquivos ao iniciar o programa.
    
    Carrega as informações antigas de volta para a memória do sistema.
     */
    void lerDadosAoIniciar();

    /**
     * @brief Grava as listas atualizadas de clientes, veículos e produtos antes de o programa fechar.
     */
    void gravarListasAntesDeFechar();

    /**
    @brief Verifica a existência de um arquivo e cria um novo em branco caso ele não exista.
    @param nomeDoArquivo Caminho ou nome do arquivo de texto que deve ser verificado e criado.
     */
    void criarArquivoCasoNaoExista(std::string nomeDoArquivo);
};

#endif