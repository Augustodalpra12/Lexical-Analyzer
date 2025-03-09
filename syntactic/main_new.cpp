#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <algorithm>
#include "grammar.cpp"  // Certifique-se de que grammar.cpp NÃO define outra main()
using namespace std;

// Função para remover os símbolos '<' e '>' de uma string
string removeSymbols(const string& str) {
    string result;
    for (char ch : str) {
        if (ch != '<' && ch != '>') {
            result += ch;
        }
    }
    return result;
}

// Função para inverter a ordem dos tokens de uma produção
vector<string> reverseTokens(const string& str) {
    istringstream iss(str);
    vector<string> tokens;
    string token;
    
    // Tokeniza a string por espaços e remove '<' e '>'
    while (iss >> token) {
        token = removeSymbols(token);
        tokens.push_back(token);
    }
    
    // Inverte a ordem dos tokens para empilhamento
    reverse(tokens.begin(), tokens.end());
    return tokens;
}

// Função auxiliar para imprimir a pilha sem perder seus elementos
void printStackWithoutLosingElements(stack<string>& pilha) {
    vector<string> temp;
    stack<string> copy = pilha; // Faz uma cópia da pilha
    while (!copy.empty()) {
        temp.push_back(copy.top());
        copy.pop();
    }
    for (int i = temp.size() - 1; i >= 0; --i) {
        cout << temp[i] << " ";
    }
    cout << endl;
}

int main() {
    // Carrega as regras na grammarMap chamando addRules()
    addRules();
    
    // Exibe a gramática carregada
    cout << "Gramática:" << endl;
    // displayGrammar();
    cout << "-------------------------------------" << endl;

    // Abre o arquivo de entrada (gerado pelo analisador léxico)
    ifstream file("../lex/outputLex.txt");
    if (!file) {
        cerr << "Erro ao abrir o arquivo de entrada!" << endl;
        return 1;
    }
    
    // A fila 'entrada' armazena vetores com 3 posições:
    // [0] = token (tipo), [1] = lexema, [2] = número da linha
    queue<vector<string>> entrada;
    string linha;
    while (getline(file, linha)) {
        vector<string> vetor(3);
        // Remove os colchetes da linha
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
    
    // Adiciona um marcador de fim de entrada
    entrada.push({"$", "$", "$"});

    // Inicializa a pilha do analisador com o símbolo final e o símbolo inicial "S"
    stack<string> pilha;
    pilha.push("$");
    pilha.push("S"); // Símbolo inicial da gramática

    bool error = false;
    
    // Loop principal do analisador sintático
    while (!entrada.empty() && !pilha.empty()) {
        vector<string> tokenInfo = entrada.front();
        string tokenAtual = tokenInfo[0]; // Token lido da entrada
        
        // Se o símbolo no topo da pilha for um não-terminal presente na grammarMap
        if (grammarMap.find(pilha.top()) != grammarMap.end()) {
            string nonTerminal = pilha.top();
            Rule regra = grammarMap[nonTerminal];
            
            // Verifica se o terminal associado à regra corresponde ao token atual
            if (regra.terminal == tokenAtual) {
                // Remove o não-terminal da pilha
                pilha.pop();
                // Obtém os símbolos da produção e inverte sua ordem para empilhar
                vector<string> invertedTokens = reverseTokens(regra.production);
                
                // Se a produção não for ε (vazia) ou sinal de sincronização ("sinc")
                if (!invertedTokens.empty() && invertedTokens[0] != "ε" && invertedTokens[0] != "sinc") {
                    for (const auto& sym : invertedTokens) {
                        pilha.push(sym);
                    }
                } else if (!invertedTokens.empty() && invertedTokens[0] == "sinc") {
                    cout << "SINC: Erro de Sincronização para o não-terminal: " << nonTerminal << endl;
                    // Em caso de erro de sincronização, remove o símbolo da pilha
                    pilha.pop();
                }
            } else {
                // Caso o token atual não corresponda ao terminal esperado para o não-terminal
                cout << "Token não esperado: " << tokenAtual 
                     << ", correspondente ao lexema: " << tokenInfo[1] 
                     << ", na linha: " << tokenInfo[2] << endl;
                cout << "Para o não-terminal \"" << nonTerminal 
                     << "\" esperava o token: " << regra.terminal << endl;
                entrada.pop();
                error = true;
                continue; // Pula para a próxima iteração
            }
        } else {
            // Se o símbolo no topo da pilha for terminal
            if (pilha.top() == tokenAtual) {
                // Token esperado; remove ambos da pilha e da entrada
                pilha.pop();
                entrada.pop();
            } else {
                cout << "Token não esperado: " << tokenAtual 
                     << ", correspondente ao lexema: " << tokenInfo[1] 
                     << ", na linha: " << tokenInfo[2] << endl;
                cout << "Esperava o token: " << pilha.top() << endl;
                entrada.pop();
                error = true;
            }
        }
        
        // (Opcional) Exibe o estado atual da pilha:
        // cout << "Pilha atual: ";
        // printStackWithoutLosingElements(pilha);
    }
    
    if (error) {
        cout << "Análise sintática concluída com erros." << endl;
    } else {
        cout << "Análise sintática concluída com sucesso." << endl;
    }
    
    return 0;
}
