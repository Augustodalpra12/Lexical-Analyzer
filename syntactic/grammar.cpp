#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Estrutura Rule para armazenar uma regra
struct Rule {
    string terminal;    // Terminal associado
    string production;  // Produção associada
};

// Hashmap que associa um não-terminal à sua regra
unordered_map<string, Rule> grammarMap;

// Função para adicionar uma regra no hashmap
void addRule(const string& nonTerminal, const string& terminal, const string& production) {
    grammarMap[nonTerminal] = {terminal, production};
}

// Função para exibir todas as regras da gramática
void displayGrammar() {
    for (const auto& entry : grammarMap) {
        cout << "Non-terminal: " << entry.first
             << ", Terminal: " << entry.second.terminal
             << " -> Production: " << entry.second.production << endl;
    }
}

int main() {
    // Adicionando regras ao hashmap
    addRule("S", "typeInt", "<BEGIN>"); // pronto

    addRule("RESERVED_TYPES", "typeInt", "typeInt"); // pronto
    addRule("RESERVED_TYPES", "typeDouble", "typeDouble");
    addRule("RESERVED_TYPES", "id", "sinc");

    addRule("BEGIN", "typeInt", "typeInt reserved_main symbol_parameter_init symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"); // pronto
    addRule("BEGIN", "$", "sinc");

    addRule("CODE_BLOCK", "typeInt", "<ATTRIBUTION> <CODE_BLOCK>"); // pronto
    addRule("CODE_BLOCK", "typeDouble", "<ATTRIBUTION> <CODE_BLOCK>");
    addRule("CODE_BLOCK", "id", "<ATTRIBUTION> <CODE_BLOCK>");
    addRule("CODE_BLOCK", "typeBoolean", "<ATTRIBUTION_BOOL> <CODE_BLOCK>");
    addRule("CODE_BLOCK", "reserved_prt", "<PRINT> <CODE_BLOCK>");
    addRule("CODE_BLOCK", "reserved_scn", "<SCAN> <CODE_BLOCK>");
    addRule("CODE_BLOCK", "laps", "<LAPS> <CODE_BLOCK>");
    addRule("CODE_BLOCK", "circuit", "<CIRCUIT> <CODE_BLOCK>");
    addRule("CODE_BLOCK", "pitEntry", "<PIT> <CODE_BLOCK>");
    addRule("CODE_BLOCK", "typeStr", "<ATTRIBUTION_STR> <CODE_BLOCK>");
    addRule("CODE_BLOCK", "symbol_op_end", "ε");

    addRule("EXPRESSION", "symbol_parameter_init", "<BOOL_EXPR> <EXPRESSION'> end_line");  // pronto
    addRule("EXPRESSION", "id", "<BOOL_EXPR> <EXPRESSION'> end_line");
    addRule("EXPRESSION", "double", "<BOOL_EXPR> <EXPRESSION'> end_line");
    addRule("EXPRESSION", "integer", "<BOOL_EXPR> <EXPRESSION'> end_line");
    addRule("EXPRESSION", "bool_false", "<BOOL_EXPR> <EXPRESSION'> end_line");
    addRule("EXPRESSION", "bool_true", "<BOOL_EXPR> <EXPRESSION'> end_line");
    addRule("EXPRESSION", "end_line", "sinc");
    addRule("EXPRESSION", "symbol_parameter_end", "sinc");

    addRule("EXPRESSION'", "op_arit_sum", "op_arit_sum <MULT_DIV> <EXPRESSION'>"); // pronto
    addRule("EXPRESSION'", "op_arit_sub", "op_arit_sub <MULT_DIV> <EXPRESSION'>");
    addRule("EXPRESSION'", "end_line", "ε");

    addRule("BOOL_EXPR", "symbol_parameter_init", "<MULT_DIV> <BOOL_EXPR'>"); // pronto
    addRule("BOOL_EXPR", "id", "<MULT_DIV> <BOOL_EXPR'>");
    addRule("BOOL_EXPR", "double", "<MULT_DIV> <BOOL_EXPR'>");
    addRule("BOOL_EXPR", "integer", "<MULT_DIV> <BOOL_EXPR'>");
    addRule("BOOL_EXPR", "bool_false", "<MULT_DIV> <BOOL_EXPR'>");
    addRule("BOOL_EXPR", "bool_true", "<MULT_DIV> <BOOL_EXPR'>");
    addRule("BOOL_EXPR", "op_arit_sum", "sinc");
    addRule("BOOL_EXPR", "op_arit_sub", "sinc");
    addRule("BOOL_EXPR", "end_line", "sinc");

    addRule("BOOL_EXPR'", "op_log_e", "op_bool_e <MULT_DIV> <BOOL_EXPR'>"); // pronto 
    addRule("BOOL_EXPR'", "op_log_or", "op_bool_or <MULT_DIV> <BOOL_EXPR'>");
    addRule("BOOL_EXPR'", "op_arit_sum", "ε");
    addRule("BOOL_EXPR'", "op_arit_sub", "ε");
    addRule("BOOL_EXPR'", "end_line", "ε");

    addRule("MULT_DIV", "symbol_parameter_init", "<POW> <MULT_DIV>'"); // pronto
    addRule("MULT_DIV", "id", "<POW> <MULT_DIV>'");
    addRule("MULT_DIV", "double", "<POW> <MULT_DIV>'");
    addRule("MULT_DIV", "integer", "<POW> <MULT_DIV>'");
    addRule("MULT_DIV", "bool_false", "<POW> <MULT_DIV>'");
    addRule("MULT_DIV", "bool_true", "<POW> <MULT_DIV>'");
    addRule("MULT_DIV", "op_arit_sum", "sinc");
    addRule("MULT_DIV", "op_arit_sub", "sinc");
    addRule("MULT_DIV", "end_line", "sinc");
    addRule("MULT_DIV", "op_log_e", "sinc");
    addRule("MULT_DIV", "op_log_or", "sinc");   

    addRule("MULT_DIV'", "op_arit_mult", "op_arit_mult <POW> <MULT_DIV>'"); // pronto
    addRule("MULT_DIV'", "op_arit_div", "op_arit_div <POW> <MULT_DIV>'");
    addRule("MULT_DIV'", "end_line", "ε");
    addRule("MULT_DIV'", "op_arit_sum", "ε");
    addRule("MULT_DIV'", "op_arit_sub", "ε");
    addRule("MULT_DIV'", "op_log_e", "ε");
    addRule("MULT_DIV'", "op_log_or", "ε");

    addRule("POW", "symbol_parameter_init", "<VAR> <POW>'"); // pronto
    addRule("POW", "id", "<VAR> <POW>'");
    addRule("POW", "double", "<VAR> <POW>'");
    addRule("POW", "integer", "<VAR> <POW>'");
    addRule("POW", "bool_false", "<VAR> <POW>'");
    addRule("POW", "bool_true", "<VAR> <POW>'");
    addRule("POW", "op_arit_sum", "sinc");
    addRule("POW", "op_arit_sub", "sinc");
    addRule("POW", "end_line", "sinc");
    addRule("POW", "op_arit_mult", "sinc");
    addRule("POW", "op_arit_div", "sinc");
    addRule("POW", "op_log_e", "sinc");
    addRule("POW", "op_log_or", "sinc");

    addRule("POW'", "op_arit_pow", "op_arit_pow <VAR> <POW'>"); // pronto 
    addRule("POW'", "end_line", "ε");
    addRule("POW'", "op_arit_mult", "ε");
    addRule("POW'", "op_arit_div", "ε");
    addRule("POW'", "op_arit_sum", "ε");
    addRule("POW'", "op_arit_sub", "ε");
    addRule("POW'", "op_log_e", "ε");
    addRule("POW'", "op_log_or", "ε");


    addRule("VAR", "symbol_parameter_init", "symbol_parameter_init <EXPRESSION> symbol_parameter_end"); // pronto
    addRule("VAR", "id", "id");
    addRule("VAR", "double", "double");
    addRule("VAR", "integer", "integer");
    addRule("VAR", "bool_false", "<VAR> <POW>");
    addRule("VAR", "bool_true", "<VAR> <POW>");
    addRule("VAR", "op_arit_sum", "sinc");
    addRule("VAR", "op_arit_sub", "sinc");
    addRule("VAR", "op_arit_mult", "sinc");
    addRule("VAR", "op_arit_div", "sinc");
    addRule("VAR", "op_arit_pow", "sinc");
    addRule("VAR", "op_log_e", "sinc");
    addRule("VAR", "op_log_or", "sinc");
    addRule("VAR", "end_line", "sinc");

    addRule("ATTRIBUTION_VALUE", "bool_false", "bool_false end_line"); // pronto
    addRule("ATTRIBUTION_VALUE", "bool_true", "bool_true end_line");
    addRule("ATTRIBUTION_VALUE", "text_between_quotes", "text_between_quotes end_line");
    addRule("ATTRIBUTION_VALUE", "symbol_parameter_init", "<EXPRESSION>");
    addRule("ATTRIBUTION_VALUE", "id", "<EXPRESSION>");
    addRule("ATTRIBUTION_VALUE", "double", "<EXPRESSION>");
    addRule("ATTRIBUTION_VALUE", "integer", "<EXPRESSION>");
    addRule("ATTRIBUTION_VALUE", "end_line", "sinc");

    addRule("ATTRIBUTION", "typeInt", "<RESERVED_TYPES> <ATTRIBUTION>'"); // pronto
    addRule("ATTRIBUTION", "typeDouble", "<RESERVED_TYPES> <ATTRIBUTION>'");
    addRule("ATTRIBUTION", "id", "<ATTRIBUTION>'");
    addRule("ATTRIBUTION", "symbol_op_end", "sinc");
    //addRule("ATTRIBUTION", "typeInt", "sinc"); acho que ta errado
    addRule("ATTRIBUTION", "typeDouble", "sinc");
    addRule("ATTRIBUTION", "typeBoolean", "sinc");
    addRule("ATTRIBUTION", "reserved_prt", "sinc");
    addRule("ATTRIBUTION", "reserved_scn", "sinc");
    addRule("ATTRIBUTION", "laps", "sinc");
    addRule("ATTRIBUTION", "circuit", "sinc");
    addRule("ATTRIBUTION", "pitEntry", "sinc");
    addRule("ATTRIBUTION", "typeStr", "sinc");
    //addRule("ATTRIBUTION", "id", "sinc"); acho que ta errado

    addRule("ATTRIBUTION'", "id", "id <ATTRIBUTION''>"); // pronto
    addRule("ATTRIBUTION'", "symbol_op_end", "sinc");
    addRule("ATTRIBUTION'", "typeInt", "sinc");
    addRule("ATTRIBUTION'", "typeDouble", "sinc");
    addRule("ATTRIBUTION'", "typeBoolean", "sinc");
    addRule("ATTRIBUTION'", "reserved_prt", "sinc");
    addRule("ATTRIBUTION'", "reserved_scn", "sinc");
    addRule("ATTRIBUTION'", "laps", "sinc");
    addRule("ATTRIBUTION'", "circuit", "sinc");
    addRule("ATTRIBUTION'", "pitEntry", "sinc");
    addRule("ATTRIBUTION'", "typeStr", "sinc");
    //addRule("ATTRIBUTION'", "id", "sinc"); acho que ta errado

    addRule("ATTRIBUTION''", "op_rel_equal", "op_rel_equal <ATTRIBUTION_VALUE>"); // pronto
    addRule("ATTRIBUTION''", "symbol_op_end", "sinc");
    addRule("ATTRIBUTION'", "typeInt", "sinc");
    addRule("ATTRIBUTION'", "typeDouble", "sinc");
    addRule("ATTRIBUTION'", "typeBoolean", "sinc");
    addRule("ATTRIBUTION'", "reserved_prt", "sinc");
    addRule("ATTRIBUTION'", "reserved_scn", "sinc");
    addRule("ATTRIBUTION'", "laps", "sinc");
    addRule("ATTRIBUTION'", "circuit", "sinc");
    addRule("ATTRIBUTION'", "pitEntry", "sinc");
    addRule("ATTRIBUTION'", "typeStr", "sinc");
    addRule("ATTRIBUTION'", "id", "sinc");

    addRule("ATTRIBUTION_BOOL", "typeBoolean", "typeBoolean id <ATTRIBUTION_BOOL'>"); // pronto
    addRule("ATTRIBUTION_BOOL", "symbol_op_end", "sinc");
    addRule("ATTRIBUTION_BOOL", "typeInt", "sinc");
    addRule("ATTRIBUTION_BOOL", "typeDouble", "sinc");
    addRule("ATTRIBUTION_BOOL", "typeBoolean", "sinc");
    addRule("ATTRIBUTION_BOOL", "reserved_prt", "sinc");
    addRule("ATTRIBUTION_BOOL", "reserved_scn", "sinc");
    addRule("ATTRIBUTION_BOOL", "laps", "sinc");
    addRule("ATTRIBUTION_BOOL", "circuit", "sinc");
    addRule("ATTRIBUTION_BOOL", "pitEntry", "sinc");
    addRule("ATTRIBUTION_BOOL", "typeStr", "sinc");
    addRule("ATTRIBUTION_BOOL", "id", "sinc");
    
    addRule("ATTRIBUTION_BOOL'", "op_rel_equal", "op_rel_equal  <ATTRIBUTION_BOOL''>"); // pronto
    addRule("ATTRIBUTION_BOOL'", "symbol_op_end", "sinc");
    addRule("ATTRIBUTION_BOOL'", "typeInt", "sinc");
    addRule("ATTRIBUTION_BOOL'", "typeDouble", "sinc");
    addRule("ATTRIBUTION_BOOL'", "typeBoolean", "sinc");
    addRule("ATTRIBUTION_BOOL'", "reserved_prt", "sinc");
    addRule("ATTRIBUTION_BOOL'", "reserved_scn", "sinc");
    addRule("ATTRIBUTION_BOOL'", "laps", "sinc");
    addRule("ATTRIBUTION_BOOL'", "circuit", "sinc");
    addRule("ATTRIBUTION_BOOL'", "pitEntry", "sinc");
    addRule("ATTRIBUTION_BOOL'", "typeStr", "sinc");
    addRule("ATTRIBUTION_BOOL'", "id", "sinc");

    addRule("ATTRIBUTION_BOOL''", "bool_false", "bool_false end_line"); // pronto
    addRule("ATTRIBUTION_BOOL''", "bool_true", "bool_true end_line");
    addRule("ATTRIBUTION_BOOL''", "double", "<ID_OR_VALUE> <ATTRIBUTION_BOOL'''> end_line");
    addRule("ATTRIBUTION_BOOL''", "integer", "<ID_OR_VALUE> <ATTRIBUTION_BOOL'''> end_line");
    addRule("ATTRIBUTION_BOOL''", "op_rel_not", "op_rel_not <ID_OR_VALUE> <ATTRIBUTION_BOOL'''> end_line");
    addRule("ATTRIBUTION_BOOL''", "symbol_op_end", "sinc");
    addRule("ATTRIBUTION_BOOL''", "typeInt", "sinc");
    addRule("ATTRIBUTION_BOOL''", "typeDouble", "sinc");
    addRule("ATTRIBUTION_BOOL''", "typeBoolean", "sinc");
    addRule("ATTRIBUTION_BOOL''", "reserved_prt", "sinc");
    addRule("ATTRIBUTION_BOOL''", "reserved_scn", "sinc");
    addRule("ATTRIBUTION_BOOL''", "laps", "sinc");
    addRule("ATTRIBUTION_BOOL''", "circuit", "sinc");
    addRule("ATTRIBUTION_BOOL''", "pitEntry", "sinc");
    addRule("ATTRIBUTION_BOOL''", "typeStr", "sinc");
    addRule("ATTRIBUTION_BOOL''", "id", "sinc");

    addRule("ATTRIBUTION_BOOL'''", "op_log_e", "<LOG_SYMBOLS> <ID_OR_VALUE> <ATTRIBUTION_BOOL'''>"); // pronto
    addRule("ATTRIBUTION_BOOL'''", "op_log_or", "<LOG_SYMBOLS> <ID_OR_VALUE> <ATTRIBUTION_BOOL'''>");
    addRule("ATTRIBUTION_BOOL'''", "end_line", "ε");

    addRule("ATTRIBUTION_STR", "typeStr", "typeStr id <ATTRIBUTION_STR'>"); // pronto
    addRule("ATTRIBUTION_STR", "symbol_op_end", "sinc");
    addRule("ATTRIBUTION_STR", "typeInt", "sinc");
    addRule("ATTRIBUTION_STR", "typeDouble", "sinc");
    addRule("ATTRIBUTION_STR", "typeBoolean", "sinc");
    addRule("ATTRIBUTION_STR", "reserved_prt", "sinc");
    addRule("ATTRIBUTION_STR", "reserved_scn", "sinc");
    addRule("ATTRIBUTION_STR", "laps", "sinc");
    addRule("ATTRIBUTION_STR", "circuit", "sinc");
    addRule("ATTRIBUTION_STR", "pitEntry", "sinc");
    addRule("ATTRIBUTION_STR", "typeStr", "sinc");
    addRule("ATTRIBUTION_STR", "id", "sinc");

    addRule("ATTRIBUTION_STR'", "op_rel_equal", "op_rel_equal text_between_quotes end_line"); // pronto
    addRule("ATTRIBUTION_STR'", "symbol_op_end", "sinc");
    addRule("ATTRIBUTION_STR'", "typeInt", "sinc");
    addRule("ATTRIBUTION_STR'", "typeDouble", "sinc");
    addRule("ATTRIBUTION_STR'", "typeBoolean", "sinc");
    addRule("ATTRIBUTION_STR'", "reserved_prt", "sinc");
    addRule("ATTRIBUTION_STR'", "reserved_scn", "sinc");
    addRule("ATTRIBUTION_STR'", "laps", "sinc");
    addRule("ATTRIBUTION_STR'", "circuit", "sinc");
    addRule("ATTRIBUTION_STR'", "pitEntry", "sinc");
    addRule("ATTRIBUTION_STR'", "typeStr", "sinc");
    addRule("ATTRIBUTION_STR'", "id", "sinc");

    addRule("PRINT", "reserved_prt", "reserved_prt symbol_parameter_init <ID_OR_STRING> symbol_parameter_end end_line"); // pronto
    addRule("PRINT", "symbol_op_end", "sinc");
    addRule("PRINT", "typeInt", "sinc");
    addRule("PRINT", "typeDouble", "sinc");
    addRule("PRINT", "typeBoolean", "sinc");
    addRule("PRINT", "reserved_prt", "sinc");
    addRule("PRINT", "reserved_scn", "sinc");
    addRule("PRINT", "laps", "sinc");
    addRule("PRINT", "circuit", "sinc");
    addRule("PRINT", "pitEntry", "sinc");
    addRule("PRINT", "typeStr", "sinc");
    addRule("PRINT", "id", "sinc");

    addRule("ID_OR_STRING", "id", "id <ID_OR_STRING'>"); // pronto
    addRule("ID_OR_STRING", "integer", "integer <ID_OR_STRING'>");
    addRule("ID_OR_STRING", "double", "double <ID_OR_STRING'>");
    addRule("ID_OR_STRING", "text_between_quotes", "text_between_quotes <ID_OR_STRING'>");
    addRule("ID_OR_STRING", "symbol_parameter_end", "sinc");

    

    
    





    // Exibindo a gramática
    cout << "Gramática:" << endl;
    displayGrammar();

    return 0;
}
