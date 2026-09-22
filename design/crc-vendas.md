# Cartões CRC - Vendas e Pagamento

Responsável: Marco Antonio Ramalho dos Reis

Cada cartão: o que a classe sabe/faz (responsabilidades) e com quem ela conversa (colaboradores).

---

## Venda

**Responsabilidades**
- Guardar data e valor final
- Ligar cliente, vendedor, veículo e forma de pagamento
- Pedir pra forma de pagamento o valor final
- Dar baixa no estoque quando confirma

**Colaboradores**: Cliente, Vendedor, Veiculo, FormaPagamento, Estoque

---

## FormaPagamento (abstrata)

Subclasses: Dinheiro, Cartao (Financiamento entra depois)

**Responsabilidades**
- calcularValorFinal(precoBase) - cada subclasse implementa do seu jeito
- descricao() - pra mostrar pro usuário

**Colaboradores**: Venda

---

## Dinheiro

**Responsabilidades**
- Aplica o desconto à vista em cima do preço
- Recusa desconto inválido (negativo ou acima de 100%)

**Colaboradores**: FormaPagamento

---

## Cartao

**Responsabilidades**
- Guarda quantas parcelas e a taxa de juros
- Calcula o valor final com juros e o valor de cada parcela
- Recusa número de parcelas inválido

**Colaboradores**: FormaPagamento
