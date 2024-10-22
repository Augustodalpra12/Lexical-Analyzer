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

// Função para inverter a ordem dos tokens em uma string
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
    stack<string> pilha;
    pilha.push("$");
    pilha.push("S");
    unordered_map<string, vector<string>> grammar = getGrammar();
    unordered_map <string, unordered_map<string, string>> table = getTable();
    bool error = false;
    entrada.push({"$", "$", "$"});
    bool teste = true;
    int count = 0;
    // while(!entrada.empty() || error) {
    while (teste){

    
        vector<string> item = entrada.front();
        
        auto it = table.find(pilha.top());
        if (it != table.end()) {
             // pilha.top() is a key in the table
            auto it2 = it->second.find(item[0]);
            if (it2 != it->second.end()) {
                // item[0] is a key in the table[pilha.top()]
                pilha.pop();
                // antes de realizar o pilha.push abaixo
                // inverta a ordem do it2 -> second e retire todos oos < e >, tem que fazer e retirar <>
                // por exemplo se tiver "<ATTRIBUTION> <CODE_BLOCK>" no it2->second, ele deve ficar "CODE_BLOCK ATTRIBUTION"
                vector<string> invertedTokens = reverseTokens(it2->second);

                // Empilhar a string invertida e limpa
                 for (const auto& token : invertedTokens) {
                    pilha.push(token);
                }
                // pilha.push(invertedAndCleaned);
                // pilha.push(it2->second); 
                
            } else {
                // erro
                error = true;
            }
            // do something with values


        } else {
            error = true;
            // erro
        }
        cout << "---------------------------------------------------" << endl;
        cout << "Pilha: " << pilha.top() << endl;
        cout << "Entrada: " << item[0] << endl;
        if(pilha.top() == item[0]) {
            entrada.pop();
            pilha.pop();
        }
        item = entrada.front();
        cout << "Pilha atual: " << pilha.top() << endl;
        cout << "Entrada atual: " << item[0] << endl;
        
        count++;
        if(count == 15){
            break;
        }
        // teste = false;
        

    }



    return 0;   
}