# Cartões CRC - Vendas e Pagamento

Responsável: Marco Antonio Ramalho dos Reis
Branch: `feature/vendas-pagamento`

Cada cartão descreve uma classe: o que ela sabe e faz (responsabilidades) e com quais outras classes ela conversa (colaboradores).

---

## Venda

**Superclasse:** nenhuma

**Responsabilidades**
- Guardar data e valor final da venda
- Ligar cliente, vendedor, veículo e forma de pagamento
- Pedir à forma de pagamento o valor final
- Confirmar a venda dando baixa no estoque

**Colaboradores**
- Cliente
- Vendedor
- Veiculo
- FormaPagamento
- Estoque

---

## FormaPagamento (classe abstrata)

**Superclasse:** nenhuma | **Subclasses:** Dinheiro (e, nas próximas partes, Cartao e Financiamento)

**Responsabilidades**
- Definir `calcularValorFinal(precoBase)` como método virtual puro
- Definir `descricao()` para exibir o pagamento ao usuário

**Colaboradores**
- Venda

---

## Dinheiro

**Superclasse:** FormaPagamento

**Responsabilidades**
- Aplicar o desconto à vista sobre o preço base
- Rejeitar percentual de desconto inválido

**Colaboradores**
- FormaPagamento
