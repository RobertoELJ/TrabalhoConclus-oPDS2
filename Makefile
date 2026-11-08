# Makefile
# Refazendo com wildcard e filter-out pra diminuir erros- Suzane

CXX = g++
CXXFLAGS = -std=c++11 -Wall -I include/ --coverage

TARGET = build/loja_carro
TEST_TARGET = build/test_loja

# Separando o main para não dar conflito com os testes
MAIN_SRC = src/main.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

# Busca automática de todos os .cpp em src/, excluindo o main.cpp
SRC_FILES = $(filter-out $(MAIN_SRC), $(wildcard src/*.cpp))

# Busca automática de todos os arquivos de teste na pasta tests/
TEST_FILES = $(wildcard tests/*.cpp)

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