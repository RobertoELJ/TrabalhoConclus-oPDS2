# Sistema de Gerenciamento de Loja de Carros

Projeto final de Programação e Desenvolvimento de Software 2 (UFMG).

## Tema

Sistema de gerenciamento de uma loja/concessionária de veículos: cadastro de modelos, controle de estoque, cadastro de clientes e funcionários, e registro de vendas com diferentes formas de pagamento.

## Divisão de tarefas

| Área                   | Responsável                    | Classes principais                          |
|------------------------|--------------------------------|---------------------------------------------|

| Veículos               | Matheus Soares Fagundes Meira  | Veiculo e subclasses, ModeloVeiculo         |

| Estoque e Persistência | Suzane Ferreira                | Estoque, leitura e escrita dos arquivos em `data/`    |

| Pessoas                | Roberto Emilio Lopes Junior    | Pessoa, Cliente, Funcionario, Vendedor, Gerente    |

| Vendas e Pagamentos    | Marco Antonio Ramalho dos Reis | Venda, Carrinho, FormaPagamento e subclasses |

| Infra e Testes         | Alexandre Ailon Martins Alves  | Makefile, testes de unidade, menu (Loja)     |

## Estrutura de diretórios

- `src/` — implementação (.cpp)
- `include/` — cabeçalhos (.hpp)
- `tests/` — testes de unidade
- `build/` — arquivos gerados na compilação
- `design/` — User Stories e Cartões CRC de cada área
- `commits_teste/` — arquivos de commit de teste (C3) de cada membro

## Como compilar e rodar

Precisa de g++ com C++11, make e, para a cobertura, gcovr (`pip install gcovr`).

| Comando | O que faz |
|---|---|
| `make` | compila o programa em `build/` |
| `make run` | compila e executa o programa |
| `make test` | compila e roda os testes de unidade (doctest, `tests/teste_*.cpp`) |
| `make coverage` | roda os testes e mostra a cobertura de `src/` com gcovr (mínimo de 60%) |
| `make clean` | apaga os arquivos gerados |

O Makefile usa sozinho todos os `.cpp` de `src/` e todos os `tests/teste_*.cpp`; basta o arquivo existir na pasta. Só `teste_main.cpp` define o `main` do doctest.

## Vendas e Pagamentos

- `FormaPagamento` é abstrata; `Dinheiro`, `Pix`, `Cartao`, `Boleto` e `Financiamento` calculam o valor final cada uma do seu jeito.
- `Carrinho` guarda os itens (`ItemCarrinho`) e calcula o total.
- `Venda` junta cliente, vendedor, carrinho e pagamento: confere o desconto com o gerente, calcula a comissão, cancela e gera o comprovante. Dar baixa no estoque é papel de quem chama (o Caixa).
- `RelatorioVendas` soma o total vendido e a comissão de um vendedor num período (datas `AAAA-MM-DD`; vendas canceladas ficam de fora).
- Erros: `PagamentoInvalidoException` e `PermissaoNegadaException`.
