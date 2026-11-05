#include "CadastroVeiculo.hpp"

bool CadastroVeiculos::cadastrarVeiculo(const Veiculo& veiculo) {
    if (!veiculo.validarDados()) {
        return false;
    }
    if(placaCadastrada(veiculo.getPlaca())) {
        return false;
    }
    veiculos.push_back(veiculo);
    return true;
}

bool CadastroVeiculos::placaCadastrada(const std::string& placa) const {
    for (const Veiculo& veiculo : veiculos) {
        if (veiculo.getPlaca() == placa) {
            return true;
        }
    }
    return false;
}

const Veiculo* CadastroVeiculos::buscarVeiculos(const std::string& placa) const {
    for (const Veiculo& veiculo : veiculos) {
        if (veiculo.getPlaca() == placa) {
            return &veiculo;
        }
    }
    return nullptr;
}

bool CadastroVeiculos::atualizarVeiculo(const std::string& placa, const Veiculo& novosDados) {
    if(!novosDados.validarDados()) {
        return false;
    }

    if(novosDados.getPlaca() != placa && placaCadastrada(novosDados.getPlaca())) {
        return false;
    }

    for(Veiculo& veiculo : veiculos){
        if (veiculo.getPlaca() == placa){
            veiculo = novosDados;
            return true;
        }
    }
    return false;
}

const std::vector<Veiculo>& CadastroVeiculos::listarVeiculos() const {
    return veiculos;
}