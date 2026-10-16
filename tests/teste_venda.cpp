#include "doctest.h"
#include "Carrinho.hpp"
#include "Cartao.hpp"
#include "Cliente.hpp"
#include "Dinheiro.hpp"
#include "Gerente.hpp"
#include "PagamentoInvalidoException.hpp"
#include "PermissaoNegadaException.hpp"
#include "Venda.hpp"
#include "Veiculo.hpp"
#include "Vendedor.hpp"

namespace {
Carrinho carrinhoDeMil() {
    Carrinho carrinho;
    carrinho.adicionarVeiculo(Veiculo("Fiat", "Uno", "AAA1111", 2020, 1000.0));
    return carrinho;
}
}

TEST_CASE("Venda: nova venda nao esta concluida nem cancelada") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    CHECK_FALSE(venda.estaConcluida());
    CHECK_FALSE(venda.estaCancelada());
    CHECK(venda.getValorFinal() == doctest::Approx(0.0));
    CHECK(venda.getComissao() == doctest::Approx(0.0));
}

TEST_CASE("Venda: sem cliente, sem vendedor ou com carrinho vazio lanca excecao") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    CHECK_THROWS_AS(Venda(nullptr, &vendedor, carrinhoDeMil()), PagamentoInvalidoException);
    CHECK_THROWS_AS(Venda(&cliente, nullptr, carrinhoDeMil()), PagamentoInvalidoException);
    CHECK_THROWS_AS(Venda(&cliente, &vendedor, Carrinho()), PagamentoInvalidoException);
}

TEST_CASE("Venda: finalizar em dinheiro calcula valor e comissao") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    Dinheiro pagamento(0.0, 1000.0);
    venda.finalizar(&pagamento, 0.0, nullptr);
    CHECK(venda.estaConcluida());
    CHECK(venda.getValorFinal() == doctest::Approx(1000.0));
    CHECK(venda.getComissao() == doctest::Approx(50.0));
}

TEST_CASE("Venda: o cartao acrescenta os juros ao valor final") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    Cartao pagamento(2, 10.0);
    venda.finalizar(&pagamento, 0.0, nullptr);
    CHECK(venda.getValorFinal() == doctest::Approx(1100.0));
}

TEST_CASE("Venda: valor pago menor que o total lanca excecao e nao conclui") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    Dinheiro pagamento(0.0, 500.0);
    CHECK_THROWS_AS(venda.finalizar(&pagamento, 0.0, nullptr), PagamentoInvalidoException);
    CHECK_FALSE(venda.estaConcluida());
}

TEST_CASE("Venda: pagamento nulo lanca excecao") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    CHECK_THROWS_AS(venda.finalizar(nullptr, 0.0, nullptr), PagamentoInvalidoException);
}

TEST_CASE("Venda: desconto fora de 0 a 100 lanca excecao") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Gerente gerente("Maria", "G1", 2.0, 10.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    Dinheiro pagamento(0.0, 1000.0);
    CHECK_THROWS_AS(venda.finalizar(&pagamento, -1.0, &gerente), PagamentoInvalidoException);
    CHECK_THROWS_AS(venda.finalizar(&pagamento, 101.0, &gerente), PagamentoInvalidoException);
}

TEST_CASE("Venda: desconto sem gerente lanca PermissaoNegadaException") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    Dinheiro pagamento(0.0, 1000.0);
    CHECK_THROWS_AS(venda.finalizar(&pagamento, 5.0, nullptr), PermissaoNegadaException);
    CHECK_FALSE(venda.estaConcluida());
}

TEST_CASE("Venda: desconto acima do limite do gerente lanca PermissaoNegadaException") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Gerente gerente("Maria", "G1", 2.0, 10.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    Dinheiro pagamento(0.0, 1000.0);
    CHECK_THROWS_AS(venda.finalizar(&pagamento, 15.0, &gerente), PermissaoNegadaException);
}

TEST_CASE("Venda: desconto aprovado pelo gerente reduz o valor") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Gerente gerente("Maria", "G1", 2.0, 10.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    Dinheiro pagamento(0.0, 1000.0);
    venda.finalizar(&pagamento, 10.0, &gerente);
    CHECK(venda.getValorFinal() == doctest::Approx(900.0));
    CHECK(venda.getComissao() == doctest::Approx(45.0));
}

TEST_CASE("Venda: nao da para finalizar duas vezes") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    Dinheiro pagamento(0.0, 1000.0);
    venda.finalizar(&pagamento, 0.0, nullptr);
    CHECK_THROWS_AS(venda.finalizar(&pagamento, 0.0, nullptr), PagamentoInvalidoException);
}

TEST_CASE("Venda: cancelar zera a comissao e marca como cancelada") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    Dinheiro pagamento(0.0, 1000.0);
    venda.finalizar(&pagamento, 0.0, nullptr);
    venda.cancelar();
    CHECK(venda.estaCancelada());
    CHECK_FALSE(venda.estaConcluida());
    CHECK(venda.getComissao() == doctest::Approx(0.0));
}

TEST_CASE("Venda: cancelar venda nao concluida ou ja cancelada lanca excecao") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    CHECK_THROWS_AS(venda.cancelar(), PagamentoInvalidoException);
    Dinheiro pagamento(0.0, 1000.0);
    venda.finalizar(&pagamento, 0.0, nullptr);
    venda.cancelar();
    CHECK_THROWS_AS(venda.cancelar(), PagamentoInvalidoException);
}

TEST_CASE("Venda: comprovante mostra cliente, vendedor, item e total") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    Dinheiro pagamento(0.0, 1000.0);
    venda.finalizar(&pagamento, 0.0, nullptr);
    const std::string texto = venda.gerarComprovante();
    CHECK(texto.find("Ana") != std::string::npos);
    CHECK(texto.find("Joao") != std::string::npos);
    CHECK(texto.find("Fiat Uno") != std::string::npos);
    CHECK(texto.find("Total: 1000.00") != std::string::npos);
}

TEST_CASE("Venda: linha de arquivo tem CPF, vendedor e situacao") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    CHECK(venda.toLinha() == "123;V1;0;0;aberta");
    Dinheiro pagamento(0.0, 1000.0);
    venda.finalizar(&pagamento, 0.0, nullptr);
    CHECK(venda.toLinha() == "123;V1;1000;50;concluida");
    venda.cancelar();
    CHECK(venda.toLinha() == "123;V1;1000;0;cancelada");
}

TEST_CASE("Venda: sem data definida a data e vazia") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    CHECK(venda.getData() == "");
}

TEST_CASE("Venda: data no formato AAAA-MM-DD e aceita") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    venda.definirData("2026-10-15");
    CHECK(venda.getData() == "2026-10-15");
}

TEST_CASE("Venda: data em outro formato lanca excecao") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    CHECK_THROWS_AS(venda.definirData("15/10/2026"), PagamentoInvalidoException);
    CHECK_THROWS_AS(venda.definirData(""), PagamentoInvalidoException);
}

TEST_CASE("Venda: devolve o CPF do cliente") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    CHECK(venda.getCpfCliente() == "123");
}

TEST_CASE("Venda: devolve o codigo do vendedor") {
    Cliente cliente("Ana", "123", "ana@email.com");
    Vendedor vendedor("Joao", "V1", 5.0);
    Venda venda(&cliente, &vendedor, carrinhoDeMil());
    CHECK(venda.getIdVendedor() == "V1");
}
