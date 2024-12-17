#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

unordered_map <string, unordered_map<string, string>> getTable() {
    unordered_map<string, unordered_map<string, string>> grammarRules = {
        {"S", {{"typeInt", "<BEGIN>"}}},
        {"RESERVED_TYPES", {{"typeInt", "typeInt"},
                            {"typeDouble", "typeDouble"},
                            {"id", "sinc"}}},
        {"BEGIN", {{"typeInt", "typeInt reserved_main symbol_parameter_init symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"}, {"$", "sinc"}}},
        {"CODE_BLOCK", {{"typeInt", "<ATTRIBUTION> <CODE_BLOCK>"},
                        {"typeDouble", "<ATTRIBUTION> <CODE_BLOCK>"},
                        {"id", "<ATTRIBUTION> <CODE_BLOCK>"},
                        {"typeBoolean", "<ATTRIBUTION_BOOL> <CODE_BLOCK>"},
                        {"reserved_prt", "<PRINT> <CODE_BLOCK>"},
                        {"reserved_scn", "<SCAN> <CODE_BLOCK>"},
                        {"laps", "<LAPS> <CODE_BLOCK>"},
                        {"circuit", "<CIRCUIT> <CODE_BLOCK>"},
                        {"pitEntry", "<PIT> <CODE_BLOCK>"},
                        {"typeStr", "<ATTRIBUTION_STR> <CODE_BLOCK>"},
                        {"symbol_op_end", "ε"}}},
                    
        {"EXPRESSION", {{"symbol_parameter_init", "<BOOL_EXPR> <EXPRESSION'> end_line "},
                        {"id", "<BOOL_EXPR> <EXPRESSION'> end_line "},
                        {"double", "<BOOL_EXPR> <EXPRESSION'> end_line "},
                        {"integer", "<BOOL_EXPR> <EXPRESSION'> end_line "},
                        {"bool_false", "<BOOL_EXPR> <EXPRESSION'> end_line"},
                        {"bool_true", "<BOOL_EXPR> <EXPRESSION'> end_line"},
                        {"end_line", "sinc"},
                        {"symbol_parameter_end", "sinc"}}},

        {"EXPRESSION'", {{"op_arit_sum", "op_arit_sum <MULT_DIV> <EXPRESSION'>"},
                        {"op_arit_sub", "op_arit_sub <MULT_DIV> <EXPRESSION'>"},
                        {"end_line", "ε"}}},

        {"BOOL_EXPR", {{"symbol_parameter_init", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"id", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"double", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"integer", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"bool_false", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"bool_true", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"op_arit_sum", "sinc"},
                        {"op_arit_sub", "sinc"},
                        {"end_line", "sinc"}}},

        {"BOOL_EXPR'", {{"op_log_e", "op_bool_e <MULT_DIV> <BOOL_EXPR'>"},
                        {"op_log_or", "op_bool_or <MULT_DIV> <BOOL_EXPR'>"},
                        {"op_arit_sum", "ε"},
                        {"op_arit_sub", "ε"},
                        {"end_line", "ε"}}},

        {"MULT_DIV", {{"symbol_parameter_init", "<POW> <MULT_DIV>'"}, 
                        {"id", "<POW> <MULT_DIV>'"}, 
                        {"double", "<POW> <MULT_DIV>'"}, 
                        {"integer", "<POW> <MULT_DIV>'"},
                        {"bool_false", "<POW> <MULT_DIV'>"},
                        {"bool_true", "<POW> <MULT_DIV'>"},
                        {"op_arit_sum", "sinc"},
                        {"op_arit_sub", "sinc"},
                        {"end_line", "sinc"},
                        {"op_log_e", "sinc"},
                        {"op_log_or", "sinc"}}},

        {"MULT_DIV'", {{"op_arit_mult", "op_arit_mult <POW> <MULT_DIV'>"}, 
                        {"op_arit_div", "op_arit_div <POW> <MULT_DIV'>"}, 
                        {"end_line", "ε"},
                        {"op_arit_sum", "ε"},
                        {"op_arit_sub", "ε"},
                        {"op_log_e", "ε"},
                        {"op_log_or", "ε"}}},

        {"POW", {{"symbol_parameter_init", "<VAR> <POW>'"}, 
                {"id", "<VAR> <POW>'"}, 
                {"double", "<VAR> <POW>'"}, 
                {"integer", "<VAR> <POW>'"},
                {"bool_false", "<VAR> <POW>"},
                {"bool_true", "<VAR> <POW>"},
                {"op_arit_mult", "sinc"},
                {"op_arit_div", "sinc"},
                {"end_line", "sinc"},
                {"op_log_e", "sinc"},
                {"op_log_or", "sinc"},
                {"op_arit_sum", "sinc"},
                {"op_arit_sub", "sinc"}}},

        {"POW'", {{"op_arit_pow", "op_arit_pow <VAR> <POW'>"}, 
                        {"end_line", "ε"},
                        {"op_arit_mult", "ε"},
                        {"op_arit_div", "ε"},
                        {"op_arit_sum", "ε"},
                        {"op_arit_sub", "ε"},
                        {"op_log_e", "ε"},
                        {"op_log_or", "ε"}}},

        {"VAR", {{"symbol_parameter_init", "symbol_parameter_init <EXPRESSION> symbol_parameter_end"},
                 {"id", "id"},	
                 {"double", "double"},
                 {"integer", "integer"},
                 {"bool_false", "<VAR> <POW>"},
                {"bool_true", "<VAR> <POW>"},
                {"op_arit_mult", "sinc"},
                {"op_arit_div", "sinc"},
                {"end_line", "sinc"},
                {"op_log_e", "sinc"},
                {"op_log_or", "sinc"},
                {"op_arit_sum", "sinc"},
                {"op_arit_sub", "sinc"},
                {"op_arit_pow", "sinc"}}},

        {"ATTRIBUTION_VALUE", {{"bool_false", "bool_false end_line"},
                {"bool_true", "bool_true end_line"},
                {"text_between_quotes", "text_between_quotes end_line"},
                {"symbol_parameter_init", "<EXPRESSION>"},
                {"id", "<EXPRESSION>"},
                {"double", "<EXPRESSION>"},
                {"integer", "<EXPRESSION>"},
                {"end_line", "sinc"}}},

        {"ATTRIBUTION", {{"typeInt", "<RESERVED_TYPES> <ATTRIBUTION>'"},
                 {"typeDouble", "<RESERVED_TYPES> <ATTRIBUTION>'"},
                 {"id", "<ATTRIBUTION'>"},
                 {"symbol_op_end", "sinc"},
                 {"typeInt", "sinc"},
                 {"typeDouble", "sinc"},
                 {"typeBoolean", "sinc"},
                 {"reserved_prt", "sinc"},
                 {"reserved_scn", "sinc"},
                 {"laps", "sinc"},
                 {"circuit", "sinc"},
                 {"pitEntry", "sinc"},
                 {"typeStr", "sinc"},
                 {"id", "sinc"}}},
                // id <ATTRIBUTION''>
        {"ATTRIBUTION'", {{"id", "id <ATTRIBUTION''>"},
                 {"symbol_op_end", "sinc"},
                 {"typeInt", "sinc"},
                 {"typeDouble", "sinc"},
                 {"typeBoolean", "sinc"},
                 {"reserved_prt", "sinc"},
                 {"reserved_scn", "sinc"},
                 {"laps", "sinc"},
                 {"circuit", "sinc"},
                 {"pitEntry", "sinc"},
                 {"typeStr", "sinc"},
                 {"id", "sinc"}}},

        {"ATTRIBUTION''", {{"op_rel_equal", "op_rel_equal <ATTRIBUTION_VALUE>"},
                 {"symbol_op_end", "sinc"},
                 {"typeInt", "sinc"},
                 {"typeDouble", "sinc"},
                 {"typeBoolean", "sinc"},
                 {"reserved_prt", "sinc"},
                 {"reserved_scn", "sinc"},
                 {"laps", "sinc"},
                 {"circuit", "sinc"},
                 {"pitEntry", "sinc"},
                 {"typeStr", "sinc"},
                 {"id", "sinc"}}},

        {"ATTRIBUTION_BOOL", {{"typeBoolean", "typeBoolean id <ATTRIBUTION_BOOL'>"},
                 {"symbol_op_end", "sinc"},
                 {"typeInt", "sinc"},
                 {"typeDouble", "sinc"},
                 {"typeBoolean", "sinc"},
                 {"reserved_prt", "sinc"},
                 {"reserved_scn", "sinc"},
                 {"laps", "sinc"},
                 {"circuit", "sinc"},
                 {"pitEntry", "sinc"},
                 {"typeStr", "sinc"},
                 {"id", "sinc"}}},

        {"ATTRIBUTION_BOOL'", {{"op_rel_equal", "op_rel_equal <ATTRIBUTION_BOOL''> "},
                        {"end_line", "endline"},
                        {"symbol_op_end", "sinc"},
                        {"typeInt", "sinc"},
                        {"typeDouble", "sinc"},
                        {"typeBoolean", "sinc"},
                        {"reserved_prt", "sinc"},
                        {"reserved_scn", "sinc"},
                        {"laps", "sinc"},
                        {"circuit", "sinc"},
                        {"pitEntry", "sinc"},
                        {"typeStr", "sinc"},
                        {"id", "sinc"}}},


        {"ATTRIBUTION_BOOL''", {{"bool_false", "bool_false end_line"},
                {"bool_true", "bool_true end_line"},
                {"id", "<ID_OR_VALUE> <ATTRIBUTION_BOOL'''> end_line"},
                {"double", "<ID_OR_VALUE> <ATTRIBUTION_BOOL'''> end_line"},
                {"integer", "<ID_OR_VALUE> <ATTRIBUTION_BOOL'''> end_line"},
                {"op_rel_not", "op_rel_not <ID_OR_VALUE> <ATTRIBUTION_BOOL'''> end_line"},
                {"symbol_op_end", "sinc"},
                {"typeInt", "sinc"},
                {"typeDouble", "sinc"},
                {"typeBoolean", "sinc"},
                {"reserved_prt", "sinc"},
                {"reserved_scn", "sinc"},
                {"laps", "sinc"},
                {"circuit", "sinc"},
                {"pitEntry", "sinc"},
                {"typeStr", "sinc"},
                {"id", "sinc"}}},

        {"ATTRIBUTION_BOOL'''", {{"op_log_e", "<LOG_SYMBOLS> <ID_OR_VALUE> <ATTRIBUTION_BOOL'''>"},
                                {"op_log_or", "<LOG_SYMBOLS> <ID_OR_VALUE> <ATTRIBUTION_BOOL'''>"},
                                {"end_line", " ε"}}},

        {"ATTRIBUTION_STR", {{"typeStr", "typeStr id <ATTRIBUTION_STR'>"},
                {"symbol_op_end", "sinc"},
                {"typeInt", "sinc"},
                {"typeDouble", "sinc"},
                {"typeBoolean", "sinc"},
                {"reserved_prt", "sinc"},
                {"reserved_scn", "sinc"},
                {"laps", "sinc"},
                {"circuit", "sinc"},
                {"pitEntry", "sinc"},
                {"typeStr", "sinc"},
                {"id", "sinc"}}},

        {"ATTRIBUTION_STR'", {{"op_rel_equal", "op_rel_equal text_between_quotes end_line"},
                {"symbol_op_end", "sinc"},
                {"typeInt", "sinc"},
                {"typeDouble", "sinc"},
                {"typeBoolean", "sinc"},
                {"reserved_prt", "sinc"},
                {"reserved_scn", "sinc"},
                {"laps", "sinc"},
                {"circuit", "sinc"},
                {"pitEntry", "sinc"},
                {"typeStr", "sinc"},
                {"id", "sinc"}}},

        {"PRINT", {{"reserved_prt", "reserved_prt symbol_parameter_init <ID_OR_STRING> symbol_parameter_end end_line"},
                {"symbol_op_end", "sinc"},
                {"typeInt", "sinc"},
                {"typeDouble", "sinc"},
                {"typeBoolean", "sinc"},
                {"reserved_prt", "sinc"},
                {"reserved_scn", "sinc"},
                {"laps", "sinc"},
                {"circuit", "sinc"},
                {"pitEntry", "sinc"},
                {"typeStr", "sinc"},
                {"id", "sinc"}}},

        {"ID_OR_STRING", {{"id", "id <ID_OR_STRING'>"},
                          {"double", "double <ID_OR_STRING'>"},
                          {"integer", "integer <ID_OR_STRING'>"},
                          {"text_between_quotes", "text_between_quotes <ID_OR_STRING'>"},
                          {"symbol_parameter_end", "sinc"}}},

        {"ID_OR_STRING'", {{"op_arit_sum", "op_arit_sum <ID_OR_STRING''> <ID_OR_STRING'>"},
                           {"symbol_parameter_end", "ε"}}},   

        {"ID_OR_STRING''", {{"id", "id"},
                            {"double", "double"},
                            {"integer", "integer"},
                            {"text_between_quotes", "text_between_quotes"},
                            {"symbol_parameter_end", "sinc"},
                            {"op_arit_sum", "sinc"}}},


        {"SCAN", {{"reserved_scn", "reserved_scn symbol_parameter_init id symbol_parameter_end end_line"},
                {"symbol_op_end", "sinc"},
                {"typeInt", "sinc"},
                {"typeDouble", "sinc"},
                {"typeBoolean", "sinc"},
                {"reserved_prt", "sinc"},
                {"reserved_scn", "sinc"},
                {"laps", "sinc"},
                {"circuit", "sinc"},
                {"pitEntry", "sinc"},
                {"typeStr", "sinc"},
                {"id", "sinc"}}},

        {"LAPS", {{"laps", "laps symbol_parameter_init <INIT_LAPS> op_rel_equal <ID_OR_VALUE> symbol_op_mid id <REL_SYMBOLS> <ID_OR_VALUE> symbol_op_mid id op_rel_equal <LAPS_INC> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"},
                {"symbol_op_end", "sinc"},
                {"typeInt", "sinc"},
                {"typeDouble", "sinc"},
                {"typeBoolean", "sinc"},
                {"reserved_prt", "sinc"},
                {"reserved_scn", "sinc"},
                {"laps", "sinc"},
                {"circuit", "sinc"},
                {"pitEntry", "sinc"},
                {"typeStr", "sinc"},
                {"id", "sinc"}}},
        
        {"INIT_LAPS", {{"typeInt", "typeInt id"},
                       {"id", "id"},
                       {"op_rel_equal", "sinc"}}},

        {"LAPS_INC", {{"id", "id"},
                       {"brake", "brake"},
                       {"overtake", "overtake"},
                       {"symbol_parameter_end", "sinc"}}},

        {"LAPS_SYMBOLS", {{"op_arit_sum", "op_arit_sum"},
                       {"op_arit_sub", "op_arit_sub"},
                       {"op_arit_mult", "op_arit_mult"},
                       {"op_arit_div", "op_arit_div"},
                       {"id", "sinc"},
                       {"integer", "sinc"}}},
        
        {"ID_OR_VALUE", {{"id", "id"},
                         {"integer", "integer"},
                         {"symbol_parameter_end", "sinc"},
                         {"symbol_op_mid", "sinc"}}},

         
        {"CIRCUIT", {{"circuit", "circuit symbol_parameter_init <CIRCUIT_LOG> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"},
                {"symbol_op_end", "sinc"},
                {"typeInt", "sinc"},
                {"typeDouble", "sinc"},
                {"typeBoolean", "sinc"},
                {"reserved_prt", "sinc"},
                {"reserved_scn", "sinc"},
                {"laps", "sinc"},
                {"circuit", "sinc"},
                {"pitEntry", "sinc"},
                {"typeStr", "sinc"},
                {"id", "sinc"}}},

        {"CIRCUIT_LOG", {{"id", "id <CIRCUIT_LOG'>"},
                         {"integer", "integer <CIRCUIT_LOG'>"},
                         {"double", "double <CIRCUIT_LOG'>"},
                         {"symbol_parameter_end", "sinc"}}},

        {"CIRCUIT_LOG'", {{"op_arit_sum", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_sub", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_mult", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_div", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_pow", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_minor", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_bigger", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_double_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_minor_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_bigger_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_not_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_and", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_or", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"symbol_parameter_end", "ε"}}},

        {"LOOPS_SYMBOLS", {{"op_arit_sum", "<ARIT_SYMBOLS>"},
                           {"op_arit_sub", "<ARIT_SYMBOLS>"},
                           {"op_arit_mult", "<ARIT_SYMBOLS>"},
                           {"op_arit_div", "<ARIT_SYMBOLS>"},
                           {"op_arit_pow", "<ARIT_SYMBOLS>"},
                           {"op_rel_minor", "<REL_SYMBOLS>"},
                           {"op_rel_bigger", "<REL_SYMBOLS>"},
                           {"op_rel_equal", "<REL_SYMBOLS>"},
                           {"op_rel_double_equal", "<REL_SYMBOLS>"},
                           {"op_rel_minor_equal", "<REL_SYMBOLS>"},
                           {"op_rel_bigger_equal", "<REL_SYMBOLS>"},
                           {"op_rel_not_equal", "<REL_SYMBOLS>"},
                           {"op_rel_and", "<LOG_SYMBOLS>"}, 
                           {"op_rel_or", "<LOG_SYMBOLS>"},
                           {"id", "sinc"},
                           {"integer", "sinc"},
                           {"double", "sinc"}}},  

        {"ARIT_SYMBOLS", {{"op_arit_sum", "op_arit_sum"},
                           {"op_arit_sub", "op_arit_sub"},
                           {"op_arit_mult", "op_arit_mult"},
                           {"op_arit_div", "op_arit_div"},
                           {"op_arit_pow", "op_arit_pow"},
                           {"id", "sinc"},
                           {"integer", "sinc"},
                           {"double", "sinc"}}},

        {"LOG_SYMBOLS", {{"op_log_e", "op_log_e"},
                        {"op_log_or", "op_log_or"},
                        {"id", "sinc"},
                        {"integer", "sinc"},
                        {"double", "sinc"}}},

        {"REL_SYMBOLS", {{"op_rel_minor", "op_rel_minor"},
                         {"op_rel_bigger", "op_rel_bigger"},
                         {"op_rel_double_equal", "op_rel_double_equal"},
                         {"op_rel_minor_equal", "op_rel_minor_equal"},
                         {"op_rel_bigger_equal", "op_rel_bigger_equal"},
                         {"op_rel_not_equal", "op_rel_not_equal"},
                         {"id", "sinc"},
                         {"integer", "sinc"},
                         {"double", "sinc"}}},



        {"PIT", {{"pitEntry", "pitEntry symbol_parameter_init <PIT_LOG> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end <PIT_EXIT>"},
                 {"symbol_op_end", "sinc"}}},
        
        {"PIT_LOG", {{"id", "id <PIT_LOG'>"},
                     {"integer", "integer <PIT_LOG'>"},
                     {"double", "double <PIT_LOG'>"},
                     {"symbol_parameter_end", "sinc"}}},

        {"PIT_LOG'", {{"op_arit_sum", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_sub", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_mult", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_div", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_pow", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_minor", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_bigger", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_equal", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_double_equal", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_minor_equal", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_bigger_equal", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_not_equal", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_and", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_or", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"symbol_parameter_end", "ε"}}},

        {"PIT_EXIT", {{"pitExit", "pitExit symbol_op_init <CODE_BLOCK> symbol_op_end"},
                        {"symbol_op_end", "ε"}}},


    };
    return grammarRules;
}

unordered_map <string, string> getTerminals() {
    unordered_map<string, string> terminals = {
        {"symbol_op_init", "{"},
        {"symbol_op_end", "}"},
        {"quotes", "\""},
        {"symbol_parameter_init", "("},
        {"symbol_parameter_end", ")"},
        {"symbol_op_mid", ";"},
        {"op_arit_sum", "+"},
        {"op_arit_sub", "-"},
        {"op_arit_mult", "*"},
        {"op_arit_div", "/"},
        {"op_arit_pow", "^"},
        {"op_rel_minor", "<"},
        {"op_rel_bigger", ">"},
        {"op_rel_equal", "="},
        {"op_rel_not", "!"},
        {"op_rel_double_equal", "=="},
        {"op_rel_minor_equal", "<="},
        {"op_rel_bigger_equal", ">="},
        {"op_rel_not_equal", "!="},
        {"integer", "integer value"},
        {"double", "double value"},
        {"laps", "laps"},
        {"circuit", "circuit"},
        {"pitEntry", "pitEntry"},
        {"pitExit", "pitExit"},
        {"overtake", "overtake"},
        {"brake", "brake"},
        {"reserved_main", "race"},
        {"typeInt", "int"},
        {"typeDouble", "double"},
        {"typeBoolean", "bool"}, // checar se é bool ou boolean
        {"typeStr", "string"},
        {"reserved_prt", "prt"},
        {"reserved_scn", "scn"},
        {"bool_true", "true"},
        {"bool_false", "false"},
        {"id", "id"},
        {"end_line", "."},
        {"text_between_quotes", "text between quotes, \"Hello World\""},
        {"op_rel_e", "&&"},
        {"op_rel_or", "||"},
    };

    return terminals;
}

struct GrammarRule {
   string nonTerminal;
   string terminal;
   string production;
};


