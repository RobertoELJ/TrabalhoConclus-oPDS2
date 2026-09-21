# User Stories - Vendas e Pagamento

Responsável: Marco Antonio Ramalho dos Reis
Branch: `feature/vendas-pagamento`

## Requisitos funcionais

| ID | História | Critérios de aceitação |
|----|----------|------------------------|
| US-V01 | Como **vendedor**, quero registrar a venda de um veículo para um cliente, para manter o histórico de vendas da loja. | A venda guarda cliente, vendedor, veículo, forma de pagamento, data e valor final. |
| US-V02 | Como **vendedor**, quero que o veículo vendido saia do estoque automaticamente, para não vender o mesmo carro duas vezes. | Após a venda, o estoque do modelo diminui em uma unidade. Se não houver unidade disponível, a venda é recusada e nada é gravado. |
| US-V03 | Como **cliente**, quero escolher a forma de pagamento (dinheiro, cartão ou financiamento), para pagar do jeito que me convém. | O sistema aceita as três formas e cada uma calcula o valor final à sua maneira. |
| US-V04 | Como **cliente**, quero pagar à vista em dinheiro e receber desconto, para economizar. | O pagamento em dinheiro aplica o percentual de desconto à vista sobre o preço do veículo. |

## Requisitos não funcionais

| ID | Requisito |
|----|-----------|
| RNF-V01 | **Robustez:** dados de pagamento inválidos (valores ou percentuais negativos) lançam uma exceção em vez de derrubar o programa. |
| RNF-V02 | **Extensibilidade:** incluir uma nova forma de pagamento deve exigir apenas criar uma nova subclasse de `FormaPagamento`, sem alterar `Venda`. |
