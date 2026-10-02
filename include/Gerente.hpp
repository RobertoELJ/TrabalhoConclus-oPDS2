#ifndef GERENTE_HPP
#define GERENTE_HPP

#include <string>

/**
 * @file Gerente.hpp
 * @brief Gerente da loja: recebe comissão e aprova descontos acima do limite.
 */

/**
 * @brief Representa um gerente.
 *
 * Criado porque a Venda precisa de alguém que aprove descontos acima de um
 * limite (US-V08 da modelagem de Vendas) e nenhuma classe Gerente existia
 * ainda em include/.
 */
class Gerente {
public:
    /**
     * @brief Cria um gerente.
     * @param nome Nome do gerente.
     * @param id Identificação do gerente.
     * @param percentualComissao Percentual de comissão sobre cada venda que ele acompanha.
     * @param limiteDescontoSemAprovacao Maior desconto (0 a 100) que não precisa de aprovação dele.
     */
    Gerente(const std::string& nome, const std::string& id, double percentualComissao, double limiteDescontoSemAprovacao);

    /** @brief Nome do gerente. */
    std::string getNome() const;

    /** @brief Identificação do gerente. */
    std::string getId() const;

    /** @brief Percentual de comissão do gerente. */
    double getPercentualComissao() const;

    /**
     * @brief Calcula a comissão do gerente sobre o valor de uma venda.
     * @param valorVenda Valor final da venda.
     */
    double calcularComissao(double valorVenda) const;

    /**
     * @brief Decide se um desconto pode ser aplicado sem problema.
     * @param percentualDesconto Desconto pedido, de 0 a 100.
     * @return true se o desconto está dentro do limite que o gerente libera sem aprovação manual.
     */
    bool aprovarDesconto(double percentualDesconto) const;

private:
    std::string nome_;
    std::string id_;
    double percentualComissao_;
    double limiteDescontoSemAprovacao_;
};

#endif
