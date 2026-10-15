# Makefile
# Fazendo a base e minhas partes de estoque e persistência - Suzane

CC = g++
CFLAGS = -std=c++11 -Wall -I include/ --coverage

TARGET = build/loja_carro
TEST_TARGET = build/test_loja

# COLOQUEM OS SEUS ARQUIVOS .cpp AQUI EMBAIXO pf!
# Não esqueçam de colocar a barra invertida \ no final da linha ao adicionar
RC_FILES = src/main.cpp \
            src/Estoque.cpp \
            src/GerenciadorDeArquivos.cpp
            # MATHEUS \
            # ROBERTO \
            # MARCO ANTONIO \



# COLOQUEM OS SEUS ARQUIVOS DE TESTE AQUI EMBAIXO!

TEST_FILES = tests/test_main.cpp \ 
             tests/test_estoque.cpp \
             tests/test_persistencia.cpp
             # MATHEUS \
             # ROBERTO \
             # MARCO ANTONIO \


OBJ_FILES = $(SRC_FILES:.cpp=.o)
TEST_OBJ_FILES = $(TEST_FILES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJ_FILES)


coverage: test
	gcovr -r . --html --html-details -o build/coverage.html

clean:
	rm -f src/*.o tests/*.o build/* *.gcda *.gcno *.html