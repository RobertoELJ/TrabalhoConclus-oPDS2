# Sistema de Gerenciamento de Loja de Carros

## Integrantes
- Alexandre Ailon Martins Alves
- Marco Antonio Ramalho dos Reis
- Matheus Soares Fagundes Meira
- Roberto Emilio Lopes Junior
- Suzane Ferreira

## Definição:

Uma loja de carros precisa controlar, ao mesmo tempo, os veículos que tem para vender, as unidades em estoque, os clientes cadastrados, os vendedores e as vendas feitas. Quando isso é anotado à mão ou em planilhas soltas, é fácil cadastrar o mesmo veículo duas vezes, vender mais unidades do que existem, aceitar dados inválidos (CPF, e-mail, preço) ou perder as informações ao fechar o programa. Cada venda ainda envolve regras próprias: forma de pagamento, desconto que depende de aprovação e comissão do vendedor.

## Objetivos:

- Cadastrar, consultar e atualizar veículos, sem permitir placas repetidas.
- Controlar o estoque de produtos, com baixa a cada venda e aviso de produto esgotado.
- Cadastrar clientes com validação de nome, e-mail e CPF.
- Registrar vendas com diferentes formas de pagamento, desconto aprovado por gerente e cálculo da comissão do vendedor.
- Gerar relatórios de vendas por período, por vendedor e por cliente.
- Guardar os dados em arquivos de texto, para que nada se perca ao fechar o programa.
- Tratar entradas inválidas com exceções, em vez de deixar o programa travar.

## Motivação:

O tema surgiu como uma ideia de  integrante do grupo, e o grupo aderiu. Não partimos de um problema real de uma loja específica, apenas escolhemos loja de carros por ser um domínio fácil de entender para todos e para diferenciar dos outros grupos. 

## Funcionalidades:

O programa abre um menu no terminal com as áreas do sistema:

Gerenciar veículos - Cadastrar, buscar por placa, atualizar e listar veículos 
Gerenciar estoque - Cadastrar produtos, repor quantidade, dar baixa e consultar 
Gerenciar clientes - Cadastrar, alterar nome e e-mail, e listar clientes 
Gerenciar vendedores - Dados e comissão dos vendedores 
Realizar venda - Montar o carrinho e fechar a venda com forma de pagamento e desconto 
Acessar caixa - Iniciar a venda, escolher o pagamento e finalizar 
Relatórios - Total vendido e comissão por período, e compras de um cliente 

## Organização do código

Cada área do sistema fica sob responsabilidade de um integrante. Cada classe tem seu próprio par `.hpp`/`.cpp`.

Veículos - Matheus Soares Fagundes Meira ( `Veiculo`, `CadastroVeiculos`, `Vendedor` )
Estoque e persistência | Suzane Ferreira ( `Estoque`, `GerenciadorDeArquivos` )
Pessoas - Roberto Emilio Lopes Junior ( `Cliente`, `Gerente`, `GerenciamentoDeClientes` )
Vendas e pagamentos - Marco Antonio Ramalho dos Reis ( `Venda`, `Carrinho`, `ItemCarrinho`,`RelatorioVendas`, `FormaPagamento` e as subclasses `Dinheiro`, `Pix`, `Cartao`, `Boleto` e `Financiamento`, `PagamentoInvalidoException`, `PermissaoNegadaException` )
Caixa e menu - Alexandre Ailon Martins Alves ( `Caixa` e o menu principal (`main.cpp`) )


### Pagamento e venda

- `Venda` confere o desconto com o gerente, calcula a comissão do vendedor, pode ser cancelada e gera o comprovante.
- `Carrinho` guarda os itens e calcula o total.
- `RelatorioVendas` soma o total vendido e a comissão de um vendedor num período (datas `AAAA-MM-DD`) e lista as compras de um cliente pelo CPF. Vendas canceladas ficam de fora.
- Dar baixa no estoque é papel de quem chama a venda (o `Caixa`).

## Estrutura de diretórios

- `src/`: implementação (`.cpp`)
- `include/`: cabeçalhos (`.hpp`)
- `tests/`: testes de unidade (`teste_*.cpp`) e o `doctest.h`
- `data/`: arquivos de dados gravados pelo programa
- `build/`: arquivos gerados na compilação (não vão para o Git)
- `design/`: User Stories e Cartões CRC de cada área
- `doxygen_docs/`: documentação gerada pelo Doxygen
- `commits_teste/`: arquivos de commit de teste (C3) de cada integrante

## Como compilar e executar

Requisitos: `g++` com suporte a C++11 e `make`. Para a cobertura, também `gcovr` (`pip install gcovr`). No Windows, use o terminal do MSYS2/MinGW e troque `make` por `mingw32-make`.

 `make` - Compila o programa em `build/` 
 `make run` - Compila e executa o programa 
 `make test` - Compila e executa os testes de unidade 
 `make coverage` - Executa os testes e gera o relatório de cobertura em `build/coverage.html` 
 `make clean` - Apaga os arquivos gerados 

O `Makefile` usa sozinho todos os `.cpp` de `src/` e todos os `tests/teste_*.cpp`. Para incluir uma classe ou um teste novo, basta criar o arquivo na pasta. Só o `teste_main.cpp` define o `main` do doctest.

## Testes

Os testes de unidade usam o [doctest](https://github.com/doctest/doctest) (`tests/doctest.h`, versão 2.4.12) e seguem a abordagem de desenvolvimento orientado a testes. Há um arquivo de teste por classe ou área, e eles cobrem tanto os casos normais quanto as entradas inválidas e as exceções. A meta é cobertura de pelo menos 60% do código de `src/`; rode `make coverage` para ver o número atual.

## Persistência de dados

O estoque é gravado em `data/estoque.txt`, com um produto por linha, no formato:

```
id;descricao;quantidade
```

Ao abrir, o programa lê esse arquivo (e o cria vazio se ainda não existir); ao fechar, grava o estoque atual. Se uma linha estiver inválida, o erro informa o arquivo e o número da linha, e nada é carregado pela metade.

## Tratamento de erros

Entradas inválidas lançam exceções com mensagens claras:

- **Estoque:** `std::invalid_argument` (ID, descrição ou quantidade inválidos), `std::out_of_range` (produto inexistente), `std::runtime_error` (baixa maior que o saldo) e `std::overflow_error`.
- **Arquivos:** `std::runtime_error` quando o arquivo não abre, não grava ou tem linha inválida.
- **Clientes:** `std::invalid_argument` (nome, e-mail ou CPF inválidos, CPF repetido) e `std::out_of_range` (ID inexistente).
- **Veículos e vendedores:** `std::invalid_argument` para marca, modelo, ano, preço, nome, ID ou comissão inválidos.
- **Pagamento e venda:** `PagamentoInvalidoException` (dado inválido ou valor pago insuficiente) e `PermissaoNegadaException` (desconto sem aprovação do gerente). O `Caixa` captura os erros e mostra a mensagem sem derrubar o programa.

## Documentação

- **Doxygen:** todos os métodos públicos têm comentários `/** ... */`. Para gerar a documentação, rode `doxygen doxygen.txt` na raiz do projeto e abra `doxygen_docs/html/index.html`.
- **Modelagem:** as User Stories e os Cartões CRC de cada área estão em `design/`.

## Participação

O desenvolvimento foi dividido por áreas, e a participação de cada integrante é medida pelos commits feitos no repositório, com o nome e o e-mail cadastrados no Moodle.
