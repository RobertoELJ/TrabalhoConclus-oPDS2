#include "doctest.h"
#include "GerenciadorDeArquivos.hpp"

#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>

namespace {

// joga na pasta build pq ela ja costuma ser ignorada pelo git
const char* const PASTA = "build";
const char* const ARQ_ESTOQUE = "build/estoque.txt";

void limparArquivos() {
    std::remove(ARQ_ESTOQUE);
}

// funcao fake p/ injetar os mock tests
void escreverTexto(const std::string& caminho, const std::string& texto) {
    std::ofstream arquivo(caminho, std::ios::binary);
    arquivo << texto;
}

}  // namespace

TEST_CASE("Persistencia: construtor valida a pasta") {
    CHECK_THROWS_AS(GerenciadorDeArquivos(""), std::invalid_argument);
    GerenciadorDeArquivos valido(PASTA);
    CHECK_NOTHROW(valido.criarArquivoCasoNaoExista(ARQ_ESTOQUE));
    limparArquivos();
}

TEST_CASE("Persistencia: criarArquivoCasoNaoExista") {
    limparArquivos();
    GerenciadorDeArquivos gerenciador(PASTA);

    SUBCASE("Cria o arquivo quando nao existe") {
        gerenciador.criarArquivoCasoNaoExista(ARQ_ESTOQUE);
        CHECK(GerenciadorDeArquivos::lerLinhas(ARQ_ESTOQUE).empty());
    }
    SUBCASE("Nao apaga um arquivo que ja existe") {
        escreverTexto(ARQ_ESTOQUE, "1;Pneu;3\n");
        gerenciador.criarArquivoCasoNaoExista(ARQ_ESTOQUE);
        CHECK(GerenciadorDeArquivos::lerLinhas(ARQ_ESTOQUE).size() == 1);
    }
    SUBCASE("Caminho vazio e recusado") {
        CHECK_THROWS_AS(gerenciador.criarArquivoCasoNaoExista(""), std::invalid_argument);
    }
    SUBCASE("Pasta inexistente gera erro") {
        CHECK_THROWS_AS(gerenciador.criarArquivoCasoNaoExista("pasta_que_nao_existe/x.txt"), std::runtime_error);
    }
    limparArquivos();
}

TEST_CASE("Persistencia: lerLinhas e gravarLinhas") {
    limparArquivos();

    SUBCASE("Grava e le de volta") {
        std::vector<std::string> linhas = {"a;b", "c;d"};
        GerenciadorDeArquivos::gravarLinhas(ARQ_ESTOQUE, linhas);
        CHECK(GerenciadorDeArquivos::lerLinhas(ARQ_ESTOQUE) == linhas);
    }
    SUBCASE("Ignora linhas vazias e o retorno de carro do Windows") {
        escreverTexto(ARQ_ESTOQUE, "a;b\r\n\r\nc;d\r\n");
        auto linhas = GerenciadorDeArquivos::lerLinhas(ARQ_ESTOQUE);
        REQUIRE(linhas.size() == 2);
        CHECK(linhas[0] == "a;b");
        CHECK(linhas[1] == "c;d");
    }
    SUBCASE("Ler arquivo inexistente gera erro") {
        CHECK_THROWS_AS(GerenciadorDeArquivos::lerLinhas("build/nao_existe.txt"), std::runtime_error);
    }
    SUBCASE("Gravar em pasta inexistente gera erro") {
        std::vector<std::string> linhas = {"x"};
        CHECK_THROWS_AS(GerenciadorDeArquivos::gravarLinhas("pasta_que_nao_existe/x.txt", linhas),
                        std::runtime_error);
    }
    limparArquivos();
}

