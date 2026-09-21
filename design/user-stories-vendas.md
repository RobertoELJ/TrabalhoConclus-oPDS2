# User Stories - Vendas e Pagamento

Responsável: Marco Antonio Ramalho dos Reis
Branch: `feature/vendas-pagamento`

## Requisitos funcionais

| ID | História | Critérios de aceitação |
|----|----------|------------------------|
| US-V01 | Como **vendedor**, quero registrar a venda de um veículo para um cliente, para manter o histórico de vendas da loja. | A venda guarda cliente, vendedor, veículo, forma de pagamento, data, valor final e comissão. |
| US-V02 | Como **vendedor**, quero que o veículo vendido saia do estoque automaticamente, para não vender o mesmo carro duas vezes. | Após a venda, o estoque do modelo diminui em uma unidade. Se não houver unidade disponível, a venda é recusada e nada é gravado. |
| US-V03 | Como **cliente**, quero escolher a forma de pagamento (dinheiro, cartão ou financiamento), para pagar do jeito que me convém. | O sistema aceita as três formas e cada uma calcula o valor final à sua maneira. |
| US-V04 | Como **cliente**, quero pagar à vista em dinheiro e receber desconto, para economizar. | O pagamento em dinheiro aplica o percentual de desconto à vista sobre o preço do veículo. |
| US-V05 | Como **cliente**, quero parcelar no cartão e ver o valor de cada parcela antes de confirmar, para decidir com clareza. | O sistema informa número de parcelas, juros (se houver), valor de cada parcela e total pago. |
| US-V06 | Como **cliente**, quero financiar o veículo informando entrada e prazo, para conseguir comprar sem pagar tudo de uma vez. | O sistema calcula saldo financiado, taxa, parcela mensal e total pago no fim do prazo. |
| US-V07 | Como **vendedor**, quero que minha comissão seja calculada automaticamente a cada venda, para não errar contas. | A comissão é obtida de `calcularComissao(valorVenda)` do funcionário responsável (Vendedor ou Gerente, com percentuais diferentes) e gravada na venda. |
| US-V08 | Como **gerente**, quero autorizar descontos acima de um limite, para controlar as margens da loja. | Existe um limite de desconto configurável (ex.: 5%). Acima dele a venda exige aprovação do gerente; sem aprovação, a venda é recusada com `PermissaoNegadaException`. |
| US-V09 | Como **gerente**, quero consultar as vendas realizadas por período, para acompanhar o desempenho. | A consulta recebe duas datas e retorna as vendas concluídas no intervalo e o total faturado. Vendas canceladas não entram no total. |
| US-V10 | Como **gerente**, quero cancelar uma venda registrada por engano, para corrigir erros. | O cancelamento devolve o veículo ao estoque, zera a comissão da venda e marca a venda como cancelada. Cancelar uma venda já cancelada é recusado com `VendaInvalidaException`. |
| US-V11 | Como **usuário do sistema**, quero que as vendas fiquem salvas em arquivo de texto, para não perdê-las ao fechar o programa. | As vendas são gravadas em `data/vendas.txt` e recarregadas na próxima execução. Arquivo ausente resulta em lista vazia. Linha corrompida é ignorada com aviso, sem derrubar o programa. |
| US-V12 | Como **vendedor**, quero consultar as compras de um cliente, para atendê-lo com base no histórico. | A consulta por cliente retorna todas as vendas associadas a ele, com data, veículo e valor. |
| US-V13 | Como **gerente**, quero ver a comissão total de cada vendedor em um período, para conferir pagamentos. | O relatório soma as comissões das vendas concluídas de cada vendedor no intervalo informado. |

## Requisitos não funcionais

| ID | Requisito |
|----|-----------|
| RNF-V01 | **Robustez:** dados de pagamento inválidos (parcelas <= 0, entrada maior que o preço, valores ou percentuais negativos) lançam `PagamentoInvalidoException` em vez de derrubar o programa. |
| RNF-V02 | **Extensibilidade:** incluir uma nova forma de pagamento deve exigir apenas criar uma nova subclasse de `FormaPagamento`, sem alterar `Venda`. |
| RNF-V03 | **Testabilidade:** cada forma de pagamento, a validação de desconto e o relatório por período devem ter testes de unidade. |
| RNF-V04 | **Persistência simples:** o formato de `data/vendas.txt` é legível, com uma venda por linha, e a leitura trata arquivo ausente ou linhas inválidas sem travar. |
| RNF-V05 | **Portabilidade:** o código segue C++11 e compila com `make`. |
| RNF-V06 | **Consistência de estado:** uma venda nunca fica pela metade. Se qualquer etapa falhar (estoque, pagamento, aprovação), o estoque e o histórico permanecem como estavam. |
