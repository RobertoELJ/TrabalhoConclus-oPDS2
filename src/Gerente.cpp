#ifndef GERENTE_HPP
#define GERENTE_HPP
#include "Gerente.hpp"
#include <stdexcept>


Gerente::Gerente(const std::string& nome, const std::string& id, double percentualComissao, double limiteDescontoSemAprovacao){
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
    return percentualDesconto <= limiteDescontoSemAprovacao_; 
}  


#endif