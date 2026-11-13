#include "Gerente.hpp"
#include "PermissaoNegadaException.hpp"


Gerente::Gerente(const std::string& nome, const std::string& id, double percentualComissao, double limiteDesconto)
    : Vendedor(nome, id, percentualComissao), limiteDesconto_(limiteDesconto) {
}

bool Gerente::aprovarDescontoMaior(double percentualDesconto) const {
    if (percentualDesconto > limiteDesconto_) {
        // Lança o erro que você já havia arrumado anteriormente
        throw PermissaoNegadaException("Desconto solicitado excede o limite do gerente.");
    }
    return true;
}