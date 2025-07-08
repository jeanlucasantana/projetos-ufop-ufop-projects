# Variáveis
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXEC = program

# Regra padrão: compilar tudo
all: $(EXEC)

# Como gerar o executável
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Como compilar cada arquivo .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar objetos e executável
clean:
	rm -f $(OBJECTS) $(EXEC)

# Rodar o programa
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run