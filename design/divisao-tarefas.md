# Divisão de tarefas

| Área | Responsável | Classes principais |
|------|-------------|--------------------|
| Veículos | Matheus Soares Fagundes Meira | Veiculo e subclasses, ModeloVeiculo |
| Estoque e Persistência | Suzane Ferreira | Estoque, leitura e escrita dos arquivos em `data/` |
| Pessoas | Roberto | Pessoa, Cliente, Funcionario, Vendedor, Gerente |
| Vendas e Pagamentos | Marco Antonio Ramalho dos Reis | Venda, FormaPagamento e subclasses |
| Infra e Testes | Alexandre Ailon Martins Alves | Makefile, testes de unidade, menu (Loja) |

## Ligações entre as áreas de Vendas e as demais

- **Veículos (Matheus):** a `Venda` precisa do preço e da identificação do modelo.
- **Estoque (Suzane):** a `Venda` precisa retirar e devolver uma unidade, e alguém precisa ler e gravar `data/vendas.txt`.
- **Pessoas (Roberto):** a `Venda` precisa do cliente, do vendedor e da comissão de cada funcionário.
- **Infra (Alexandre):** o menu chama a `Venda` e captura as exceções, e os testes cobrem as três hierarquias.
