#include "../lex/regex_definitions.h" // Arquivo de regex externo
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

int tempVarCount = 0; // Contador de variáveis temporárias
int labelCount = 0; // Contador de rótulos

// Função para gerar código intermediário ETAC a partir do código-fonte
void generateETAC(const string& sourceCode, ofstream& outFile) {
    smatch match;
    string temp = sourceCode;
    vector<set<string>> scopeStack;
    scopeStack.push_back(set<string>()); // Escopo global

    // Remove espaços extras
    temp = regex_replace(temp, regex("\\s+"), " ");

    // Regex para declarações de variáveis: tipo id (= valor)?
    regex declarationRegex(R"(\s*(int|double|str|bool)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*(=\s*([^.]+))?\s*.)");
    if (regex_match(temp, match, declarationRegex)) {
        string varType = match[1].str();  // Tipo (ex.: "int")
        string varName = match[2].str();  // Nome da variável (ex.: "x")
        string value = match[4].str();    // Valor, se presente (ex.: "0")

        // Mapeia o tipo da linguagem fonte para o tipo ETAC
        string etacType = (varType == "int") ? "i32" : 
                          (varType == "double") ? "f64" : 
                          (varType == "str") ? "str" : "bool";
        string defaultVal = (varType == "int") ? "0" : 
                            (varType == "double") ? "0.0" : 
                            (varType == "str") ? "\"\"" : "false";

        // Gera a saída ETAC
        if (!value.empty()) {
            outFile << varName << ": " << etacType << " = " << value << endl;
        } else {
            outFile << varName << ": " << etacType << " = " << defaultVal << endl;
        }
        scopeStack.back().insert(varName); // Adiciona a variável ao escopo
        return;
    }

    // Regex para atribuições: id = valor
    regex assignmentRegex(R"(\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([^.]+)\s*.)");
    if (regex_match(temp, match, assignmentRegex)) {
        string varName = match[1].str();   // Nome da variável
        string expression = match[2].str(); // Expressão ou valor (ex.: "10")

        // Gera a saída ETAC (assume valor literal; expressões complexas exigiriam parsing adicional)
        outFile << varName << " = " << expression << endl;
        return;
    }

    // Regex para comandos de impressão: prt(expressão)
    regex printRegex(R"(\s*prt\(([^)]+)\)\s*.)");
    regex quotesRegex(R"("[^"]*")"); // Para strings entre aspas
    regex idRegex(R"([a-zA-Z_][a-zA-Z0-9_]*)"); // Para identificadores
    if (regex_match(temp, match, printRegex)) {
        string content = match[1].str(); // Conteúdo entre parênteses

        if (regex_match(content, quotesRegex)) {
            // String literal
            string value = content.substr(1, content.length() - 2); // Remove aspas
            outFile << "call write_string(\"" << value << "\")" << endl;
        } else if (regex_match(content, idRegex)) {
            // Variável
            outFile << "call write_int(" << content << ")" << endl;
        }
        return;
    }

    // Comando de leitura
    if (regex_search(temp, match, reserved_scn)) {
        if (regex_search(temp, match, id)) {
            string varName = match.str();
            outFile << "call read_int(" << varName << ")" << endl; // Agora a variável é passada corretamente
        }
    }

    // Estruturas de controle de fluxo (loops)
    if (regex_search(temp, match, laps)) {
        scopeStack.push_back(set<string>());
        string Lstart = "label_" + to_string(labelCount++);
        string Lexit = "label_" + to_string(labelCount++);
        string loopVar = "t" + to_string(tempVarCount++);
        outFile << loopVar << ": u8 = 0u8" << endl;
        outFile << "loop:" << endl;
        outFile << "  if " << loopVar << " >= 50u8 goto " << Lexit << endl;
        outFile << "  " << loopVar << ": u8 = " << loopVar << " + 1u8" << endl;
        outFile << "  goto loop" << endl;
        outFile << Lexit << ":" << endl;
        scopeStack.pop_back();
    }

    // Estruturas de controle de fluxo (condicionais)
    if (regex_search(temp, match, pitEntry)) {
        scopeStack.push_back(set<string>());
        string Ltrue = "label_" + to_string(labelCount++);
        string Lexit = "label_" + to_string(labelCount++);
        outFile << "if " << match[1].str() << " goto " << Ltrue << endl;
        outFile << "goto " << Lexit << endl;
        outFile << Ltrue << ":" << endl;
        outFile << "call write_string(\"Velocidade alta, reduza éã!\")" << endl;
        outFile << "goto label_" << labelCount << endl;
        outFile << Lexit << ":" << endl;
        outFile << "call write_string(\"Velocidade segura.\")" << endl;
        outFile << "label_" << labelCount++ << ":" << endl;
        scopeStack.pop_back();
    }
}

int main() {
    ifstream inFile("../lex/cod_examples/exemploSprint.senna");
    ofstream outFile("outputETAC.txt");
    if (!inFile) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    string line;
    while (getline(inFile, line)) {
        generateETAC(line, outFile);
    }

    inFile.close();
    outFile.close();
    cout << "Código ETAC gerado em 'outputETAC.txt'" << endl;
    return 0;
}