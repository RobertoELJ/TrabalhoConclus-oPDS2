# Cartões CRC - Vendas e Pagamento

Responsável: Marco Antonio Ramalho dos Reis
Branch: `feature/vendas-pagamento`

Cada cartão descreve uma classe, o que ela sabe e faz (responsabilidades) e com quem ela conversa (colaboradores).

---

## Venda

**Superclasse:** nenhuma

| Responsabilidades | Colaboradores |
|-------------------|---------------|
| Guardar data, valor final e situação da venda (concluída ou cancelada) | Cliente |
| Ligar cliente, vendedor, veículo e forma de pagamento | Vendedor |
| Pedir à forma de pagamento o valor final | Veiculo |
| Confirmar a venda e solicitar a baixa no estoque | FormaPagamento |
| Cancelar a venda e devolver o veículo ao estoque | Estoque |
| Converter a venda para linha de texto (persistência) | Loja |

---

## FormaPagamento (classe abstrata)

**Superclasse:** nenhuma | **Subclasses:** Dinheiro, Cartao, Financiamento

| Responsabilidades | Colaboradores |
|-------------------|---------------|
| Definir a interface `calcularValorFinal(precoBase)` (método virtual puro) | Venda |
| Definir `descricao()` para exibir o pagamento ao usuário | PagamentoInvalidoException |
| Validar os dados comuns do pagamento (valores não negativos) | |

---

## Dinheiro

**Superclasse:** FormaPagamento

| Responsabilidades | Colaboradores |
|-------------------|---------------|
| Aplicar o desconto à vista sobre o preço base | FormaPagamento |
| Rejeitar percentual de desconto inválido | PagamentoInvalidoException |

---

## Cartao

**Superclasse:** FormaPagamento

| Responsabilidades | Colaboradores |
|-------------------|---------------|
| Guardar número de parcelas e taxa de juros | FormaPagamento |
| Calcular valor final com juros e valor de cada parcela | PagamentoInvalidoException |
| Rejeitar número de parcelas inválido (<= 0 ou acima do limite) | |

---

## Financiamento

**Superclasse:** FormaPagamento

| Responsabilidades | Colaboradores |
|-------------------|---------------|
| Guardar entrada, prazo em meses e taxa mensal | FormaPagamento |
| Calcular saldo financiado, parcela mensal e total pago | PagamentoInvalidoException |
| Rejeitar entrada maior que o preço ou prazo inválido | |

---

## ComissaoVendedor

**Superclasse:** nenhuma

| Responsabilidades | Colaboradores |
|-------------------|---------------|
| Calcular a comissão de uma venda conforme o tipo de funcionário | Venda |
| Guardar os percentuais de comissão configurados | Vendedor |
| Acumular a comissão total de um vendedor em um período | Gerente |

---

## PagamentoInvalidoException

**Superclasse:** std::exception

| Responsabilidades | Colaboradores |
|-------------------|---------------|
| Representar erro em dados de pagamento com mensagem clara | FormaPagamento e subclasses |
| Ser capturada no menu para exibir o erro sem encerrar o programa | Loja |

---

## Observação para o grupo

Os colaboradores `Cliente`, `Vendedor`, `Gerente`, `Veiculo`, `Estoque` e `Loja` pertencem às áreas dos outros membros. Ao fechar o C5, conferir se os nomes e métodos combinados batem com os cartões de cada um.
