# Cartões CRC - Vendas e Pagamento

Responsável: Marco Antonio Ramalho dos Reis
Branch: `feature/vendas-pagamento`

Cada cartão descreve uma classe: o que ela sabe e faz (responsabilidades) e com quais outras classes ela conversa (colaboradores). As duas listas são independentes; um colaborador não corresponde a uma responsabilidade específica.

---

## Venda

**Superclasse:** nenhuma

**Responsabilidades**
- Guardar data, valor final, comissão e situação (concluída ou cancelada)
- Ligar cliente, vendedor, veículo e forma de pagamento
- Pedir à forma de pagamento o valor final
- Verificar se o desconto excede o limite e exigir aprovação do gerente
- Pedir a comissão ao funcionário responsável e guardar o valor
- Confirmar a venda dando baixa no estoque (tudo ou nada)
- Cancelar a venda: devolver o veículo ao estoque e zerar a comissão
- Converter-se para uma linha de texto e ser recriada a partir dela

**Colaboradores**
- Cliente
- Vendedor
- Gerente
- Veiculo
- FormaPagamento
- Estoque
- VendaInvalidaException
- PermissaoNegadaException

---

## FormaPagamento (classe abstrata)

**Superclasse:** nenhuma | **Subclasses:** Dinheiro, Cartao, Financiamento

**Responsabilidades**
- Definir `calcularValorFinal(precoBase)` como método virtual puro
- Definir `descricao()` para exibir o pagamento ao usuário
- Validar dados comuns do pagamento (valores não negativos)

**Colaboradores**
- Venda
- PagamentoInvalidoException

---

## Dinheiro

**Superclasse:** FormaPagamento

**Responsabilidades**
- Aplicar o desconto à vista sobre o preço base
- Rejeitar percentual de desconto inválido

**Colaboradores**
- FormaPagamento
- PagamentoInvalidoException

---

## Cartao

**Superclasse:** FormaPagamento

**Responsabilidades**
- Guardar número de parcelas e taxa de juros
- Calcular o valor final com juros e o valor de cada parcela
- Rejeitar número de parcelas inválido (<= 0 ou acima do limite)

**Colaboradores**
- FormaPagamento
- PagamentoInvalidoException

---

## Financiamento

**Superclasse:** FormaPagamento

**Responsabilidades**
- Guardar entrada, prazo em meses e taxa mensal
- Calcular saldo financiado, parcela mensal e total pago
- Rejeitar entrada maior que o preço ou prazo inválido

**Colaboradores**
- FormaPagamento
- PagamentoInvalidoException

---

## RelatorioVendas

**Superclasse:** nenhuma

**Responsabilidades**
- Listar vendas concluídas em um período
- Calcular o total faturado no período, ignorando vendas canceladas
- Listar as vendas de um cliente
- Somar a comissão de cada vendedor em um período

**Colaboradores**
- Venda
- Cliente
- Vendedor
- Loja

---

## PagamentoInvalidoException

**Superclasse:** std::exception

**Responsabilidades**
- Representar erro em dados de pagamento, com mensagem clara
- Ser capturada no menu para mostrar o erro sem encerrar o programa

**Colaboradores**
- FormaPagamento e subclasses
- Loja

---

## VendaInvalidaException

**Superclasse:** std::exception

**Responsabilidades**
- Representar erro no estado ou nos dados de uma venda (cancelar venda já cancelada, linha de arquivo corrompida)
- Permitir que a leitura de `vendas.txt` ignore a linha ruim e continue

**Colaboradores**
- Venda
- Loja

---

## PermissaoNegadaException

**Superclasse:** std::exception

**Responsabilidades**
- Representar a recusa de uma operação por falta de autorização (desconto acima do limite sem aprovação do gerente)

**Colaboradores**
- Venda
- Gerente

---

## Interfaces esperadas das outras áreas

Combinar com o grupo antes do C6, para os `.hpp` não divergirem.

| Classe (área) | O que a Venda precisa dela |
|---------------|----------------------------|
| Veiculo (Veículos) | `getPreco()` e identificação do modelo |
| Estoque (Estoque e Persistência) | `retirar(modelo)` e `devolver(modelo)`, lançando exceção se não houver unidade |
| Cliente (Pessoas) | identificação única (por exemplo CPF ou id) e nome |
| Vendedor e Gerente (Pessoas) | `calcularComissao(valorVenda)` polimórfico e `getId()` |
| Gerente (Pessoas) | `aprovarDesconto(...)` |
| Persistência (Estoque e Persistência) | quem lê e grava `data/vendas.txt`, usando o texto que `Venda` gera e interpreta |
| Loja (Infra) | guarda a lista de vendas e captura as exceções no menu |
