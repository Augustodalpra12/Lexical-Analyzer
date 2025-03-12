#include "../lex/regex_definitions.h" // Arquivo de regex externo
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <regex>

using namespace std;

int tempVarCount = 0; // Contador de variáveis temporárias
int labelCount = 0;   // Contador de rótulos

// Função para lidar com expressões complexas (aritméticas ou booleanas)
void handleComplexExpression(const string& varName, const string& expression, const string& varType, ofstream& outFile) {
    istringstream iss(expression);
    string token;
    vector<string> operands;
    vector<string> operators;
    
    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/" || 
            token == "&&" || token == "||" || token == "==" || token == "!=" || 
            token == "<" || token == ">" || token == "<=" || token == ">=") {
            operators.push_back(token);
        } else if (token == "!") {
            // Trata negação unária
            string operand;
            iss >> operand;
            string tempVar = "t" + to_string(tempVarCount++);
            outFile << tempVar << ": " << varType << " = !" << operand << endl;
            operands.push_back(tempVar);
        } else {
            operands.push_back(token);
        }
    }
    
    if (operands.size() > 2) {
        string tempVar = "t" + to_string(tempVarCount++);
        outFile << tempVar << ": " << varType << " = " << operands[0] << " " << operators[0] << " " << operands[1] << endl;
        
        for (size_t i = 2; i < operands.size(); i++) {
            string newTempVar = "t" + to_string(tempVarCount++);
            outFile << newTempVar << ": " << varType << " = " << tempVar << " " << operators[i-1] << " " << operands[i] << endl;
            tempVar = newTempVar;
        }
        outFile << varName << " = " << tempVar << endl;
    } else if (operands.size() == 2) {
        outFile << varName << ": " << varType << " = " << operands[0] << " " << operators[0] << " " << operands[1] << endl;
    } else {
        outFile << varName << ": " << varType << " = " << expression << endl;
    }
}

