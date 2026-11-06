# Makefile
# Refazendo com wildcard e filter-out pra diminuir erros- Suzane

CXX = g++
CXXFLAGS = -std=c++11 -Wall -I include/ --coverage

TARGET = build/loja_carro
TEST_TARGET = build/test_loja

# Separando o main para não dar conflito com os testes
MAIN_SRC = src/main.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

<<<<<<< HEAD
# COLOQUEM OS SEUS ARQUIVOS .cpp AQUI EMBAIXO pf!
# Não esqueçam de colocar a barra invertida \ no final da linha ao adicionar
SRC_FILES = src/Estoque.cpp \
			src/GerenciadorDeArquivos.cpp \
            src/GerenciamentoDeClientes.cpp 

# COLOQUEM OS SEUS ARQUIVOS DE TESTE AQUI EMBAIXO!
TEST_FILES = tests/teste_main.cpp \
			tests/teste_estoque.cpp \
			tests/teste_persistencia.cpp \
            tests/teste_GerenciadorDeCliente.cpp
			# MARCO ANTONIO
TEST_FILES += tests/teste_boleto.cpp \
			tests/teste_carrinho.cpp \
			tests/teste_cartao.cpp \
			tests/teste_dinheiro.cpp \
			tests/teste_excecoes.cpp \
			tests/teste_financiamento.cpp \
			tests/teste_item_carrinho.cpp \
			tests/teste_pix.cpp \
			tests/teste_polimorfismo_pagamento.cpp \
			tests/teste_relatorio_vendas.cpp \
			tests/teste_venda.cpp 
=======
# Busca automática de todos os .cpp em src/, excluindo o main.cpp
SRC_FILES = $(filter-out $(MAIN_SRC), $(wildcard src/*.cpp))

# Busca automática de todos os arquivos de teste na pasta tests/
TEST_FILES = $(wildcard tests/*.cpp)
>>>>>>> 6dba5e13f6db01fd78dd30672431c7efa4312e84

OBJ_FILES = $(SRC_FILES:.cpp=.o)
TEST_OBJ_FILES = $(TEST_FILES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN_OBJ) $(OBJ_FILES)

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(OBJ_FILES) $(TEST_OBJ_FILES)

coverage: test
	gcovr -r . --html --html-details -o build/coverage.html

clean:
	rm -f src/*.o tests/*.o build/* *.gcda *.gcno *.html