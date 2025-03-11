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

    // Removendo espaços extras das linhas
    temp = regex_replace(temp, spaces, " ");

    // Declarações de variáveis
    if (regex_search(temp, match, typeInt) || regex_search(temp, match, typeDouble) ||
    regex_search(temp, match, typeStr) || regex_search(temp, match, typeBoolean)) {
    string varType = match.str();
    temp = match.suffix().str();
    if (regex_search(temp, match, id)) {
        string varName = match.str();
        scopeStack.back().insert(varName);
        string defaultVal;
        // Verifica cada tipo e trata a atribuição literal, se houver:
        if (varType == "int") {
            varType = "i32";
            defaultVal = "0";
            if (regex_search(temp, match, op_rel_equal)) {
                temp = match.suffix().str();
                if (regex_search(temp, match, integer)) {
                    string value = match.str();
                    outFile << "t" << tempVarCount++ << ": " << varType << " = " << value << endl;
                    return; // Processa somente essa linha
                }
            }
        } else if (varType == "double") {
            varType = "f64";
            defaultVal = "0";
            if (regex_search(temp, match, op_rel_equal)) {
                temp = match.suffix().str();
                if (regex_search(temp, match, double_regex)) {
                    string value = match.str();
                    outFile << "t" << tempVarCount++ << ": " << varType << " = " << value << endl;
                    return;
                }
            }
        } else if (varType == "str") {
            varType = "str";
            defaultVal = "\"\"";
            if (regex_search(temp, match, op_rel_equal)) {
                temp = match.suffix().str();
                if (regex_search(temp, match, quotes_regex)) {
                    string value = match.str();  // valor já com aspas
                    outFile << "t" << tempVarCount++ << ": " << varType << " = " << value << endl;
                    return;
                }
            }
        } else if (varType == "bool") {
            // Para bool, o padrão é 'false'
            defaultVal = "false";
            if (regex_search(temp, match, op_rel_equal)) {
                temp = match.suffix().str();
                // Supondo que exista um regex para literais booleanos (ex.: true ou false)
                if (regex_search(temp, match, bool_false) || regex_search(temp, match, bool_true)) {
                    string value = match.str();
                    outFile << "t" << tempVarCount++ << ": " << varType << " = " << value << endl;
                    return;
                }
            }
        }
        // Caso não haja atribuição literal, declara com o valor padrão
        outFile << "t" << tempVarCount++ << ": " << varType << " = " << defaultVal << endl;
    }
    }
    
    // Atribuições
    if (regex_search(temp, match, id) && regex_search(temp, match, op_rel_equal)) {
        string varName = match.str();
        temp = match.suffix().str();
        
        // Verifique o valor da variável 'temp' e se ela contém algo válido
        if (regex_search(temp, match, integer)) {
            string value = match.str();
            outFile << varName << " = " << value << endl; // Linha corrigida para tipo i32
        } else if (regex_search(temp, match, double_regex)) {
            string value = match.str();
            outFile << varName << " = " << value << endl; // Linha corrigida para tipo f64
        } else if (regex_search(temp, match, quotes_regex)) {
            string value = match.str();
            // Remover as aspas da string
            value = value.substr(1, value.length() - 2); // Removendo as aspas
            outFile << varName << " = " << "\"" << value << "\"" << endl; // Para strings, preserva as aspas
        } else if (regex_search(temp, match, id)) {
            string rhsVar = match.str();
            outFile << varName << " = " << rhsVar << endl;
        } else if (regex_search(temp, match, op_arit_sum) || regex_search(temp, match, op_arit_sub) ||
                regex_search(temp, match, op_arit_mult) || regex_search(temp, match, op_arit_div) ||
                regex_search(temp, match, op_arit_pow)) {
            string op = match.str();
            temp = match.suffix().str();
            regex_search(temp, match, id);
            string rhsVar = match.str();
            string tempVar = "t" + to_string(tempVarCount++);
            outFile << tempVar << " = " << varName << " " << op << " " << rhsVar << endl; // Atribuição de operação
            outFile << varName << " = " << tempVar << endl;
        } else {
            // Verifique se o valor que está sendo atribuído não é inválido ou vazio
            cerr << "Erro: expressão inválida na atribuição de " << varName << endl;
        }
    }
    
    // Comando de impressão
    if (regex_search(temp, match, reserved_prt)) {
        if (regex_search(temp, match, id)) {
            string varName = match.str();
            outFile << "call write_int(" << varName << ")" << endl; // Agora a variável é passada corretamente
        } else if (regex_search(temp, match, quotes_regex)) {
            string value = match.str();
            value = value.substr(1, value.length() - 2); // Remover as aspas
            outFile << "call write_string(" << "\"" << value << "\"" << ")" << endl; // Agora a string é passada corretamente
        }
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
        outFile << "if true goto " << Ltrue << endl;
        outFile << "goto " << Lexit << endl;
        outFile << Ltrue << ":" << endl;
        outFile << "// PIT ENTRY BLOCK" << endl;
        outFile << Lexit << ":" << endl;
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