TEST_CASE("Persistencia: estoque grava e carrega") {
    limparArquivos();
    GerenciadorDeArquivos gerenciador(PASTA);

    SUBCASE("Ida e volta preserva os dados") {
        Estoque original;
        original.adicionarProduto(2, "Pneu aro 15", 6);
        original.adicionarProduto(7, "Farol", 1);
        gerenciador.gravarListasAntesDeFechar(original);

        Estoque carregado;
        gerenciador.lerDadosAoIniciar(carregado);
        CHECK(carregado.listarIds() == original.listarIds());
        CHECK(carregado.getDescricaoProduto(2) == "Pneu aro 15");
        CHECK(carregado.buscarProdutoPorId(2) == 6);
        CHECK(carregado.buscarProdutoPorId(7) == 1);
    }
    SUBCASE("Arquivo inexistente: cria vazio e deixa o estoque vazio") {
        Estoque estoque;
        CHECK_NOTHROW(gerenciador.lerDadosAoIniciar(estoque));
        CHECK(estoque.listarIds().empty());
        CHECK_NOTHROW(GerenciadorDeArquivos::lerLinhas(ARQ_ESTOQUE));
    }
    SUBCASE("Linha com numero de campos errado") {
        escreverTexto(ARQ_ESTOQUE, "1;Pneu\n");
        Estoque estoque;
        CHECK_THROWS_AS(gerenciador.lerDadosAoIniciar(estoque), std::runtime_error);
    }
    SUBCASE("ID ou quantidade que nao e numero") {
        Estoque estoque;
        escreverTexto(ARQ_ESTOQUE, "abc;Pneu;3\n");
        CHECK_THROWS_AS(gerenciador.lerDadosAoIniciar(estoque), std::runtime_error);
        escreverTexto(ARQ_ESTOQUE, "1;Pneu;3x\n");
        CHECK_THROWS_AS(gerenciador.lerDadosAoIniciar(estoque), std::runtime_error);
        escreverTexto(ARQ_ESTOQUE, "1;Pneu;99999999999999\n"); // estoura o limite
        CHECK_THROWS_AS(gerenciador.lerDadosAoIniciar(estoque), std::runtime_error);
        escreverTexto(ARQ_ESTOQUE, "1;Pneu;\n");
        CHECK_THROWS_AS(gerenciador.lerDadosAoIniciar(estoque), std::runtime_error);
    }
    SUBCASE("Valores que o estoque recusa (quantidade negativa, descricao vazia)") {
        Estoque estoque;
        escreverTexto(ARQ_ESTOQUE, "1;Pneu;-4\n");
        CHECK_THROWS_AS(gerenciador.lerDadosAoIniciar(estoque), std::runtime_error);
        escreverTexto(ARQ_ESTOQUE, "1;;4\n");
        CHECK_THROWS_AS(gerenciador.lerDadosAoIniciar(estoque), std::runtime_error);
    }
    SUBCASE("Erro na segunda linha nao deixa o estoque pela metade") {
        escreverTexto(ARQ_ESTOQUE, "1;Pneu;3\nlinha quebrada\n");
        Estoque estoque;
        CHECK_THROWS_AS(gerenciador.lerDadosAoIniciar(estoque), std::runtime_error);
        CHECK(estoque.listarIds().empty()); // tem q reverter pro padrao
    }
    SUBCASE("A mensagem de erro identifica o arquivo e a linha") {
        escreverTexto(ARQ_ESTOQUE, "1;Pneu;3\nlinha quebrada\n");
        Estoque estoque;
        try {
            gerenciador.lerDadosAoIniciar(estoque);
            FAIL("deveria ter lancado excecao");
        } catch (const std::runtime_error& erro) {
            std::string mensagem = erro.what();
            CHECK(mensagem.find("estoque.txt") != std::string::npos);
            CHECK(mensagem.find("linha 2") != std::string::npos);
        }
    }
    SUBCASE("Salvar em pasta inexistente gera erro") {
        GerenciadorDeArquivos invalido("pasta_que_nao_existe");
        Estoque estoque;
        estoque.adicionarProduto(1, "Pneu", 1);
        CHECK_THROWS_AS(invalido.gravarListasAntesDeFechar(estoque), std::runtime_error);
    }
    limparArquivos();
}