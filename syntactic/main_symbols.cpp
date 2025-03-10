#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include <queue>
#include <stack>
#include "grammar_old.cpp"
using namespace std;

struct Symbol {
    string type;
    string value;
};

unordered_map<string, Symbol> symbolTable;

void insertSymbol(const string& name, const string& type, const string& value = "") {
    if (symbolTable.find(name) == symbolTable.end()) {
        symbolTable[name] = {type, value};
    } else {
        cout << "Erro: Variável '" << name << "' já declarada." << endl;
    }
}

bool symbolExists(const string& name) {
    return symbolTable.find(name) != symbolTable.end();
}

void printSymbolTable() {
    cout << "Tabela de Símbolos:" << endl;
    for (const auto& pair : symbolTable) {
        cout << "Nome: " << pair.first << ", Tipo: " << pair.second.type << ", Valor: " << pair.second.value << endl;
    }
}

// Função para remover '<' e '>' de uma string
string removeSymbols(const string& str) {
    string result;
    for (char ch : str) {
        if (ch != '<' && ch != '>') {
            result += ch;
        }
    }
    return result;
}



vector<string> reverseTokens(const string& str) {
    istringstream iss(str);
    vector<string> tokens;
    string token;

    // Tokenizar a string por espaços
    while (iss >> token) {
        // Remover os símbolos < e >
        token = removeSymbols(token);
        tokens.push_back(token);
    }

    // Inverter a ordem dos tokens
    reverse(tokens.begin(), tokens.end());

    return tokens;  // Retorna o vetor de tokens invertidos
}

int main() {
    ifstream file("../lex/outputLex.txt");
    if (!file) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    queue<vector<string>> entrada;
    string linha;
    while (getline(file, linha)) {
        vector<string> vetor(3);
        linha.erase(remove(linha.begin(), linha.end(), '['), linha.end());
        linha.erase(remove(linha.begin(), linha.end(), ']'), linha.end());
        stringstream ss(linha);
        string elemento;
        int index = 0;
        while (getline(ss, elemento, ',')) {
            if (index < 3) {
                vetor[index++] = elemento;
            }
        }
        entrada.push(vetor);
    }
    file.close();

    stack<string> pilha;
    pilha.push("$");
    pilha.push("S");
    unordered_map<string, unordered_map<string, string>> table = getTable();
    unordered_map<string, string> terminals = getTerminals();
    entrada.push({"$", "$", "$"});
    bool error = false;
    bool running = true;
    
    while (running) {
        vector<string> item = entrada.front();
        auto it = table.find(pilha.top());
        if (it != table.end()) {
            auto it2 = it->second.find(item[0]);
            if (it2 != it->second.end()) {
                pilha.pop();
                vector<string> invertedTokens = reverseTokens(it2->second);
                if (!(invertedTokens[0] == "ε") && !(invertedTokens[0] == "sinc")) {
                    for (const auto& token : invertedTokens) {
                        pilha.push(token);
                    }
                } else if (invertedTokens[0] == "sinc") {
                    cout << "SINC: Erro de Sincronização" << endl;
                    pilha.pop();
                }
            } else {
                cout << "Erro: Token inesperado '" << item[0] << "' na linha " << item[2] << endl;
                entrada.pop();
                error = true;
            }
        } else {
            if (pilha.top() == item[0]) {
                if (pilha.top() == "IDENTIFIER") {
                    insertSymbol(item[1], "desconhecido");
                }
                entrada.pop();
                pilha.pop();
            } else {
                cout << "Erro: Esperava '" << pilha.top() << "', mas encontrou '" << item[0] << "' na linha " << item[2] << endl;
                entrada.pop();
                error = true;
            }
        }
        if (entrada.empty() || pilha.top() == "$") {
            running = false;
        }
    }

    printSymbolTable();
    return 0;
}