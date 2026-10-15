# Makefile
# Fazendo a base e minhas partes de estoque e persistência - Suzane

CXX = g++
CXXFLAGS = -std=c++11 -Wall -I include/ --coverage

TARGET = build/loja_carro
TEST_TARGET = build/test_loja

# Separando o main para não dar conflito com os testes
MAIN_SRC = src/main.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

# COLOQUEM OS SEUS ARQUIVOS .cpp AQUI EMBAIXO pf!
# Não esqueçam de colocar a barra invertida \ no final da linha ao adicionar
SRC_FILES = src/Estoque.cpp \
			src/GerenciadorDeArquivos.cpp
			# MATHEUS \
			# ROBERTO \
			# MARCO ANTONIO \

# COLOQUEM OS SEUS ARQUIVOS DE TESTE AQUI EMBAIXO!
TEST_FILES = tests/teste_main.cpp \
			tests/teste_estoque.cpp \
			tests/teste_persistencia.cpp
			# MATHEUS \
			# ROBERTO \
			# MARCO ANTONIO \

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