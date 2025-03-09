# Variáveis
LEX_DIR = ./lex
SINTATIC_DIR = ./syntactic

# Definir o compilador
CXX = g++
CXXFLAGS = -std=c++11

# Alvos
.PHONY: all lex sintatic clean

all: lex sintatic

lex:
	@echo "Compilando e executando em ./lex..."
	cd $(LEX_DIR) && $(CXX) -o main main.cpp regex_definitions.h regex_functions.h
	cd $(LEX_DIR) && ./main

sintatic:
	@echo "Compilando e executando em ./sintatic..."
	cd $(SINTATIC_DIR) && $(CXX) main.cpp -o main
	cd $(SINTATIC_DIR) && ./main

clean:
	@echo "Limpando os arquivos compilados..."
	rm -f $(LEX_DIR)/main $(SINTATIC_DIR)/main
