#pragma once

#include <string>
#include <vector>
#include "Venda.hpp"

/** @brief Relatório das vendas concluídas de um período. Datas no formato AAAA-MM-DD; vendas canceladas ou sem data ficam de fora. */
class RelatorioVendas {
public:
    /** @brief Guarda uma cópia da venda no relatório. */
    void adicionar(const Venda& venda);

    /** @brief Vendas concluídas entre as duas datas, incluindo as próprias datas. Lança std::invalid_argument se a data inicial for depois da final. */
    std::vector<Venda> vendasDoPeriodo(const std::string& inicio, const std::string& fim) const;

    /** @brief Soma do valor final das vendas do período. */
    double totalVendido(const std::string& inicio, const std::string& fim) const;

    /** @brief Soma da comissão das vendas do período feitas pelo vendedor com esse código. */
    double comissaoDoVendedor(const std::string& idVendedor, const std::string& inicio, const std::string& fim) const;

    /** @brief Vendas concluídas do cliente com esse CPF, de qualquer data. */
    std::vector<Venda> vendasDoCliente(const std::string& cpf) const;

private:
    std::vector<Venda> vendas_;
};
