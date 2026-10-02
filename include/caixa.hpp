#ifndef CAIXA_HPP
#define CAIXA_HPP

#include <string>

class Venda;
class FormaPagamento;
class PagamentoInvalidoException;

/**
 * @brief Representa o caixa responsável pelo atendimento de uma venda.
 *
 * A classe Caixa controla a venda que está em andamento,
 * encaminha a forma de pagamento escolhida e solicita
 * a finalização da venda.
 */
class Caixa {
private:

    /**
     * @brief Venda que está sendo realizada atualmente.
     */
    Venda* vendaAtual;

public:

    /**
     * @brief Construtor padrão da classe Caixa.
     *
     * Inicializa o caixa sem nenhuma venda em andamento.
     */
    Caixa();

    /**
     * @brief Inicia uma nova venda.
     *
     * @param venda Ponteiro para a venda que será iniciada.
     */
    void iniciarVenda(Venda* venda);

    /**
     * @brief Seleciona a forma de pagamento da venda atual.
     *
     * A forma de pagamento escolhida é encaminhada
     * para a venda que está em andamento.
     *
     * @param pagamento Ponteiro para a forma de pagamento escolhida.
     */
    void selecionarFormaPagamento(FormaPagamento* pagamento);

    /**
     * @brief Solicita a finalização da venda atual.
     *
     * A venda será finalizada caso todos os dados necessários
     * estejam válidos e o pagamento seja aceito.
     */
    void finalizarVenda();

    /**
     * @brief Exibe o resultado da operação realizada pelo caixa.
     *
     * @param resultado Mensagem contendo o resultado da operação
     * ou uma mensagem de erro.
     */
    void exibirResultado(const std::string& resultado);
};

#endif