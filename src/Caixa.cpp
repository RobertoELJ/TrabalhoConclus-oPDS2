#include "Caixa.hpp"
#include "Venda.hpp"
#include "FormaPagamento.hpp"
#include "PagamentoInvalidoException.hpp"
#include "PermissaoNegadaException.hpp"

#include <iostream>
#include <exception>

// Inicializa o caixa sem venda e sem pagamento selecionado.
Caixa::Caixa()
    : vendaAtual(nullptr), pagamentoAtual(nullptr) {
}

// Inicia uma nova venda no caixa.
void Caixa::iniciarVenda(Venda* venda) {
    if (venda == nullptr) {
        exibirResultado("Erro: nenhuma venda foi informada.");
        return;
    }

    vendaAtual = venda;
    pagamentoAtual = nullptr;

    exibirResultado("Venda iniciada com sucesso.");
}

// Seleciona a forma de pagamento da venda atual.
void Caixa::selecionarFormaPagamento(FormaPagamento* pagamento) {
    if (vendaAtual == nullptr) {
        exibirResultado("Erro: nenhuma venda foi iniciada.");
        return;
    }

    if (pagamento == nullptr) {
        exibirResultado("Erro: forma de pagamento invalida.");
        return;
    }

    pagamentoAtual = pagamento;

    exibirResultado("Forma de pagamento selecionada: " + pagamento->descricao());
}

// Finaliza a venda e trata possíveis erros.
void Caixa::finalizarVenda() {
    if (vendaAtual == nullptr) {
        exibirResultado("Erro: nenhuma venda foi iniciada.");
        return;
    }

    if (pagamentoAtual == nullptr) {
        exibirResultado("Erro: nenhuma forma de pagamento foi selecionada.");
        return;
    }

    try {
        // Finaliza sem desconto e sem aprovação de gerente.
        vendaAtual->finalizar(pagamentoAtual, 0.0, nullptr);

        exibirResultado("Venda finalizada com sucesso!");
        exibirResultado(vendaAtual->gerarComprovante());

        vendaAtual = nullptr;
        pagamentoAtual = nullptr;
    }
    catch (const PagamentoInvalidoException& erro) {
        exibirResultado(std::string("Erro no pagamento: ") + erro.what());
    }
    catch (const PermissaoNegadaException& erro) {
        exibirResultado(std::string("Permissao negada: ") + erro.what());
    }
    catch (const std::exception& erro) {
        exibirResultado(std::string("Erro ao finalizar venda: ") + erro.what());
    }
}

// Exibe o resultado de uma operação do caixa.
void Caixa::exibirResultado(const std::string& resultado) {
    std::cout << resultado << std::endl;
}