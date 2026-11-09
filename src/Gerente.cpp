#ifndef GERENTE_HPP
#define GERENTE_HPP
#include "Gerente.hpp"
#include <stdexcept>
#include "PermissaoNegadaException.hpp"

Gerente::Gerente(const std::string& nome, const std::string& id, double percentualComissao, double limiteDescontoSemAprovacao) : nome_(nome), id_(id), percentualComissao_(percentualComissao), limiteDescontoSemAprovacao_(limiteDescontoSemAprovacao) {
    if (percentualComissao < 0 || percentualComissao > 100) {
        throw std::invalid_argument("Percentual de comissão deve estar entre 0 e 100.");
    }
}

std::string Gerente::getNome() const { 
    return nome_; 
}

std::string Gerente::getId() const { 
    return id_; 
}

double Gerente::getPercentualComissao() const { 
    return percentualComissao_; 
}

double Gerente::calcularComissao(double valorVenda) const { 
    return (valorVenda * this->percentualComissao_) / 100.0; 
}

bool Gerente::aprovarDesconto(double percentualDesconto) const { 
    if(percentualDesconto > Gerente::limiteDescontoSemAprovacao_) {
        throw PermissaoNegadaException("Desconto acima do limite permitido pelo gerente.");
    }
    return percentualDesconto <= limiteDescontoSemAprovacao_; 
}  


#endif