void generateETAC(const string& sourceCode, ofstream& outFile, vector<map<string, string>>& scopeStack) {
    smatch match;
    string temp = sourceCode;
    
    temp = regex_replace(temp, regex("\\s+"), " ");

    // Ignora comentários e linhas de função
    if (temp.empty() || temp.find('@') != string::npos || temp == "int race() {" || temp == "}") return;

    // Declaração de variáveis
    regex declarationRegex(R"(\s*(int|double|str|bool)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*(=\s*([^.;]+))?\s*[.;])");
    if (regex_match(temp, match, declarationRegex)) {
        string varType = match[1].str();
        string varName = match[2].str();
        string value = match[4].str();
        
        string etacType = (varType == "int") ? "i32" : 
                         (varType == "double") ? "f64" : 
                         (varType == "str") ? "str" : "bool";
        string defaultVal = (varType == "int") ? "0" : 
                           (varType == "double") ? "0.0" : 
                           (varType == "str") ? "\"\"" : "false";

        if (!value.empty()) {
            if (value.find_first_of("+-*/&&||==!=<>") != string::npos || value.find("!") != string::npos) {
                if (etacType != "bool" || value.find_first_of("+-*/") != string::npos) {
                    outFile << varName << ": " << etacType << endl;
                }
                handleComplexExpression(varName, value, etacType, outFile);
            } else {
                outFile << varName << ": " << etacType << " = " << value << endl;
            }
        } else {
            outFile << varName << ": " << etacType << " = " << defaultVal << endl;
        }
        scopeStack.back()[varName] = etacType;
        return;
    }

    // Atribuição
    regex assignmentRegex(R"(\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([^.;]+)\s*[.;])");
    if (regex_match(temp, match, assignmentRegex)) {
        string varName = match[1].str();
        string expression = match[2].str();
        
        string varType = "i32"; // Tipo padrão
        for (auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
            if (it->find(varName) != it->end()) {
                varType = it->at(varName);
                break;
            }
        }
        
        if (expression.find_first_of("+-*/&&||==!=<>") != string::npos || expression.find("!") != string::npos) {
            handleComplexExpression(varName, expression, varType, outFile);
        } else {
            outFile << varName << " = " << expression << endl;
        }
        return;
    }

    // Impressão
    regex printRegex(R"(\s*prt\(([^)]+)\)\s*[.;])");
    if (regex_match(temp, match, printRegex)) {
        string content = match[1].str();
        if (content[0] == '"') {
            string value = content.substr(1, content.length() - 2);
            outFile << "call write_string(\"" << value << "\")" << endl;
        } else {
            outFile << "call write_int(" << content << ")" << endl;
        }
        return;
    }

    // Loop (laps)
    regex lapsRegex(R"(\s*laps\s*\(([^;]+);([^;]+);([^)]+)\)\s*\{([^}]+)\}\s*[.;]?)");
    if (regex_match(temp, match, lapsRegex)) {
        cout << "Entrou no laps: " << temp << endl;
        scopeStack.push_back(map<string, string>());
        string init = match[1].str();
        string condition = match[2].str();
        string increment = match[3].str();
        string body = match[4].str();

        string Lstart = "loop_" + to_string(labelCount++);
        string Lexit = "done_" + to_string(labelCount++);

        generateETAC(init + ".", outFile, scopeStack);
        outFile << Lstart << ":" << endl;
        string tempCondVar = "t" + to_string(tempVarCount++);
        outFile << "  " << tempCondVar << ": bool = " << condition << endl;
        outFile << "  if not " << tempCondVar << " goto " << Lexit << endl;
        
        istringstream bodyStream(body);
        string line;
        while (getline(bodyStream, line, '.')) {
            if (!line.empty()) {
                outFile << "  ";
                generateETAC(line + ".", outFile, scopeStack);
            }
        }
        
        outFile << "  ";
        generateETAC(increment + ".", outFile, scopeStack);
        outFile << "  goto " << Lstart << endl;
        outFile << Lexit << ":" << endl;
        
        scopeStack.pop_back();
        return;
    }

    // Condicional (pitEntry com ou sem pitExit)
    regex pitEntryOnlyRegex(R"(\s*pitEntry\s*\(([^)]+)\)\s*\{([^}]+)\}\s*[.;]?)");
    regex pitEntryExitRegex(R"(\s*pitEntry\s*\(([^)]+)\)\s*\{([^}]+)\}\s*pitExit\s*\{([^}]+)\}\s*[.;]?)");
    
    if (regex_match(temp, match, pitEntryExitRegex)) {
        cout << "Entrou no pitEntryExit: " << temp << endl;
        scopeStack.push_back(map<string, string>());
        string condition = match[1].str();
        string trueBody = match[2].str();
        string falseBody = match[3].str();

        string Ltrue = "label_" + to_string(labelCount++);
        string Lexit = "label_" + to_string(labelCount++);

        string tempCondVar = "t" + to_string(tempVarCount++);
        outFile << tempCondVar << ": bool = " << condition << endl;
        outFile << "if " << tempCondVar << " goto " << Ltrue << endl;
        
        istringstream falseStream(falseBody);
        string falseLine;
        while (getline(falseStream, falseLine, '.')) {
            if (!falseLine.empty()) {
                generateETAC(falseLine + ".", outFile, scopeStack);
            }
        }
        
        outFile << "goto " << Lexit << endl;
        outFile << Ltrue << ":" << endl;
        
        istringstream trueStream(trueBody);
        string trueLine;
        while (getline(trueStream, trueLine, '.')) {
            if (!trueLine.empty()) {
                generateETAC(trueLine + ".", outFile, scopeStack);
            }
        }
        
        outFile << Lexit << ":" << endl;
        scopeStack.pop_back();
        return;
    } else if (regex_match(temp, match, pitEntryOnlyRegex)) {
        cout << "Entrou no pitEntryOnly: " << temp << endl;
        scopeStack.push_back(map<string, string>());
        string condition = match[1].str();
        string trueBody = match[2].str();

        string Ltrue = "label_" + to_string(labelCount++);
        string Lexit = "label_" + to_string(labelCount++);

        string tempCondVar = "t" + to_string(tempVarCount++);
        outFile << tempCondVar << ": bool = " << condition << endl;
        outFile << "if " << tempCondVar << " goto " << Ltrue << endl;
        outFile << "goto " << Lexit << endl;
        outFile << Ltrue << ":" << endl;
        
        istringstream trueStream(trueBody);
        string trueLine;
        while (getline(trueStream, trueLine, '.')) {
            if (!trueLine.empty()) {
                generateETAC(trueLine + ".", outFile, scopeStack);
            }
        }
        
        outFile << Lexit << ":" << endl;
        scopeStack.pop_back();
        return;
    }
}

int main() {
    ifstream inFile("../lex/cod_examples/exemploSprint.senna");
    ofstream outFile("outputETAC.txt");
    if (!inFile) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << inFile.rdbuf();
    string sourceCode = buffer.str();

    vector<map<string, string>> scopeStack;
    scopeStack.push_back(map<string, string>());

    // Regex para capturar blocos completos
    regex blockRegex(R"((laps\s*\([^)]+\)\s*\{[^}]+\}\s*[.;]?)|(pitEntry\s*\([^)]+\)\s*\{[^}]+\}\s*pitExit\s*\{[^}]+\}\s*[.;]?)|(pitEntry\s*\([^)]+\)\s*\{[^}]+\}\s*[.;]?)|([^.]+?\.))");
    sregex_iterator it(sourceCode.begin(), sourceCode.end(), blockRegex);
    sregex_iterator end;

    for (; it != end; ++it) {
        string block = it->str();
        if (!block.empty()) {
            cout << "Processando bloco: " << block << endl;
            generateETAC(block, outFile, scopeStack);
        }
    }

    inFile.close();
    outFile.close();
    cout << "Código ETAC gerado em 'outputETAC.txt'" << endl;
    return 0;
}