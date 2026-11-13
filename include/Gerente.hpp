#ifndef GERENTE_HPP
#define GERENTE_HPP
#include "Vendedor.hpp"


/** @brief Gerente da loja: recebe comissão e aprova descontos acima do limite. */
class Gerente : public Vendedor {
public:
    Gerente(const std::string& nome, const std::string& id, double percentualComissao, double limiteDesconto);
    
    /** @brief Diz se o desconto pedido (0 a 100) é menor ou igual ao limite liberado pelo gerente. */
    bool aprovarDescontoMaior(double percentualDesconto) const;

private:
    double limiteDesconto_;
};


#endif