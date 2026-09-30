#ifndef GERENCIADOR_DE_ARQUIVOS_HPP
#define GERENCIADOR_DE_ARQUIVOS_HPP

#include <string>

class GerenciadorDeArquivos {

    private:

    std::string caminho_dos_arq_clientes;
    std::string caminho_dos_arq_produtos;
    std::string caminho_dos_arq_veiculos;
    std::string status_Arquivo;

    public:
    void lerDadosAoIniciar();
    void gravarListasAntesDeFechar();
};

#endif