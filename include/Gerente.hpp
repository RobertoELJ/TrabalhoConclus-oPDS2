#pragma once

#include <string>

/** @brief Gerente da loja: recebe comissão e aprova descontos acima do limite. */
class Gerente {
public:
    /** @brief Cria o gerente com a comissão em percentual e o maior desconto (0 a 100) que ele libera sem aprovação manual. */
    Gerente(const std::string& nome, const std::string& id, double percentualComissao, double limiteDescontoSemAprovacao);

    /** @brief Nome do gerente. */
    std::string getNome() const;

    /** @brief Identificação do gerente. */
    std::string getId() const;

    /** @brief Percentual de comissão. */
    double getPercentualComissao() const;

    /** @brief Comissão sobre uma venda: valor da venda vezes o percentual, dividido por 100. */
    double calcularComissao(double valorVenda) const;

    /** @brief Diz se o desconto pedido (0 a 100) é menor ou igual ao limite liberado pelo gerente. */
    bool aprovarDesconto(double percentualDesconto) const;

private:
    std::string nome_;
    std::string id_;
    double percentualComissao_;
    double limiteDescontoSemAprovacao_;
};
