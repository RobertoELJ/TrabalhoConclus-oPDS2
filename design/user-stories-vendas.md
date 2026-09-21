# User Stories - Vendas e Pagamento

Responsável: Marco Antonio Ramalho dos Reis
Branch: `feature/vendas-pagamento`

## Requisitos funcionais

| ID | História | Critérios de aceitação |
|----|----------|------------------------|
| US-V01 | Como **vendedor**, quero registrar a venda de um veículo para um cliente, para manter o histórico de vendas da loja. | A venda guarda cliente, vendedor, veículo, forma de pagamento, data e valor final. |
| US-V02 | Como **vendedor**, quero que o veículo vendido saia do estoque automaticamente, para não vender o mesmo carro duas vezes. | Após a venda, o estoque do modelo diminui em uma unidade. Se não houver unidade disponível, a venda é recusada. |
| US-V03 | Como **cliente**, quero escolher a forma de pagamento (dinheiro, cartão ou financiamento), para pagar do jeito que me convém. | O sistema aceita as três formas e cada uma calcula o valor final à sua maneira. |
| US-V04 | Como **cliente**, quero pagar à vista em dinheiro e receber desconto, para economizar. | O pagamento em dinheiro aplica o percentual de desconto configurado sobre o preço do veículo. |
| US-V05 | Como **cliente**, quero parcelar no cartão e ver o valor de cada parcela antes de confirmar, para decidir com clareza. | O sistema informa número de parcelas, juros (se houver) e valor de cada parcela. |
| US-V06 | Como **cliente**, quero financiar o veículo informando entrada e prazo, para conseguir comprar sem pagar tudo de uma vez. | O sistema calcula o saldo financiado, a taxa, a parcela mensal e o total pago no fim do prazo. |
| US-V07 | Como **vendedor**, quero que minha comissão seja calculada automaticamente a cada venda, para não errar contas. | A comissão é calculada sobre o valor da venda conforme o tipo de funcionário. |
| US-V08 | Como **gerente**, quero autorizar descontos acima de um limite, para controlar as margens da loja. | Desconto acima do limite exige aprovação do gerente; sem ela, a venda é recusada. |
| US-V09 | Como **gerente**, quero consultar as vendas realizadas por período, para acompanhar o desempenho. | A consulta lista as vendas entre duas datas e o total faturado. |
| US-V10 | Como **gerente**, quero cancelar uma venda registrada por engano, para corrigir erros. | O cancelamento devolve o veículo ao estoque e remove a comissão associada. |
| US-V11 | Como **usuário do sistema**, quero que as vendas fiquem salvas em arquivo de texto, para não perdê-las ao fechar o programa. | As vendas são gravadas em `data/vendas.txt` e recarregadas na próxima execução. |

## Requisitos não funcionais

| ID | Requisito |
|----|-----------|
| RNF-V01 | **Robustez:** dados de pagamento inválidos (parcelas <= 0, entrada maior que o preço, valores negativos) lançam exceção própria em vez de derrubar o programa. |
| RNF-V02 | **Extensibilidade:** incluir uma nova forma de pagamento deve exigir apenas criar uma nova subclasse de `FormaPagamento`, sem alterar `Venda`. |
| RNF-V03 | **Testabilidade:** cada forma de pagamento e o cálculo de comissão devem ter testes de unidade. |
| RNF-V04 | **Persistência simples:** o formato do arquivo `data/vendas.txt` deve ser legível e fácil de reler, tratando arquivo ausente ou corrompido sem travar. |
| RNF-V05 | **Portabilidade:** o código segue C++11 e compila com `make`. |
