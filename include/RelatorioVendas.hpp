#pragma once

#include <string>
#include <vector>
#include "Venda.hpp"

/** @brief Relatório das vendas concluídas de um período. Datas no formato AAAA-MM-DD; vendas canceladas ou sem data ficam de fora. */
class RelatorioVendas {
public:
    /** @brief Guarda uma cópia da venda no relatório. */
    void adicionar(const Venda& venda);

    /** @brief Vendas concluídas entre as duas datas, incluindo as próprias datas. Lança std::invalid_argument se uma data estiver fora do formato AAAA-MM-DD ou se a inicial for depois da final. */
    std::vector<Venda> vendasDoPeriodo(const std::string& inicio, const std::string& fim) const;

    /** @brief Soma do valor final das vendas do período. */
    double totalVendido(const std::string& inicio, const std::string& fim) const;

    /** @brief Soma da comissão das vendas do período feitas pelo vendedor com esse código. Lança std::invalid_argument se o código estiver vazio ou o período for inválido. */
    double comissaoDoVendedor(const std::string& idVendedor, const std::string& inicio, const std::string& fim) const;

    /** @brief Vendas concluídas do cliente com esse CPF, de qualquer data. Lança std::invalid_argument se o CPF estiver vazio. */
    std::vector<Venda> vendasDoCliente(const std::string& cpf) const;
    /** @brief Retorna todas as vendas concluidas registradas no relatorio. */
    std::vector<Venda> todasVendasConcluidas() const;
    
private:
    std::vector<Venda> vendas_;
};
