#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>
using namespace std;

//-----------------------------------------------------------------
// Funções auxiliares para identificar operadores
//-----------------------------------------------------------------
bool isOperator(const string &tokenType) {
    return tokenType == "op_arit_sum" || tokenType == "op_arit_sub" ||
           tokenType == "op_arit_mult" || tokenType == "op_arit_div" ||
           tokenType == "op_arit_pow"  || tokenType == "op_log_e"    ||
           tokenType == "op_log_or";
}

bool isRelationalOperator(const string &tokenType) {
    return tokenType == "op_rel_minor"     || tokenType == "op_rel_bigger" ||
           tokenType == "op_rel_double_equal"|| tokenType == "op_rel_minor_equal" ||
           tokenType == "op_rel_bigger_equal"|| tokenType == "op_rel_not_equal";
}

//-----------------------------------------------------------------
// Gerenciamento de escopo
//-----------------------------------------------------------------
class ScopeManager {
public:
    vector<unordered_map<string, string>> scopes;
    ScopeManager() {
        scopes.push_back(unordered_map<string, string>()); // escopo global
    }
    string lookupVariable(const string &varName) {
        for (auto it = scopes.rbegin(); it != scopes.rend(); ++it)
            if (it->find(varName) != it->end())
                return it->at(varName);
        return "";
    }
    bool variableExists(const string &varName) {
        return !lookupVariable(varName).empty();
    }
    bool addVariable(const string &varName, const string &type) {
        if (variableExists(varName))
            return false;
        scopes.back()[varName] = type;
        return true;
    }
    void pushScope() {
        scopes.push_back(unordered_map<string, string>());
    }
    void popScope() {
        if (scopes.size() > 1)
            scopes.pop_back();
    }
};

//-----------------------------------------------------------------
// Função auxiliar: avalia uma expressão até encontrar um token de fronteira.
// Parâmetros:
//   - declaredType e assignment: para atribuições (não há conversão implícita).
//   - isCondition: se true, e não houver operador relacional, o resultado deve ser bool.
//   - isPrint: relaxa a verificação de tipos (para concatenação, por exemplo).
// (Esta função permanece inalterada.)
string evaluateExpression(queue<vector<string>> &tokens, const string &boundary, 
    const string &declaredType, bool assignment, 
    ScopeManager &scopeManager, bool &errorFlag, 
    bool isCondition = false, bool isPrint = false) {
string exprType = "";
bool encounteredRelational = false;
while (!tokens.empty() && tokens.front()[0] != boundary) {
vector<string> token = tokens.front();

// Se o token for o operador de atribuição, ignora-o.
if (token[0] == "op_rel_equal") {
tokens.pop();
continue;
}

if(token[0] == "op_rel_not") {
tokens.pop();
if(!tokens.empty() && tokens.front()[0] != boundary) {
vector<string> nextToken = tokens.front();
tokens.pop();
string nextType = "";
if(nextToken[0] == "bool_true" || nextToken[0] == "bool_false")
nextType = "bool";
else if(nextToken[0] == "id") {
nextType = scopeManager.lookupVariable(nextToken[1]);
if(nextType == "") {
cerr << "Erro na linha " << nextToken[2] << ": Variavel '" << nextToken[1] 
     << "' nao declarada." << endl;
errorFlag = true;
}
}
if(nextType != "bool") {
cerr << "Erro na linha " << nextToken[2] << ": Operador '!' espera bool, mas obteve '" 
 << nextType << "'." << endl;
errorFlag = true;
}
if(exprType.empty())
exprType = "bool";
else if(exprType != "bool" && !isPrint) {
cerr << "Erro na linha " << nextToken[2] << ": Inconsistencia de tipos com operador '!'." << endl;
errorFlag = true;
}
continue;
}
}
if (isRelationalOperator(token[0])) {
encounteredRelational = true;
tokens.pop(); // remove o operador relacional
break;
}
tokens.pop();
if (isOperator(token[0]))
continue;
string currentType = "";
if (token[0] == "integer")
currentType = "int";
else if (token[0] == "double")
currentType = "double";
else if (token[0] == "text_between_quotes")
currentType = "str";
else if (token[0] == "bool_true" || token[0] == "bool_false")
currentType = "bool";
// Tratar os operadores reservados para incremento/decremento como int.
else if (token[0] == "overtake" || token[0] == "brake")
currentType = "int";
else if (token[0] == "id") {
currentType = scopeManager.lookupVariable(token[1]);
if (currentType == "") {
cerr << "Erro na linha " << token[2] << ": Variavel '" 
<< token[1] << "' nao declarada." << endl;
errorFlag = true;
continue;
}
}
if (exprType.empty())
exprType = currentType;
else if (!isPrint && exprType != currentType) {
cerr << "Erro na linha " << token[2] 
<< ": Inconsistencia de tipos na expressao. Operando anterior era '" 
<< exprType << "' e o atual eh '" << currentType << "'." << endl;
errorFlag = true;
}
if (assignment && !declaredType.empty() && currentType != declaredType) {
cerr << "Erro na linha " << token[2] << ": Atribuicao invalida. Tipo '" 
<< currentType << "' nao pode ser atribuido a uma variavel do tipo '" 
<< declaredType << "'." << endl;
errorFlag = true;
}
}
if (!encounteredRelational) {
if (isCondition && exprType != "bool") {
cerr << "Erro: Expressao condicional invalida. Esperado bool, mas obteve '" 
<< exprType << "'." << endl;
errorFlag = true;
}
return exprType;
}
string rightType = "";
while (!tokens.empty() && tokens.front()[0] != boundary) {
vector<string> token = tokens.front();
tokens.pop();
if (token[0] == "op_rel_equal") {
continue; // ignora operador de atribuição
}
if (isOperator(token[0]))
continue;
string currentType = "";
if (token[0] == "integer")
currentType = "int";
else if (token[0] == "double")
currentType = "double";
else if (token[0] == "text_between_quotes")
currentType = "str";
else if (token[0] == "bool_true" || token[0] == "bool_false")
currentType = "bool";
else if (token[0] == "overtake" || token[0] == "brake")
currentType = "int";
else if (token[0] == "id") {
currentType = scopeManager.lookupVariable(token[1]);
if (currentType == "") {
cerr << "Erro na linha " << token[2] << ": Variavel '" 
<< token[1] << "' nao declarada." << endl;
errorFlag = true;
continue;
}
}
if (rightType.empty())
rightType = currentType;
else if (!isPrint && rightType != currentType) {
cerr << "Erro na linha " << token[2] 
<< ": Inconsistencia de tipos na expressao condicional. Operando anterior era '" 
<< rightType << "' e o atual eh '" << currentType << "'." << endl;
errorFlag = true;
}
}
if (!isPrint && !rightType.empty() && exprType != rightType) {
cerr << "Erro: Inconsistencia de tipos na expressao condicional. "
<< "Operando esquerdo possui tipo '" << exprType << "' e o direito '" 
<< rightType << "'." << endl;
errorFlag = true;
}
return "bool";
}

