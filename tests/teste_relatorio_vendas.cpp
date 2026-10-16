#include <stdexcept>
#include "doctest.h"
#include "Carrinho.hpp"
#include "Cliente.hpp"
#include "Dinheiro.hpp"
#include "RelatorioVendas.hpp"
#include "Venda.hpp"
#include "Veiculo.hpp"
#include "Vendedor.hpp"

namespace {
Venda vendaConcluida(Cliente* cliente, Vendedor* vendedor, double valor, const std::string& data) {
    Carrinho carrinho;
    carrinho.adicionarVeiculo(Veiculo("Fiat", "Uno", "AAA1111", 2020, valor));
    Venda venda(cliente, vendedor, carrinho);
    Dinheiro pagamento(0.0, valor);
    venda.finalizar(&pagamento, 0.0, nullptr);
    venda.definirData(data);
    return venda;
}
}

TEST_CASE("RelatorioVendas: relatorio vazio tem total zero e nenhuma venda") {
    RelatorioVendas relatorio;
    CHECK(relatorio.totalVendido("2026-10-01", "2026-10-31") == doctest::Approx(0.0));
    CHECK(relatorio.vendasDoPeriodo("2026-10-01", "2026-10-31").empty());
}

TEST_CASE("RelatorioVendas: soma so as vendas dentro do periodo") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    RelatorioVendas relatorio;
    relatorio.adicionar(vendaConcluida(&cliente, &vendedor, 1000.0, "2026-10-01"));
    relatorio.adicionar(vendaConcluida(&cliente, &vendedor, 2000.0, "2026-10-10"));
    relatorio.adicionar(vendaConcluida(&cliente, &vendedor, 4000.0, "2026-10-20"));
    CHECK(relatorio.totalVendido("2026-10-01", "2026-10-15") == doctest::Approx(3000.0));
    CHECK(relatorio.vendasDoPeriodo("2026-10-01", "2026-10-15").size() == 2);
}

TEST_CASE("RelatorioVendas: o periodo inclui as datas das pontas") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    RelatorioVendas relatorio;
    relatorio.adicionar(vendaConcluida(&cliente, &vendedor, 1000.0, "2026-10-05"));
    CHECK(relatorio.totalVendido("2026-10-05", "2026-10-05") == doctest::Approx(1000.0));
}

TEST_CASE("RelatorioVendas: venda cancelada nao entra no total") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda cancelada = vendaConcluida(&cliente, &vendedor, 1000.0, "2026-10-05");
    cancelada.cancelar();
    RelatorioVendas relatorio;
    relatorio.adicionar(cancelada);
    relatorio.adicionar(vendaConcluida(&cliente, &vendedor, 500.0, "2026-10-06"));
    CHECK(relatorio.totalVendido("2026-10-01", "2026-10-31") == doctest::Approx(500.0));
}

TEST_CASE("RelatorioVendas: venda sem data nao entra") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Carrinho carrinho;
    carrinho.adicionarVeiculo(Veiculo("Fiat", "Uno", "AAA1111", 2020, 1000.0));
    Venda semData(&cliente, &vendedor, carrinho);
    Dinheiro pagamento(0.0, 1000.0);
    semData.finalizar(&pagamento, 0.0, nullptr);
    RelatorioVendas relatorio;
    relatorio.adicionar(semData);
    CHECK(relatorio.totalVendido("2026-01-01", "2026-12-31") == doctest::Approx(0.0));
}

TEST_CASE("RelatorioVendas: comissao soma so as vendas do vendedor pedido") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor joao("Joao", "V1", 5.0);
    Vendedor maria("Maria", "V2", 10.0);
    RelatorioVendas relatorio;
    relatorio.adicionar(vendaConcluida(&cliente, &joao, 1000.0, "2026-10-05"));
    relatorio.adicionar(vendaConcluida(&cliente, &joao, 2000.0, "2026-10-06"));
    relatorio.adicionar(vendaConcluida(&cliente, &maria, 1000.0, "2026-10-07"));
    CHECK(relatorio.comissaoDoVendedor("V1", "2026-10-01", "2026-10-31") == doctest::Approx(150.0));
    CHECK(relatorio.comissaoDoVendedor("V2", "2026-10-01", "2026-10-31") == doctest::Approx(100.0));
    CHECK(relatorio.comissaoDoVendedor("V9", "2026-10-01", "2026-10-31") == doctest::Approx(0.0));
}

TEST_CASE("RelatorioVendas: cliente sem compras tem historico vazio") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    RelatorioVendas relatorio;
    relatorio.adicionar(vendaConcluida(&cliente, &vendedor, 1000.0, "2026-10-05"));
    CHECK(relatorio.vendasDoCliente("999").empty());
}

TEST_CASE("RelatorioVendas: historico devolve so as compras do cliente pedido") {
    Cliente ana("Ana", "123", "ana@email.com");
    Cliente bia("Bia", "456", "bia@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    RelatorioVendas relatorio;
    relatorio.adicionar(vendaConcluida(&ana, &vendedor, 1000.0, "2026-10-05"));
    relatorio.adicionar(vendaConcluida(&bia, &vendedor, 2000.0, "2026-10-06"));
    relatorio.adicionar(vendaConcluida(&ana, &vendedor, 3000.0, "2026-11-07"));
    CHECK(relatorio.vendasDoCliente("123").size() == 2);
    CHECK(relatorio.vendasDoCliente("456").size() == 1);
}

TEST_CASE("RelatorioVendas: compra cancelada nao entra no historico do cliente") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda cancelada = vendaConcluida(&cliente, &vendedor, 1000.0, "2026-10-05");
    cancelada.cancelar();
    RelatorioVendas relatorio;
    relatorio.adicionar(cancelada);
    CHECK(relatorio.vendasDoCliente("123").empty());
}

TEST_CASE("RelatorioVendas: data inicial depois da final lanca excecao") {
    RelatorioVendas relatorio;
    CHECK_THROWS_AS(relatorio.totalVendido("2026-10-31", "2026-10-01"), std::invalid_argument);
}
