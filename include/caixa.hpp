#ifndef CAIXA_HPP
#define CAIXA_HPP

#include <string>

class Venda;
class FormaPagamento;
class PagamentoInvalidoException;

class Caixa {
private:
    Venda* vendaAtual;

public:
    Caixa();

    void iniciarVenda(Venda* venda);
    void selecionarFormaPagamento(FormaPagamento* pagamento);
    void finalizarVenda();

    void exibirResultado(const std::string& resultado);
};

#endif