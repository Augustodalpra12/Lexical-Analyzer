#include "../lex/regex_definitions.h" // Arquivo de regex externo
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <regex>
#include <cctype>
#include <utility>

using namespace std;

int tempVarCount = 0; // Contador para variáveis temporárias (t1, t2, …)
int labelCount = 0;   // Contador de rótulos

// A pilha de escopo agora mapeia o nome original para um par: (nome temporário, tipo ETAC)
using ScopeMap = map<string, pair<string, string>>;

// Função auxiliar para remover espaços em branco do início e fim de uma string
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \n\r\t");
    if(start == string::npos) return "";
    size_t end = s.find_last_not_of(" \n\r\t");
    return s.substr(start, end - start + 1);
}

// Retorna o nome temporário associado a uma variável, se existir; caso contrário, retorna o token inalterado.
string getTempName(const string& token, const vector<ScopeMap>& scopeStack) {
    for(auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
        auto found = it->find(token);
        if(found != it->end()){
            return found->second.first;
        }
    }
    return token;
}

// Processa uma expressão substituindo cada token que corresponda a uma variável pelo seu nome temporário.
// Essa função assume que os tokens estão separados por espaços.
string processExpression(const string& expr, const vector<ScopeMap>& scopeStack) {
    istringstream iss(expr);
    string token;
    string result;
    while(iss >> token) {
        // Se for literal (começa com aspas), mantém inalterado
        if(token[0] == '"')
            result += token + " ";
        else
            result += getTempName(token, scopeStack) + " ";
    }
    if(!result.empty())
        result.pop_back(); // remove espaço final
    return result;
}

// Lida com expressões complexas (aritméticas/booleanas) e emite somente a atribuição final.
// Os tokens são substituídos pelo seu nome temporário.
void handleComplexExpression(const string& varTempName, const string& expression, const string& varType, 
                             ofstream& outFile, const vector<ScopeMap>& scopeStack) {
    istringstream iss(expression);
    string token;
    vector<string> operands;
    vector<string> operators;
    
    while (iss >> token) {
        if(token == "+" || token == "-" || token == "*" || token == "/" || 
           token == "&&" || token == "||" || token == "==" || token == "!=" || 
           token == "<" || token == ">" || token == "<=" || token == ">=") {
            operators.push_back(token);
        }
        else if(token == "!") {
            string operand;
            iss >> operand;
            string tempVar = "t" + to_string(tempVarCount++);
            operand = getTempName(operand, scopeStack);
            outFile << tempVar << ": " << varType << " = !" << operand << endl;
            operands.push_back(tempVar);
        } else {
            operands.push_back(getTempName(token, scopeStack));
        }
    }
    
    if (operands.size() > 2) {
        string tempVar = "t" + to_string(tempVarCount++);
        outFile << tempVar << ": " << varType << " = " 
                << operands[0] << " " << operators[0] << " " << operands[1] << endl;
        
        for (size_t i = 2; i < operands.size(); i++) {
            string newTempVar = "t" + to_string(tempVarCount++);
            outFile << newTempVar << ": " << varType << " = " 
                    << tempVar << " " << operators[i-1] << " " << operands[i] << endl;
            tempVar = newTempVar;
        }
        outFile << varTempName << ": " << varType << " = " << tempVar << endl;
    } else if (operands.size() == 2) {
        outFile << varTempName << ": " << varType << " = " 
                << operands[0] << " " << operators[0] << " " << operands[1] << endl;
    } else {
        outFile << varTempName << ": " << varType << " = " 
                << processExpression(expression, scopeStack) << endl;
    }
}

