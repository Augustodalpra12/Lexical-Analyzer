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

    addRule("ID_OR_STRING'", "op_arit_sum", "op_arit_sum <ID_OR_STRING''> <ID_OR_STRING'>"); // pronto
    addRule("ID_OR_STRING'", "symbol_parameter_end", "ε");

    addRule("ID_OR_STRING''", "id", "id"); // pronto
    addRule("ID_OR_STRING''", "integer", "integer");
    addRule("ID_OR_STRING''", "double", "double");
    addRule("ID_OR_STRING''", "text_between_quotes", "text_between_quotes");
    addRule("ID_OR_STRING''", "symbol_parameter_end", "sinc");
    addRule("ID_OR_STRING''", "op_arit_sum", "sinc");

    addRule("SCAN", "reserved_scn", "reserved_scn symbol_parameter_init id symbol_parameter_end end_line"); // pronto
    addRule("SCAN", "symbol_op_end", "sinc");
    addRule("SCAN", "typeInt", "sinc");
    addRule("SCAN", "typeDouble", "sinc");
    addRule("SCAN", "typeBoolean", "sinc");
    addRule("SCAN", "reserved_prt", "sinc");
    addRule("SCAN", "reserved_scn", "sinc");
    addRule("SCAN", "laps", "sinc");
    addRule("SCAN", "circuit", "sinc");
    addRule("SCAN", "pitEntry", "sinc");
    addRule("SCAN", "typeStr", "sinc");
    addRule("SCAN", "id", "sinc");

    addRule("LAPS", "laps", "laps symbol_parameter_init <INIT_LAPS> op_rel_equal <ID_OR_VALUE> symbol_op_mid id <REL_SYMBOLS> <ID_OR_VALUE> symbol_op_mid id op_rel_equal <LAPS_INC> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"); // pronto
    addRule("LAPS", "symbol_op_end", "sinc");
    addRule("LAPS", "typeInt", "sinc");
    addRule("LAPS", "typeDouble", "sinc");
    addRule("LAPS", "typeBoolean", "sinc");
    addRule("LAPS", "reserved_prt", "sinc");
    addRule("LAPS", "reserved_scn", "sinc");
    addRule("LAPS", "laps", "sinc");
    addRule("LAPS", "circuit", "sinc");
    addRule("LAPS", "pitEntry", "sinc");
    addRule("LAPS", "typeStr", "sinc");
    addRule("LAPS", "id", "sinc");

    addRule("INIT_LAPS", "typeInt", "typeInt id"); // pronto
    addRule("INIT_LAPS", "id", "id");
    addRule("INIT_LAPS", "op_rel_equal", "sinc");

    addRule("LAPS_INC", "overtake", "overtake"); // pronto
    addRule("LAPS_INC", "brake", "brake");
    addRule("LAPS_INC", "id", "id");
    addRule("LAPS_INC", "symbol_parameter_end", "sinc");

    addRule("LAPS_SYMBOLS", "op_arit_sum", "op_arit_sum"); // pronto
    addRule("LAPS_SYMBOLS", "op_arit_sub", "op_arit_sub");
    addRule("LAPS_SYMBOLS", "op_arit_mult", "op_arit_mult");
    addRule("LAPS_SYMBOLS", "op_arit_div", "op_arit_div");
    addRule("LAPS_SYMBOLS", "id", "sinc");
    addRule("LAPS_SYMBOLS", "integer", "sinc");

    addRule("ID_OR_VALUE", "id", "id"); // pronto
    addRule("ID_OR_VALUE", "integer", "integer");
    addRule("ID_OR_VALUE", "symbol_parameter_end", "sinc");
    addRule("ID_OR_VALUE", "symbol_op_mid", "sinc");

    addRule("CIRCUIT", "circuit", "circuit symbol_parameter_init <CIRCUIT_LOG> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"); // pronto
    addRule("CIRCUIT", "symbol_op_end", "sinc");
    addRule("CIRCUIT", "typeInt", "sinc");
    addRule("CIRCUIT", "typeDouble", "sinc");
    addRule("CIRCUIT", "typeBoolean", "sinc");
    addRule("CIRCUIT", "reserved_prt", "sinc");
    addRule("CIRCUIT", "reserved_scn", "sinc");
    addRule("CIRCUIT", "laps", "sinc");
    addRule("CIRCUIT", "circuit", "sinc");
    addRule("CIRCUIT", "pitEntry", "sinc");
    addRule("CIRCUIT", "typeStr", "sinc");
    addRule("CIRCUIT", "id", "sinc");

    addRule("CIRCUIT_LOG", "id", "id <CIRCUIT_LOG>"); // pronto
    addRule("CIRCUIT_LOG", "integer", "integer <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG", "double", "double <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG", "symbol_parameter_end", "sinc");

    addRule("CIRCUIT_LOG'", "op_arit_sum", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"); // pronto
    addRule("CIRCUIT_LOG'", "op_arit_sub", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_arit_mult", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_arit_div", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_arit_pow", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_rel_minor", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_rel_bigger", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_rel_minor_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_rel_bigger_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_rel_double_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_rel_not_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_rel_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_rel_and", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "op_rel_or", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>");
    addRule("CIRCUIT_LOG'", "symbol_parameter_end", "ε");

    addRule("LOOPS_SYMBOLS", "op_arit_sum", "<ARIT_SYMBOLS>"); // pronto
    addRule("LOOPS_SYMBOLS", "op_arit_sub", "<ARIT_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_arit_mult", "<ARIT_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_arit_div", "<ARIT_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_arit_pow", "<ARIT_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_rel_minor", "<REL_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_rel_bigger", "<REL_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_rel_minor_equal", "<REL_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_rel_bigger_equal", "<REL_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_rel_double_equal", "<REL_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_rel_not_equal", "<REL_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_rel_equal", "<REL_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_rel_and", "<LOG_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "op_rel_or", "<LOG_SYMBOLS>");
    addRule("LOOPS_SYMBOLS", "id", "sinc");
    addRule("LOOPS_SYMBOLS", "integer", "sinc");
    addRule("LOOPS_SYMBOLS", "double", "sinc");

    addRule("ARIT_SYMBOLS", "op_arit_sum", "op_arit_sum"); // pronto
    addRule("ARIT_SYMBOLS", "op_arit_sub", "op_arit_sub");
    addRule("ARIT_SYMBOLS", "op_arit_mult", "op_arit_mult");
    addRule("ARIT_SYMBOLS", "op_arit_div", "op_arit_div");
    addRule("ARIT_SYMBOLS", "op_arit_pow", "op_arit_pow");
    addRule("ARIT_SYMBOLS", "id", "sinc");
    addRule("ARIT_SYMBOLS", "integer", "sinc");
    addRule("ARIT_SYMBOLS", "double", "sinc");

    addRule("LOG_SYMBOLS", "op_log_e", "op_log_e"); // pronto
    addRule("LOG_SYMBOLS", "op_log_or", "op_log_or");
    addRule("LOG_SYMBOLS", "id", "sinc");
    addRule("LOG_SYMBOLS", "integer", "sinc");
    addRule("LOG_SYMBOLS", "double", "sinc");

    addRule("REL_SYMBOLS", "op_rel_minor", "op_rel_minor"); // pronto
    addRule("REL_SYMBOLS", "op_rel_bigger", "op_rel_bigger");
    addRule("REL_SYMBOLS", "op_rel_minor_equal", "op_rel_minor_equal");
    addRule("REL_SYMBOLS", "op_rel_bigger_equal", "op_rel_bigger_equal");
    addRule("REL_SYMBOLS", "op_rel_double_equal", "op_rel_double_equal");
    addRule("REL_SYMBOLS", "op_rel_not_equal", "op_rel_not_equal");
    addRule("REL_SYMBOLS", "id", "sinc");
    addRule("REL_SYMBOLS", "integer", "sinc");
    addRule("REL_SYMBOLS", "double", "sinc");

    addRule("PIT", "pitEntry", "pitEntry symbol_parameter_init <PIT_LOG> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end <PIT_EXIT>"); // pronto
    addRule("PIT", "symbol_op_end", "<sinc'>");
    
    addRule("PIT_LOG", "id", "id <PIT_LOG'>");  // pronto
    addRule("PIT_LOG", "integer", "integer <PIT_LOG'>");
    addRule("PIT_LOG", "double", "double <PIT_LOG'>");
    addRule("PIT_LOG", "symbol_parameter_end", "sinc");

    
    addRule("PIT_LOG'", "op_arit_sum", "<LOOPS_SYMBOLS> <PIT_LOG>");  // pronto
    addRule("PIT_LOG'", "op_arit_sub", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_arit_mult", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_arit_div", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_arit_pow", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_rel_minor", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_rel_bigger", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_rel_minor_equal", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_rel_bigger_equal", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_rel_double_equal", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_rel_not_equal", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_log_and", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "op_log_or", "<LOOPS_SYMBOLS> <PIT_LOG>");
    addRule("PIT_LOG'", "symbol_parameter_end", "ε");

    addRule("PIT_EXIT", "pitExit", "pitExit symbol_op_init <CODE_BLOCK> symbol_op_end");
    addRule("PIT_EXIT", "symbol_op_end", "ε");
    

    // Exibindo a gramática
    cout << "Gramática:" << endl;
    displayGrammar();

    return 0;
}
