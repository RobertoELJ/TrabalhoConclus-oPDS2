CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude -Itests

ifeq ($(OS),Windows_NT)
EXE = .exe
endif

SRC     = $(filter-out src/main.cpp,$(wildcard src/*.cpp))
TESTES  = $(wildcard tests/teste_*.cpp)
APP     = build/loja$(EXE)
TESTAPP = build/testes$(EXE)

.PHONY: all run test coverage clean

all: $(APP)

$(APP): src/main.cpp $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(APP)
	./$(APP)

test: $(TESTAPP)
	./$(TESTAPP)

$(TESTAPP): $(TESTES) $(SRC)
	$(CXX) $(CXXFLAGS) --coverage -O0 $^ -o $@

coverage: clean test
	gcovr -r . --filter src/ --print-summary --fail-under-line 60

clean:
	rm -f build/loja build/loja.exe build/testes build/testes.exe build/*.gcno build/*.gcda
