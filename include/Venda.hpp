#pragma once

#include <string>
#include "Carrinho.hpp"

class Cliente;
class Vendedor;
class Gerente;
class FormaPagamento;

/** @brief Uma venda: liga cliente, vendedor, carrinho e forma de pagamento. O estoque é atualizado por quem chama (o Caixa). */
class Venda {
public:
    /** @brief Cria a venda. Lança PagamentoInvalidoException se cliente ou vendedor forem nulos ou se o carrinho estiver vazio. */
    Venda(Cliente* cliente, Vendedor* vendedor, const Carrinho& carrinho);

    /** @brief Finaliza a venda com a forma de pagamento e um desconto de 0 a 100 sobre o total do carrinho. Todo desconto acima de zero precisa do gerente aprovando. Lança PagamentoInvalidoException se a venda já foi finalizada, se o pagamento for nulo, se o desconto sair de 0 a 100 ou se o valor pago não cobrir o total, e PermissaoNegadaException se o desconto não for aprovado. */
    void finalizar(FormaPagamento* pagamento, double percentualDesconto, Gerente* gerente);

    /** @brief Cancela uma venda concluída e zera a comissão. Lança PagamentoInvalidoException se a venda não estiver concluída. */
    void cancelar();

    /** @brief Texto com cliente, vendedor, itens e o valor final da venda. */
    std::string gerarComprovante() const;

    /** @brief Venda em uma linha de texto (CPF;vendedor;valor;comissão;situação), para salvar em arquivo. */
    std::string toLinha() const;

    /** @brief Valor final da venda (zero antes de finalizar). */
    double getValorFinal() const;

    /** @brief Comissão do vendedor (zero antes de finalizar e depois de cancelar). */
    double getComissao() const;

    /** @brief Diz se a venda foi finalizada e não cancelada. */
    bool estaConcluida() const;

    /** @brief Diz se a venda foi cancelada. */
    bool estaCancelada() const;

    /** @brief Define a data da venda no formato AAAA-MM-DD. Lança PagamentoInvalidoException se o formato estiver errado. */
    void definirData(const std::string& data);

    /** @brief Data da venda (vazia se ainda não foi definida). */
    std::string getData() const;

    /** @brief Código do vendedor responsável pela venda. */
    std::string getIdVendedor() const;

    /** @brief CPF do cliente da venda. */
    std::string getCpfCliente() const;

private:
    Cliente* cliente_;
    Vendedor* vendedor_;
    Carrinho carrinho_;
    double valorFinal_;
    double comissao_;
    bool concluida_;
    bool cancelada_;
    std::string data_;
};