// Função para separar o código em blocos/instruções – inclui tratamento para laps, pitEntry e pitExit.
vector<string> parseBlocks(const string& code) {
    vector<string> blocks;
    int i = 0, n = code.size();
    while(i < n) {
        while(i < n && isspace(code[i])) i++;
        if(i >= n) break;
        int start = i;

        // Identifica blocos iniciados por palavras-chave específicas
        if(code.compare(i, 5, "laps(") == 0 || code.compare(i, 8, "pitEntry") == 0) {
            string keyword = (code.compare(i, 5, "laps(") == 0) ? "laps" : "pitEntry";
            while(i < n && code[i] != '{') i++;
            if(i < n && code[i] == '{') {
                int braceCount = 0;
                while(i < n) {
                    if(code[i] == '{') braceCount++;
                    if(code[i] == '}') braceCount--;
                    i++;
                    if(braceCount == 0) break;
                }
            }
            // Se for pitEntry, verifica se há pitExit em seguida e processa separadamente
            if(keyword == "pitEntry") {
                while(i < n && isspace(code[i])) i++;
                if(i < n && code.compare(i, 7, "pitExit") == 0) {
                    blocks.push_back(trim(code.substr(start, i - start))); // Adiciona pitEntry
                    // Agora processa pitExit separadamente
                    start = i;
                    while(i < n && code[i] != '{') i++;
                    if(i < n && code[i] == '{') {
                        int braceCount = 0;
                        while(i < n) {
                            if(code[i] == '{') braceCount++;
                            if(code[i] == '}') braceCount--;
                            i++;
                            if(braceCount == 0) break;
                        }
                    }
                    while(i < n && isspace(code[i])) i++;
                    if(i < n && code[i] == '.') { i++; }
                    blocks.push_back(trim(code.substr(start, i - start)));
                    continue;
                }
            }
            while(i < n && isspace(code[i])) i++;
            if(i < n && code[i] == '.') { i++; }
            blocks.push_back(trim(code.substr(start, i - start)));
        }
        // Caso geral: captura até encontrar um ponto final fora de blocos
        else {
            int braceCount = 0;
            while(i < n) {
                if(code[i] == '{') braceCount++;
                if(code[i] == '}') braceCount--;
                if(braceCount == 0 && code[i] == '.') { i++; break; }
                i++;
            }
            blocks.push_back(trim(code.substr(start, i - start)));
        }
    }
    return blocks;
}

