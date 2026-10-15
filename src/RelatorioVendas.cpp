#include "RelatorioVendas.hpp"

#include <stdexcept>

namespace {
bool estaNoPeriodo(const Venda& venda, const std::string& inicio, const std::string& fim) {
    const std::string data = venda.getData();
    return venda.estaConcluida() && !data.empty() && data >= inicio && data <= fim;
}
}

void RelatorioVendas::adicionar(const Venda& venda) {
    vendas_.push_back(venda);
}

std::vector<Venda> RelatorioVendas::vendasDoPeriodo(const std::string& inicio, const std::string& fim) const {
    if (inicio > fim) {
        throw std::invalid_argument("A data inicial nao pode ser depois da final.");
    }
    std::vector<Venda> resultado;
    for (const Venda& venda : vendas_) {
        if (estaNoPeriodo(venda, inicio, fim)) {
            resultado.push_back(venda);
        }
    }
    return resultado;
}

double RelatorioVendas::totalVendido(const std::string& inicio, const std::string& fim) const {
    double total = 0.0;
    for (const Venda& venda : vendasDoPeriodo(inicio, fim)) {
        total += venda.getValorFinal();
    }
    return total;
}

double RelatorioVendas::comissaoDoVendedor(const std::string& idVendedor, const std::string& inicio, const std::string& fim) const {
    double total = 0.0;
    for (const Venda& venda : vendasDoPeriodo(inicio, fim)) {
        if (venda.getIdVendedor() == idVendedor) {
            total += venda.getComissao();
        }
    }
    return total;
}
