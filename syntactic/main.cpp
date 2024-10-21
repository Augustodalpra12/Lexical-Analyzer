#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include <queue>
#include <stack>
#include "grammar.cpp"
using namespace std;

int main() {
    ifstream file("../lex/outputLex.txt");

    if (!file)
    {
        cerr << "Erro ao abrir o file!" << endl;
        return 1;
    }
    queue<vector<string>> entrada; // fila de vetores
    
    string linha;

    while (getline(file, linha)) {
        vector<string> vetor(3); // Vetor de 3 posições

        // Remove os colchetes e a vírgula
        linha.erase(remove(linha.begin(), linha.end(), '['), linha.end());
        linha.erase(remove(linha.begin(), linha.end(), ']'), linha.end());
        
        stringstream ss(linha); // Cria um stream a partir da linha
        string elemento;
        int index = 0;

        // Divide a linha em elementos
        while (getline(ss, elemento, ',')) {
            if (index < 3) { // Certifica-se de que não excede 3 elementos
                vetor[index++] = elemento; // Armazena cada elemento no vetor
            }
        }

        entrada.push(vetor); // Adiciona o vetor à fila
    }
    file.close(); // Fecha o arquivo

    // while (!entrada.empty()) {
    //     vector<string> item = entrada.front();
    //     entrada.pop();

    //     // Imprime o vetor
    //     cout << "[";
    //     for (size_t i = 0; i < item.size(); i++) {
    //         cout << item[i];
    //         if (i < item.size() - 1) {
    //             cout << ", ";
    //         }
    //     }
    //     cout << "]" << endl;
    // }
    stack <string> pilha;
    pilha.push("S");
    unordered_map<string, vector<string>> grammar = getGrammar();
    unordered_map <string, vector<string>> table = getTable();
    bool error = false;
    while(!entrada.empty() || error) {
        vector<string> item = entrada.front();
        if(table.find(pilha.top())) {
            
        }
    }



    return 0;   
}