// Função principal para gerar o código ETAC a partir de uma instrução/bloco
void generateETAC(const string& sourceCode, ofstream& outFile, vector<ScopeMap>& scopeStack) {
    smatch match;
    string temp = trim(sourceCode);
    temp = regex_replace(temp, regex("\\s+"), " ");

    // Ignora linhas irrelevantes
    if (temp.empty() || temp.find('@') != string::npos || temp == "int race() {" || temp == "}") return;

    // Trata o loop "laps"
    if(temp.substr(0, 5) == "laps(") {
        cout << "Processando laps: " << temp << endl;
        regex lapsRegex(R"(laps\(\s*([^;]+);([^;]+);([^)]+)\)\s*\{([^}]+)\}\s*[.;]?)");
        if(regex_match(temp, match, lapsRegex)) {
            string initPart = match[1].str();      // Ex: "int i = 0"
            string condPart = match[2].str();        // Ex: "i<50"
            string incrementPart = match[3].str();   // Ex: "i = overtake" (incremento unitário)
            string body = match[4].str();            // Corpo do laço

            regex initRegex(R"(int\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([0-9]+))");
            smatch initMatch;
            string origVar, initValue;
            if(regex_search(initPart, initMatch, initRegex)) {
                origVar = initMatch[1].str();
                initValue = initMatch[2].str();
            } else {
                origVar = "i";
                initValue = "0";
            }
            string loopTemp = "t" + to_string(tempVarCount++);
            outFile << loopTemp << ": u8 = " << initValue << "u8" << endl;
            scopeStack.back()[origVar] = make_pair(loopTemp, "u8");

            regex condRegex(R"(([a-zA-Z_][a-zA-Z0-9_]*)\s*<\s*([0-9]+))");
            smatch condMatch;
            string limitValue = "0";
            if(regex_search(condPart, condMatch, condRegex)) {
                limitValue = condMatch[2].str();
            }
            string loopLabel = "loop_" + to_string(labelCount++);
            string doneLabel = "done_" + to_string(labelCount++);
            outFile << loopLabel << ":" << endl;
            outFile << "  if " << loopTemp << " >= " << limitValue << "u8 goto " << doneLabel << endl;
            
            istringstream bodyStream(body);
            string line;
            while(getline(bodyStream, line, '.')) {
                line = trim(line);
                if(!line.empty()){
                    outFile << "  ";
                    generateETAC(line + ".", outFile, scopeStack);
                }
            }
            outFile << "  " << loopTemp << ": u8 = " << loopTemp << " + 1u8" << endl;
            outFile << "  goto " << loopLabel << endl;
            outFile << doneLabel << ":" << endl;
        }
        return;
    }

    // Trata declaração de variáveis
    regex declarationRegex(R"((int|double|str|bool)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*(=\s*([^.;]+))?\s*[.;])");
    if(regex_match(temp, match, declarationRegex)) {
        string varType = match[1].str();
        string origVar = match[2].str();
        string value = match[4].str();
        
        string etacType = (varType == "int") ? "i32" : 
                          (varType == "double") ? "f64" : 
                          (varType == "str") ? "str" : "bool";
        string defaultVal = (varType == "int") ? "0" : 
                           (varType == "double") ? "0.0" : 
                           (varType == "str") ? "\"\"" : "false";
        string tempName = "t" + to_string(tempVarCount++);
        scopeStack.back()[origVar] = make_pair(tempName, etacType);

        if(!value.empty()){
            if(value.find_first_of("+-*/&&||==!=<>") != string::npos || value.find("!") != string::npos) {
                handleComplexExpression(tempName, value, etacType, outFile, scopeStack);
            } else {
                outFile << tempName << ": " << etacType << " = " 
                        << processExpression(value, scopeStack) << endl;
            }
        } else {
            outFile << tempName << ": " << etacType << " = " << defaultVal << endl;
        }
        return;
    }

    // Trata atribuição
    regex assignmentRegex(R"(([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([^.;]+)\s*[.;])");
    if(regex_match(temp, match, assignmentRegex)) {
        string origVar = match[1].str();
        string expression = match[2].str();
        
        string varTempName = getTempName(origVar, scopeStack);
        string varType = "i32"; 
        for(auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
            if(it->find(origVar) != it->end()){
                varType = it->at(origVar).second;
                break;
            }
        }
        if(expression.find_first_of("+-*/&&||==!=<>") != string::npos || expression.find("!") != string::npos) {
            handleComplexExpression(varTempName, expression, varType, outFile, scopeStack);
        } else {
            outFile << varTempName << " = " << processExpression(expression, scopeStack) << endl;
        }
        return;
    }

    // Trata impressão (prt)
    regex printRegex(R"(prt\s*\(\s*(.+)\s*\)[.;]?)");
    if(regex_match(temp, match, printRegex)) {
        string expression = match[1].str();
        string processedExpr = processExpression(expression, scopeStack);
        outFile << "call write_string(" << processedExpr << ")" << endl;
        return;
    }

// Trata condicionais: pitEntry e pitExit
// Usamos quantificadores não gulosos para capturar corretamente os conteúdos, inclusive com quebras de linha
regex pitEntryExitRegex(R"(pitEntry\s*\(([^)]+)\)\s*\{((?:.|\n)+?)\}\s*pitExit\s*\{((?:.|\n)+?)\}\s*[.;]?)");
regex pitEntryOnlyRegex(R"(pitEntry\s*\(([^)]+)\)\s*\{([^}]+)\}\s*[.;]?)");
if(regex_match(temp, match, pitEntryExitRegex)) {
    cout << "Processando pitEntry/pitExit: " << temp << endl;
    scopeStack.push_back(ScopeMap());
    string condition = match[1].str();
    string trueBody = match[2].str();   // Bloco pitEntry (if)
    string falseBody = match[3].str();  // Bloco pitExit (else)

    // Usamos três rótulos para definir a estrutura condicional
    string Lif = "label_" + to_string(labelCount++);
    string Lelse = "label_" + to_string(labelCount++);
    string Lend = "label_" + to_string(labelCount++);

    string tempCondVar = "t" + to_string(tempVarCount++);
    outFile << tempCondVar << ": bool = " << processExpression(condition, scopeStack) << endl;
    outFile << "if " << tempCondVar << " goto " << Lif << endl;
    outFile << "goto " << Lelse << endl;
    
    outFile << Lif << ":" << endl;
    {
        istringstream trueStream(trueBody);
        string trueLine;
        while(getline(trueStream, trueLine, '.')) {
            trueLine = trim(trueLine);
            if(!trueLine.empty()){
                generateETAC(trueLine + ".", outFile, scopeStack);
            }
        }
    }
    outFile << "goto " << Lend << endl;
    
    outFile << Lelse << ":" << endl;
    {
        istringstream falseStream(falseBody);
        string falseLine;
        while(getline(falseStream, falseLine, '.')) {
            falseLine = trim(falseLine);
            if(!falseLine.empty()){
                generateETAC(falseLine + ".", outFile, scopeStack);
            }
        }
    }
    outFile << Lend << ":" << endl;
    scopeStack.pop_back();
    return;
} else if(regex_match(temp, match, pitEntryOnlyRegex)){
    cout << "Processando pitEntry (somente): " << temp << endl;
    scopeStack.push_back(ScopeMap());
    string condition = match[1].str();
    string trueBody = match[2].str();

    string Ltrue = "label_" + to_string(labelCount++);
    string Lexit = "label_" + to_string(labelCount++);

    string tempCondVar = "t" + to_string(tempVarCount++);
    outFile << tempCondVar << ": bool = " << processExpression(condition, scopeStack) << endl;
    outFile << "if " << tempCondVar << " goto " << Ltrue << endl;
    outFile << "goto " << Lexit << endl;
    outFile << Ltrue << ":" << endl;
    
    {
        istringstream trueStream(trueBody);
        string trueLine;
        while(getline(trueStream, trueLine, '.')) {
            trueLine = trim(trueLine);
            if(!trueLine.empty()){
                generateETAC(trueLine + ".", outFile, scopeStack);
            }
        }
    }
    outFile << Lexit << ":" << endl;
    scopeStack.pop_back();
    return;
}

}

// Função main – utiliza parseBlocks para separar corretamente os blocos/instruções
int main() {
    ifstream inFile("../lex/cod_examples/exemploSprint.senna");
    ofstream outFile("outputETAC.txt");
    if(!inFile){
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }
    
    stringstream buffer;
    buffer << inFile.rdbuf();
    string sourceCode = buffer.str();

    // Pré-processamento: remove o cabeçalho "int race() {" e o fechamento "}" final
    regex headerRegex("^\\s*int\\s+race\\s*\\(\\)\\s*\\{");
    sourceCode = regex_replace(sourceCode, headerRegex, "");
    regex footerRegex("\\}\\s*$");
    sourceCode = regex_replace(sourceCode, footerRegex, "");

    vector<ScopeMap> scopeStack;
    scopeStack.push_back(ScopeMap());

    // Usa parseBlocks para separar os blocos corretamente
    vector<string> blocks = parseBlocks(sourceCode);
    for(const auto& block : blocks) {
        if(!block.empty()){
            cout << "Processando bloco: " << block << endl;
            generateETAC(block, outFile, scopeStack);
        }
    }

    inFile.close();
    outFile.close();
    cout << "Código ETAC gerado em 'outputETAC.txt'" << endl;
    return 0;
}
