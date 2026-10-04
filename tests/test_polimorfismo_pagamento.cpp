#include <memory>
#include <vector>
#include "doctest.h"
#include "Boleto.hpp"
#include "Cartao.hpp"
#include "Dinheiro.hpp"
#include "Financiamento.hpp"
#include "FormaPagamento.hpp"
#include "Pix.hpp"

TEST_CASE("FormaPagamento: a Venda usa qualquer forma pela interface comum") {
    std::vector<std::unique_ptr<FormaPagamento>> formas;
    formas.emplace_back(new Dinheiro(10.0, 1000.0));
    formas.emplace_back(new Pix(1000.0));
    formas.emplace_back(new Cartao(2, 10.0));
    formas.emplace_back(new Boleto(5, 1000.0));
    formas.emplace_back(new Financiamento(0.0, 10, 1.0));

    const double esperado[] = {900.0, 1000.0, 1100.0, 1000.0, 1100.0};
    for (std::size_t i = 0; i < formas.size(); ++i) {
        CHECK(formas[i]->calcularValorFinal(1000.0) == doctest::Approx(esperado[i]));
        CHECK_FALSE(formas[i]->descricao().empty());
    }
}

TEST_CASE("FormaPagamento: so o Dinheiro devolve troco") {
    Dinheiro dinheiro(0.0, 1200.0);
    Pix pix(1000.0);
    const FormaPagamento& comTroco = dinheiro;
    const FormaPagamento& semTroco = pix;
    CHECK(comTroco.calcularTroco(1000.0) == doctest::Approx(200.0));
    CHECK(semTroco.calcularTroco(1000.0) == doctest::Approx(0.0));
}