//-----------------------------------------------------------------
// Função para processar o cabeçalho do laço 'laps' (for loop)
// Divide o header em três partes: inicializacao, condicao e iteracao.
// Pressupondo que as partes são separadas pelo token "symbol_op_mid" e que o header é
// delimitado por '(' e ')'.
// (Ajuste os tokens separadores conforme sua saída léxica.)
void processLapsHeader(queue<vector<string>> &tokens, ScopeManager &scopeManager, bool &errorFlag) {
    // Remove o token de abertura "(".
    if (!tokens.empty() && tokens.front()[0] == "symbol_parameter_init")
        tokens.pop();
    else {
        cerr << "Erro: '(' esperado apos 'laps'." << endl;
        errorFlag = true;
        return;
    }

    // ---- Parte de inicializacao ----
    queue<vector<string>> initTokens;
    while (!tokens.empty() && tokens.front()[0] != "symbol_op_mid") {
        initTokens.push(tokens.front());
        tokens.pop();
    }
    if (!tokens.empty() && tokens.front()[0] == "symbol_op_mid")
        tokens.pop(); // remove o ";"
    else {
        cerr << "Erro: ';' esperado apos a inicializacao no laps." << endl;
        errorFlag = true;
        return;
    }
    // Processa a inicializacao (ex.: "typeInt", "id", "op_rel_equal", "integer")
    if (!initTokens.empty()) {
        vector<string> firstToken = initTokens.front();
        if (firstToken[0] == "typeInt" || firstToken[0] == "typeDouble") {
            string declaredType;
            if (firstToken[0] == "typeInt") declaredType = "int";
            else if (firstToken[0] == "typeDouble") declaredType = "double";
            initTokens.pop(); // remove o token de tipo
            if (initTokens.empty()) {
                cerr << "Erro: Identificador esperado na inicializacao do laps." << endl;
                errorFlag = true;
            }
            vector<string> idToken = initTokens.front();
            initTokens.pop();
            if (idToken[0] != "id") {
                cerr << "Erro: Identificador esperado na inicializacao do laps, encontrado '" 
                     << idToken[1] << "'." << endl;
                errorFlag = true;
            }
            string varName = idToken[1];
            if (!scopeManager.addVariable(varName, declaredType)) {
                cerr << "Erro: Variavel '" << varName << "' ja declarada na inicializacao do laps." << endl;
                errorFlag = true;
            }
            // Se houver atribuição na inicializacao:
            if (!initTokens.empty() && initTokens.front()[0] == "op_rel_equal") {
                initTokens.pop(); // remove "="
                bool dummyError = false;
                string exprType = evaluateExpression(initTokens, "end_line", declaredType, true, scopeManager, dummyError);
                if (dummyError)
                    errorFlag = true;
            }
        } else {
            // Se não é uma declaração, pode ser uma atribuição simples.
            bool dummyError = false;
            string exprType = evaluateExpression(initTokens, "end_line", "", false, scopeManager, dummyError);
            if (dummyError)
                errorFlag = true;
        }
    }
    // ---- Parte de condicao ----
    queue<vector<string>> condTokens;
    while (!tokens.empty() && tokens.front()[0] != "symbol_op_mid") {
        condTokens.push(tokens.front());
        tokens.pop();
    }
    if (!tokens.empty() && tokens.front()[0] == "symbol_op_mid")
        tokens.pop(); // remove o ";"
    else {
        cerr << "Erro: ';' esperado apos a condicao do laps." << endl;
        errorFlag = true;
        return;
    }
    bool condError = false;
    string condType = evaluateExpression(condTokens, "end_line", "", false, scopeManager, condError, true, false);
    if (condError)
        errorFlag = true;
    if (condType != "bool") {
        cerr << "Erro: Condicao do laps deve resultar em bool, mas obteve '" << condType << "'." << endl;
        errorFlag = true;
    }
    // ---- Parte de iteracao ----
    queue<vector<string>> iterTokens;
    while (!tokens.empty() && tokens.front()[0] != "symbol_parameter_end") {
        iterTokens.push(tokens.front());
        tokens.pop();
    }
    if (!tokens.empty() && tokens.front()[0] == "symbol_parameter_end")
        tokens.pop(); // remove o ")"
    else {
        cerr << "Erro: ')' esperado no header do laps." << endl;
        errorFlag = true;
        return;
    }
    // A iteração pode ser uma atribuição ou o uso dos operadores reservados "overtake" ou "brake".
    bool iterError = false;
    string iterType = evaluateExpression(iterTokens, "end_line", "", false, scopeManager, iterError, false, false);
    if (iterError)
        errorFlag = true;
    // Se houver um token "end_line" final, remova-o.
    if (!tokens.empty() && tokens.front()[0] == "end_line")
        tokens.pop();
}

