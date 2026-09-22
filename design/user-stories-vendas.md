# User Stories - Vendas e Pagamento

Responsável: Marco Antonio Ramalho dos Reis

## Funcionais

- **US-V01** - Como vendedor, quero registrar a venda de um veículo pra um cliente, pra ter o histórico das vendas.
  - A venda guarda cliente, vendedor, veículo, forma de pagamento e valor final.
- **US-V02** - Como vendedor, quero que o carro vendido saia do estoque, pra não vender o mesmo carro duas vezes.
  - Se não tiver estoque, a venda não acontece.
- **US-V03** - Como cliente, quero escolher como pagar (dinheiro, cartão ou financiado), pra pagar do jeito que dá pra mim.
- **US-V04** - Como cliente, quero desconto pagando à vista em dinheiro, pra economizar.
- **US-V05** - Como cliente, quero parcelar no cartão e ver o valor de cada parcela antes de fechar negócio.

## Não funcionais

- Pagamento com valor inválido (negativo, por exemplo) não pode travar o programa - tem que dar um erro tratado.
- Dá pra criar uma forma de pagamento nova sem mexer na classe Venda.
