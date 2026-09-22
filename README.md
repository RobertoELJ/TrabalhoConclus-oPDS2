# Sistema de Gerenciamento de Loja de Carros

Projeto final de Programação e Desenvolvimento de Software 2 (UFMG).

## Tema

Sistema de gerenciamento de uma loja/concessionária de veículos: cadastro de modelos, controle de estoque, cadastro de clientes e funcionários, e registro de vendas com diferentes formas de pagamento.

## Divisão de tarefas

| Área | Responsável | Classes principais |
|------|-------------|---------------------|
| Veículos | Matheus Soares Fagundes Meira | Veiculo e subclasses, ModeloVeiculo |
| Estoque e Persistência | Suzane Ferreira | Estoque, leitura e escrita dos arquivos em `data/` |
| Pessoas | Roberto | Pessoa, Cliente, Funcionario, Vendedor, Gerente |
| Vendas e Pagamentos | Marco Antonio Ramalho dos Reis | Venda, FormaPagamento e subclasses |
| Infra e Testes | Alexandre Ailon Martins Alves | Makefile, testes de unidade, menu (Loja) |

## Estrutura de diretórios

- `src/` — implementação (.cpp)
- `include/` — cabeçalhos (.hpp)
- `tests/` — testes de unidade
- `build/` — arquivos gerados na compilação
- `design/` — User Stories e Cartões CRC de cada área

## Como compilar e rodar

(a preencher pelo grupo junto do Makefile no checkpoint C7)