//-----------------------------------------------------------------
// Função principal de análise semântica
//-----------------------------------------------------------------
void semanticAnalysis(queue<vector<string>> tokens) {
    ScopeManager scopeManager;
    bool errorFound = false;

    while (!tokens.empty()) {
        vector<string> token = tokens.front();
        tokens.pop();
        string tokenType = token[0];
        string lexeme = token[1];
        string line = token[2];

        // Gerenciamento de escopo: abrindo e fechando blocos.
        if (tokenType == "pitEntry" || tokenType == "pitExit" ||
            tokenType == "circuit") {
            scopeManager.pushScope();
            // Para pitEntry e circuit, assumimos que há condição entre parênteses.
            if (tokenType == "pitEntry" || tokenType == "circuit") {
                if (!tokens.empty() && tokens.front()[0] == "symbol_parameter_init")
                    tokens.pop(); // remove "("
                bool exprError = false;
                string condType = evaluateExpression(tokens, "symbol_parameter_end", "", false, scopeManager, exprError, true, false);
                if (exprError)
                    errorFound = true;
                if (!tokens.empty() && tokens.front()[0] == "symbol_parameter_end")
                    tokens.pop(); // remove ")"
                if (!tokens.empty() && tokens.front()[0] == "symbol_op_init")
                    tokens.pop(); // remove "{"
                if (condType != "bool") {
                    cerr << "Erro na linha " << line << ": Expressao condicional deve resultar em bool, mas obteve '" 
                         << condType << "'." << endl;
                    errorFound = true;
                }
            }
            continue;
        }
        if (tokenType == "pitExit") {
            // pitExit é um else sem parâmetros; se houver abertura de bloco, remova-a.
            if (!tokens.empty() && tokens.front()[0] == "symbol_op_init")
                tokens.pop();
            continue;
        }
        if (tokenType == "laps") {
            // Trata o cabeçalho do for de forma específica.
            processLapsHeader(tokens, scopeManager, errorFound);
            continue;
        }
        // Tratamento para o print.
        if (tokenType == "reserved_prt") {
            if (!tokens.empty() && tokens.front()[0] == "symbol_parameter_init")
                tokens.pop(); // remove "("
            bool exprError = false;
            string printExprType = evaluateExpression(tokens, "symbol_parameter_end", "", false, scopeManager, exprError, false, true);
            if (exprError)
                errorFound = true;
            if (!tokens.empty() && tokens.front()[0] == "symbol_parameter_end")
                tokens.pop(); // remove ")"
            continue;
        }
        // Declaração de variável.
        if (tokenType == "typeInt" || tokenType == "typeDouble" ||
            tokenType == "typeBoolean" || tokenType == "typeStr") {
            string declaredType;
            if (tokenType == "typeInt")
                declaredType = "int";
            else if (tokenType == "typeDouble")
                declaredType = "double";
            else if (tokenType == "typeBoolean")
                declaredType = "bool";
            else if (tokenType == "typeStr")
                declaredType = "str";
            if (tokens.empty()) {
                cerr << "Erro na linha " << line << ": Identificador esperado apos a declaracao de tipo." << endl;
                errorFound = true;
                continue;
            }
            vector<string> idToken = tokens.front();
            tokens.pop();
            if (idToken[0] != "id") {
                cerr << "Erro na linha " << idToken[2] << ": Esperava um identificador, encontrado '" 
                     << idToken[1] << "'." << endl;
                errorFound = true;
                continue;
            }
            string varName = idToken[1];
            if (!scopeManager.addVariable(varName, declaredType)) {
                cerr << "Erro na linha " << idToken[2] << ": Variavel '" << varName 
                     << "' ja declarada." << endl;
                errorFound = true;
            }
            if (!tokens.empty() && tokens.front()[0] == "op_rel_equal") {
                tokens.pop(); // remove "="
                bool exprError = false;
                string exprType = evaluateExpression(tokens, "end_line", declaredType, true, scopeManager, exprError);
                if (exprError)
                    errorFound = true;
                if (!tokens.empty() && tokens.front()[0] == "end_line")
                    tokens.pop();
            } else {
                if (!tokens.empty() && tokens.front()[0] == "end_line")
                    tokens.pop();
            }
            continue;
        }
        // Atribuição simples fora de declaração.
        if (tokenType == "id") {
            string varType = scopeManager.lookupVariable(lexeme);
            if (varType == "") {
                cerr << "Erro na linha " << line << ": Variavel '" << lexeme << "' nao declarada." << endl;
                errorFound = true;
                continue;
            }
            if (!tokens.empty() && tokens.front()[0] == "op_rel_equal") {
                tokens.pop(); // remove "="
                bool exprError = false;
                string exprType = evaluateExpression(tokens, "end_line", varType, true, scopeManager, exprError);
                if (exprError)
                    errorFound = true;
                if (!tokens.empty() && tokens.front()[0] == "end_line")
                    tokens.pop();
            }
            continue;
        }
        // Outros tokens...
    }

    if (!errorFound)
        cout << "Analise semantica concluida sem erros." << endl;
}

//-----------------------------------------------------------------
// Função main: Leitura dos tokens e chamada da análise semântica
//-----------------------------------------------------------------
int main() {
    ifstream file("../lex/outputLex.txt");
    if (!file) {
        cerr << "Erro ao abrir o arquivo de saida do lexico!" << endl;
        return 1;
    }
    vector<vector<string>> tokensVector;
    string linha;
    while (getline(file, linha)) {
        vector<string> vetor;
        linha.erase(remove(linha.begin(), linha.end(), '['), linha.end());
        linha.erase(remove(linha.begin(), linha.end(), ']'), linha.end());
        size_t pos = 0;
        string tokenStr;
        while ((pos = linha.find(' ')) != string::npos) {
            tokenStr = linha.substr(0, pos);
            tokenStr.erase(remove(tokenStr.begin(), tokenStr.end(), ' '), tokenStr.end());
            tokenStr.erase(remove(tokenStr.begin(), tokenStr.end(), ','), tokenStr.end());
            if (!tokenStr.empty())
                vetor.push_back(tokenStr);
            linha.erase(0, pos + 1);
        }
        linha.erase(remove(linha.begin(), linha.end(), ' '), linha.end());
        linha.erase(remove(linha.begin(), linha.end(), ','), linha.end());
        if (!linha.empty())
            vetor.push_back(linha);
        if (vetor.size() == 3)
            tokensVector.push_back(vetor);
    }
    file.close();

    if (tokensVector.size() > 6) {
        vector<vector<string>> filteredTokens(tokensVector.begin() + 5, tokensVector.end() - 1);
        queue<vector<string>> tokensQueue;
        for (const auto &token : filteredTokens)
            tokensQueue.push(token);
        semanticAnalysis(tokensQueue);
    } else {
        cerr << "Erro: tokens insuficientes para remover header e footer." << endl;
    }
    return 0;
}
