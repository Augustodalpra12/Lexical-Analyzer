#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

unordered_map<string, vector<string>> getGrammar() {
    // HashMap que armazena as produções da gramática
    unordered_map<string, vector<string>> grammar;

    // Inserindo as regras da gramática no hashmap
    grammar["S"] = {"<BEGIN>"};
    grammar["RESERVED_TYPES"] = {"typeInt", "typeDouble"};
    grammar["BEGIN"] = {
        "typeInt reserved_main symbol_parameter_init symbol_parameter_end symbol_op_end <CODE_BLOCK> symbol_op_end"
    };

    grammar["CODE_BLOCK"] = {
        "<EXPRESSION> <CODE_BLOCK>", "<ATTRIBUTION> <CODE_BLOCK>", "<ATRIBUTION_BOOL> <CODE_BLOCK>", "<PRINT> <CODE_BLOCK>",
        "<SCAN> <CODE_BLOCK>", "<LAPS> <CODE_BLOCK>", "<CIRCUIT> <CODE_BLOCK>", "<PIT> <CODE_BLOCK>", "<ATTRIBUTION_STR> <CODE_BLOCK>",
        "<ATTRIBUTION_CHAR> <CODE_BLOCK>", "<REL> <CODE_BLOCK>", "<LOGIC> <CODE_BLOCK>", "ε"
    };

    grammar["EXPRESSION"] = {"<MULT_DIV> <EXPRESSION'> end_line"};
    grammar["EXPRESSION'"] = {"op_arit_sum <MULT_DIV> <EXPRESSION'>", "op_arit_sub <MULT_DIV> <EXPRESSION'>", "ε"};

    grammar["MULT_DIV"] = {"<POW> <MULT_DIV'>"};
    grammar["MULT_DIV'"] = {"op_arit_mult <POW> <MULT_DIV'>", "op_arit_div <POW> <MULT_DIV'>", "ε"};

    grammar["POW"] = {"<VAR> <POW'>"};
    grammar["POW'"] = {"op_arit_pow <VAR> <POW'>", "ε"};

    grammar["VAR"] = {"symbol_parameter_init <EXPRESSION> symbol_parameter_end", "id", "integer", "double"};

    grammar["REL"] = {"<EXPRESSION> <REL_OP> <EXPRESSION>"};
    grammar["REL_OP"] = {
        "op_rel_minor", "op_rel_bigger", "op_rel_equal", "op_rel_not", "op_rel_double_equal", 
        "op_rel_minor_equal", "op_rel_bigger_equal", "op_rel_not_equal"
    };

    grammar["LOGIC"] = {"<EXPRESSION> <LOGIC_OP> <EXPRESSION>"};
    grammar["LOGIC_OP"] = {"op_log_e_function", "op_log_or_function"};

    // Atribuição
    grammar["ATTRIBUTION"] = {"<RESERVED_TYPES> <ATTRIBUTION'>"};
    grammar["ATTRIBUTION'"] = {"id <ATTRIBUTION''>"};
    grammar["ATTRIBUTION''"] = {"op_rel_equal <EXPRESSION>", "end_line"};

    grammar["ATRIBUTION_BOOL"] = {"typeBoolean id <ATRIBUTION_BOOL'>"};
    grammar["ATRIBUTION_BOOL'"] = {"op_rel_equal <ATTRIBUTION_BOOL''>", "end_line"};
    grammar["ATTRIBUTION_BOOL''"] = {"bool_false end_line", "bool_true end_line"};

    grammar["ATTRIBUTION_STR"] = {"typeStr id <ATTRIBUTION_STR'>"};
    grammar["ATTRIBUTION_STR'"] = {"op_rel_equal quotes all_except_quotes quotes end_line", "end_line"};

    grammar["ATTRIBUTION_CHAR"] = {"typeChar id <ATTRIBUTION_CHAR'>"};
    grammar["ATTRIBUTION_CHAR'"] = {"op_rel_equal quotes char_regex quotes end_line", "end_line"};

    // PRINT
    grammar["PRINT"] = {"reserved_prt symbol_parameter_init <ID_OR_STRING> symbol_parameter_end end_line"};
    grammar["ID_OR_STRING"] = {
        "quotes all_except_quotes quotes <ID_OR_STRING'>", "id <ID_OR_STRING'>", 
        "integer <ID_OR_STRING'>", "double <ID_OR_STRING'>"
    };
    grammar["ID_OR_STRING'"] = {"op_arit_sum <ID_OR_STRING''> <ID_OR_STRING'>", "ε"};
    grammar["ID_OR_STRING''"] = {"quotes all_except_quotes quotes", "id", "integer", "double"};

    // SCAN
    grammar["SCAN"] = {"reserved_scn symbol_parameter_init id symbol_parameter_end end_line"};

    // LAPS
    grammar["LAPS"] = {
        "laps symbol_parameter_init <INIT_LAPS>  op_rel_equal <ID_OR_VALUE> symbol_op_mid id <REL_SYMBOLS> "
        "<ID_OR_VALUE> symbol_op_mid id op_rel_equal <LAPS_INC> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"
    };
    grammar["INIT_LAPS"] = {"typeInt id", "id"};
    grammar["LAPS_INC"] = {"overtake", "brake", "id <LAPS_SYMBOLS> <ID_OR_VALUE>"};
    grammar["LAPS_SYMBOLS"] = {"op_arit_sum", "op_arit_sub", "op_arit_mult", "op_arit_div"};
    grammar["ID_OR_VALUE"] = {"id", "integer"};

    // CIRCUIT
    grammar["CIRCUIT"] = {
        "circuit symbol_parameter_init <CIRCUIT_LOG> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"
    };
    grammar["CIRCUIT_LOG"] = {"id <CIRCUIT_LOG'>", "integer <CIRCUIT_LOG'>", "double <CIRCUIT_LOG'>"};
    grammar["CIRCUIT_LOG'"] = {"<LOOPS_SYMBOLS> <CIRCUIT_LOG>", "ε"};
    grammar["LOOPS_SYMBOLS"] = {"<REL_SYMBOLS>", "<LOG_SYMBOLS>", "<ARIT_SYMBOLS>"};

    grammar["ARIT_SYMBOLS"] = {"op_arit_sum", "op_arit_sub", "op_arit_div", "op_arit_mult", "op_arit_pow"};
    grammar["LOG_SYMBOLS"] = {"op_log_e", "op_log_or"};
    grammar["REL_SYMBOLS"] = {
        "op_rel_minor", "op_rel_bigger", "op_rel_minor_equal", "op_rel_bigger_equal", 
        "op_rel_double_equal", "op_rel_not_equal"
    };

    // PIT
    grammar["PIT"] = {
        "pitEntry symbol_parameter_init <PIT_LOG> symbol_parameter_end symbol_block_init <CODE_BLOCK> symbol_block_end <PIT_EXIT>"
    };
    grammar["PIT_LOG"] = {"id <PIT_LOG'>", "integer <PIT_LOG'>", "double <PIT_LOG'>"};
    grammar["PIT_LOG'"] = {"<LOOPS_SYMBOLS> <PIT_LOG>", "ε"};
    grammar["PIT_EXIT"] = {"pitExit symbol_parameter_init CODE_BLOCK symbol_block_end", "ε"};

    // Iterar e imprimir o conteúdo do hashmap
    // for (const auto& pair : grammar) {
    //     cout << pair.first << " -> ";
    //     for (const auto& production : pair.second) {
    //         cout << production << " | ";
    //     }
    //     cout << endl;
    // }

    

    return grammar;
}

unordered_map <string, vector<string>> getFirst() {
    unordered_map <string, vector<string>> first;

    first["S"] = {"typeInt"};
    first["RESERVED_TYPES"] = {"typeInt", "typeDouble"};
    first["BEGIN"] = {"typeInt"};
    first["CODE_BLOCK"] = {"symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
                           "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar", "ε"};
    first["EXPRESSION"] = {"symbol_parameter_init", "id", "double"};
    first["EXPRESSION'"] = {"op_arit_sum", "op_arit_sub", "ε"};
    first["MULT_DIV"] = {"symbol_parameter_init", "id", "integer", "double"};
    first["MULT_DIV'"] = {"op_arit_mult", "op_arit_div", "ε"};
    first["POW"] = {"symbol_parameter_init", "id", "integer", "double"};
    first["POW'"] = {"op_arit_pow", "ε"};
    first["VAR"] = {"symbol_parameter_init", "id", "integer", "double"};
    first["REL"] = {"symbol_parameter_init", "id", "integer", "double"};
    first["REL_OP"] = {"op_rel_minor", "op_rel_bigger", "op_rel_equal", "op_rel_not", "op_rel_double_equal", 
                       "op_rel_minor_equal", "op_rel_bigger_equal", "op_rel_not_equal"};
    first["LOGIC"] = {"symbol_parameter_init", "id", "integer", "double"};
    first["LOGIC_OP"] = {"op_log_e_function", "op_log_or_function"};
    first["ATTRIBUTION"] = {"typeInt", "typeDouble"};
    first["ATTRIBUTION'"] = {"id"};
    first["ATTRIBUTION''"] = {"op_rel_equal", "end_line"};
    first["ATRIBUTION_BOOL"] = {"typeBoolean"};
    first["ATRIBUTION_BOOL'"] = {"op_rel_equal", "end_line"};
    first["ATRIBUTION_BOOL''"] = {"bool_false", "bool_true"};
    first["ATTRIBUTION_STR"] = {"typeStr"};
    first["ATTRIBUTION_STR'"] = {"op_rel_equal", "end_line"};
    first["ATTRIBUTION_CHAR"] = {"typeChar"};
    first["ATTRIBUTION_CHAR'"] = {"op_rel_equal", "end_line"};
    first["PRINT"] = {"reserved_prt"};
    first["ID_OR_STRING"] = {"quotes", "id", "integer", "double"};
    first["ID_OR_STRING'"] = {"op_arit_sum", "ε"};
    first["ID_OR_STRING''"] = {"quotes", "id", "integer", "double"};
    first["SCAN"] = {"reserved_scn"};
    first["LAPS"] = {"laps"};
    first["INIT_LAPS"] = {"typeInt", "id"};
    first["LAPS_INC"] = {"overtake", "brake", "id"};
    first["LAPS_SYMBOLS"] = {"op_arit_sum", "op_arit_sub", "op_arit_mult", "op_arit_div"};
    first["ID_OR_VALUE"] = {"id", "integer"};
    first["CIRCUIT"] = {"circuit"};
    first["CIRCUIT_LOG"] = {"id", "integer", "double"};
    first["CIRCUIT_LOG'"] = {"op_arit_sum", "op_arit_sub", "op_arit_div", "op_arit_mult", "op_arit_pow", 
                             "op_log_e", "op_log_or", "op_rel_minor", "op_rel_bigger", "op_rel_minor_equal", 
                             "op_rel_bigger_equal", "op_rel_double_equal", "op_rel_not_equal", "ε"};
    first["LOOPS_SYMBOLS"] = {"op_arit_sum", "op_arit_sub", "op_arit_div", "op_arit_mult", "op_arit_pow", 
                              "op_log_e", "op_log_or", "op_rel_minor", "op_rel_bigger", "op_rel_minor_equal", 
                              "op_rel_bigger_equal", "op_rel_double_equal", "op_rel_not_equal"};
    first["ARIT_SYMBOLS"] = {"op_arit_sum", "op_arit_sub", "op_arit_div", "op_arit_mult", "op_arit_pow"};
    first["LOG_SYMBOLS"] = {"op_log_e", "op_log_or"};
    first["REL_SYMBOLS"] = {"op_rel_minor", "op_rel_bigger", "op_rel_minor_equal", "op_rel_bigger_equal", 
                            "op_rel_double_equal", "op_rel_not_equal"};
    first["PIT"] = {"pitEntry"};
    first["PIT_LOG"] = {"id", "integer", "double"};
    first["PIT_LOG'"] = {"op_arit_sum", "op_arit_sub", "op_arit_div", "op_arit_mult", "op_arit_pow", 
                         "op_log_e", "op_log_or", "op_rel_minor", "op_rel_bigger", "op_rel_minor_equal", 
                         "op_rel_bigger_equal", "op_rel_double_equal", "op_rel_not_equal", "ε"};
    first["PIT_EXIT"] = {"pitExit", "ε"};

    return first;
}

unordered_map<string, vector<string>> getFollow() {
    unordered_map<string, vector<string>> follow;

    follow["S"] = {"$"};
    follow["RESERVED_TYPES"] = {"typeInt", "typeDouble"};
    follow["BEGIN"] = {"$"};
    follow["CODE_BLOCK"] = {"symbol_op_end"};
    follow["EXPRESSION"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", "reserved_prt", 
        "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar", "symbol_parameter_end", 
        "op_rel_minor", "op_rel_bigger", "op_rel_equal", "op_rel_not", "op_rel_double_equal", 
        "op_rel_minor_equal", "op_rel_bigger_equal", "op_rel_not_equal", "op_log_e_function", 
        "op_log_or_function"
    };
    follow["EXPRESSION'"] = {"end_line"};
    follow["MULT_DIV"] = {"op_arit_sum", "op_arit_sub"};
    follow["MULT_DIV'"] = {"op_arit_sum", "op_arit_sub"};
    follow["POW"] = {"op_arit_mult", "op_arit_div"};
    follow["POW'"] = {"op_arit_mult", "op_arit_div"};
    follow["VAR"] = {"op_arit_pow"};
    follow["REL"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["REL_OP"] = {};
    follow["LOGIC"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["LOGIC_OP"] = {"symbol_parameter_init", "id", "double"};
    follow["ATTRIBUTION"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["ATTRIBUTION'"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["ATTRIBUTION''"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["ATRIBUTION_BOOL"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["ATRIBUTION_BOOL'"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["ATRIBUTION_BOOL''"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["ATTRIBUTION_STR"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["ATTRIBUTION_STR'"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["ATTRIBUTION_CHAR"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["ATTRIBUTION_CHAR'"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["PRINT"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["ID_OR_STRING"] = {"symbol_parameter_end"};
    follow["ID_OR_STRING'"] = {"symbol_parameter_end"};
    follow["ID_OR_STRING''"] = {"symbol_parameter_end"};
    follow["SCAN"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["LAPS"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["INIT_LAPS"] = {"op_rel_equal"};
    follow["LAPS_INC"] = {"symbol_parameter_end"};
    follow["LAPS_SYMBOLS"] = {"id", "integer"};
    follow["ID_OR_VALUE"] = {"symbol_op_mid", "symbol_parameter_end"};
    follow["CIRCUIT"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["CIRCUIT_LOG"] = {"symbol_parameter_end"};
    follow["CIRCUIT_LOG'"] = {"symbol_parameter_end"};
    follow["LOOPS_SYMBOLS"] = {"id", "integer", "double"};
    follow["ARIT_SYMBOLS"] = {"id", "integer", "double"};
    follow["LOG_SYMBOLS"] = {"id", "integer", "double"};
    follow["REL_SYMBOLS"] = {"id", "integer", "double"};
    follow["PIT"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };
    follow["PIT_LOG"] = {"symbol_parameter_end"};
    follow["PIT_LOG'"] = {"symbol_parameter_end"};
    follow["PIT_EXIT"] = {
        "symbol_parameter_init", "id", "double", "typeInt", "typeDouble", "typeBoolean", 
        "reserved_prt", "reserved_scn", "laps", "circuit", "pitEntry", "typeStr", "typeChar"
    };

    return follow;
}

unordered_map <string, unordered_map<string, string>> getTable() {
    unordered_map<string, unordered_map<string, string>> grammarRules = {
        {"S", {{"typeInt", "S -> <BEGIN>"}}},
        {"RESERVED_TYPES", {{"typeInt", "RESERVED_TYPES -> typeInt"}, {"typeDouble", "RESERVED_TYPES -> typeDouble"}}},
        {"BEGIN", {{"typeInt", "BEGIN -> typeInt reserved_main symbol_parameter_init symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"}}},
        {"CODE_BLOCK", {{"typeInt", "CODE_BLOCK -> <ATTRIBUTION> <CODE_BLOCK>"},
                        {"typeDouble", "CODE_BLOCK -> <ATTRIBUTION> <CODE_BLOCK>"},
                        {"symbol_parameter_init", "CODE_BLOCK -> <EXPRESSION> <CODE_BLOCK>"},
                        {"id", "CODE_BLOCK -> <EXPRESSION> <CODE_BLOCK>"},
                        {"double", "CODE_BLOCK -> <EXPRESSION> <CODE_BLOCK>"},
                        {"typeInt", "CODE_BLOCK -> <ATRIBUTION_BOOL> <CODE_BLOCK>"},
                        {"reserved_prt", "CODE_BLOCK -> <PRINT> <CODE_BLOCK>"},
                        {"reserved_scn", "CODE_BLOCK -> <SCAN> <CODE_BLOCK>"},
                        {"laps", "CODE_BLOCK -> <LAPS> <CODE_BLOCK>"},
                        {"circuit", "CODE_BLOCK -> <CIRCUIT> <CODE_BLOCK>"},
                        {"pitEntry", "CODE_BLOCK -> <PIT> <CODE_BLOCK>"},
                        {"typeStr", "CODE_BLOCK -> <ATTRIBUTION_STR> <CODE_BLOCK>"},
                        {"typeChar", "CODE_BLOCK -> <ATTRIBUTION_CHAR> <CODE_BLOCK>"},
                        {"integer", "CODE_BLOCK -> <EXPRESSION> <CODE_BLOCK>"},
                        {"$", "CODE_BLOCK -> ε"}}},
                    
        {"EXPRESSION", {{"symbol_parameter_init", "EXPRESSION -> <MULT_DIV> <EXPRESSION>' end_line"},
                        {"id", "EXPRESSION -> <MULT_DIV> <EXPRESSION>' end_line"},
                        {"double", "EXPRESSION -> <MULT_DIV> <EXPRESSION>' end_line"}}},

        {"EXPRESSION'", {{"op_arit_sum", "EXPRESSION' -> op_arit_sum <MULT_DIV> <EXPRESSION'>"},
                        {"op_arit_sub", "EXPRESSION' -> op_arit_sub <MULT_DIV> <EXPRESSION'>"},
                        {"$", "EXPRESSION' -> ε"}}},

        {"MULT_DIV", {{"symbol_parameter_init", "MULT_DIV -> <POW> <MULT_DIV>'"}, 
                        {"id", "MULT_DIV -> <POW> <MULT_DIV>'"}, 
                        {"double", "MULT_DIV -> <POW> <MULT_DIV>'"}, 
                        {"integer", "MULT_DIV -> <POW> <MULT_DIV>'"}}},

        {"MULT_DIV'", {{"op_arit_mult", "MULT_DIV' -> op_arit_mult <POW> <MULT_DIV'>"}, 
                        {"op_arit_div", "MULT_DIV' -> op_arit_div <POW> <MULT_DIV'>"}, 
                        {"$", "MULT_DIV' -> ε"}}},

        {"POW", {{"symbol_parameter_init", "POW -> <VAR> <POW>'"}, 
                {"id", "POW -> <VAR> <POW>'"}, 
                {"double", "POW -> <VAR> <POW>'"}, 
                {"integer", "POW -> <VAR> <POW>'"}}},

        {"POW", {{"op_arit_pow", "POW' -> op_arit_pow <VAR> <POW'>"}, 
                 {"$", "POW' -> ε"}}},

        {"VAR", {{"symbol_parameter_init", "VAR -> symbol_parameter_init <EXPRESSION> symbol_parameter_end"},
                 {"id", "VAR -> id"},	
                 {"double", "VAR -> double"},
                 {"integer", "VAR -> integer"}}},

        {"REL", {{"symbol_parameter_init", "REL -> <EXPRESSION> <REL_OP> <EXPRESSION>"},
                 {"id", "REL -> <EXPRESSION> <REL_OP> <EXPRESSION>"},	
                 {"double", "REL -> <EXPRESSION> <REL_OP> <EXPRESSION>"},
                 {"integer", "REL -> <EXPRESSION> <REL_OP> <EXPRESSION>"}}},

        {"REL_OP", {{"op_rel_minor", "REL_OP -> op_rel_minor"},
                 {"op_rel_bigger", "REL_OP -> op_rel_bigger"},	
                 {"op_rel_equal", "REL_OP -> op_rel_equal"},
                 {"op_rel_not", "REL_OP -> op_rel_not"},
                 {"op_rel_double_equal", "REL_OP -> op_rel_double_equal"},
                 {"op_rel_minor_equal", "REL_OP -> op_rel_minor_equal"},
                 {"op_rel_bigger_equal", "REL_OP -> op_rel_bigger_equal"},
                 {"op_rel_not_equal", "REL_OP -> op_rel_not_equal"}}},

        {"LOGIC", {{"symbol_parameter_init", "LOGIC -> <EXPRESSION> <LOGIC_OP> <EXPRESSION>"},
                 {"id", "LOGIC -> <EXPRESSION> <LOGIC_OP> <EXPRESSION>"},	
                 {"double", "LOGIC -> <EXPRESSION> <LOGIC_OP> <EXPRESSION>"},
                 {"integer", "LOGIC -> <EXPRESSION> <LOGIC_OP> <EXPRESSION>"}}},

        {"LOGIC_OP", {{"op_log_e", "LOGIC_OP -> op_log_e"},
                 {"op_log_or", "LOGIC_OP -> op_log_or"}}},


        {"ATTRIBUTION", {{"typeInt", "ATTRIBUTION -> <RESERVED_TYPES> <ATTRIBUTION>'"},
                 {"typeDouble", "ATTRIBUTION -> <RESERVED_TYPES> <ATTRIBUTION>'"}}},

        {"ATTRIBUTION'", {{"id", "ATTRIBUTION' -> id <ATTRIBUTION''>"}}},

        {"ATTRIBUTION''", {{"op_rel_equal", "ATTRIBUTION'' -> op_rel_equal <EXPRESSION>"},
                 {"end_line", "ATTRIBUTION'' -> end_line"}}},

        {"ATRIBUTION_BOOL", {{"typeBoolean", "ATRIBUTION_BOOL -> typeBoolean id <ATRIBUTION_BOOL'>"}}},

        {"ATRIBUTION_BOOL'", {{"op_rel_equal", "ATRIBUTION_BOOL' -> op_rel_equal <ATTRIBUTION_BOOL''> "},
                              {"end_line", "ATRIBUTION_BOOL' -> endline"}}},


        {"ATRIBUTION_BOOL''", {{"bool_false", "ATRIBUTION_BOOL'' -> bool_false end_line"},
                               {"bool_true", "ATRIBUTION_BOOL'' -> bool_true end_line"}}},

        {"ATTRIBUTION_STR", {{"typeStr", "ATTRIBUTION_STR -> typeStr id <ATTRIBUTION_STR'>"}}},

        {"ATTRIBUTION_STR'", {{"op_rel_equal", "ATTRIBUTION_STR' -> op_rel_equal quotes all_except_quotes quotes end_line"},
                              {"end_line", "ATTRIBUTION_STR' -> end_line"}}},

        {"ATTRIBUTION_CHAR", {{"typeChar", "ATTRIBUTION_CHAR -> typeChar id <ATTRIBUTION_CHAR'>"}}},

        {"ATTRIBUTION_CHAR'", {{"op_rel_equal", "ATTRIBUTION_CHAR' -> op_rel_equal quotes char_regex quotes end_line"},
                              {"end_line", "ATTRIBUTION_CHAR' -> end_line"}}},  

        {"PRINT", {{"reserved_prt", "PRINT -> reserved_prt symbol_parameter_init <ID_OR_STRING> symbol_parameter_end end_line"}}},

        {"ID_OR_STRING", {{"id", "ID_OR_STRING -> id <ID_OR_STRING'>"},
                          {"double", "ID_OR_STRING -> double <ID_OR_STRING'>"},
                          {"integer", "ID_OR_STRING -> integer <ID_OR_STRING'>"},
                          {"quotes", "ID_OR_STRING -> quotes all_except_quotes quotes <ID_OR_STRING'>"}}},

        {"ID_OR_STRING'", {{"op_arit_sum", "ID_OR_STRING' -> op_arit_sum <ID_OR_STRING''> <ID_OR_STRING'>"},
                           {"ε", "ID_OR_STRING' -> ε"}}},   

        {"ID_OR_STRING''", {{"id", "ID_OR_STRING'' -> id"},
                            {"double", "ID_OR_STRING'' -> double"},
                            {"integer", "ID_OR_STRING'' -> integer"},
                            {"quotes", "ID_OR_STRING'' -> quotes all_except_quotes quotes"}}},


        {"SCAN", {{"reserved_scn", "SCAN -> reserved_scn symbol_parameter_init id symbol_parameter_end end_line"}}},

        {"LAPS", {{"laps", "LAPS -> laps symbol_parameter_init <INIT_LAPS> op_rel_equal <ID_OR_VALUE> symbol_op_mid id <REL_SYMBOLS> <ID_OR_VALUE> symbol_op_mid id op_rel_equal <LAPS_INC> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"}}},
        
        {"INIT_LAPS", {{"typeInt", "INIT_LAPS -> typeInt id"},
                       {"id", "INIT_LAPS -> id"}}},

        {"LAPS_INC", {{"id", "LAPS_INC -> id"},
                       {"brake", "LAPS_INC -> brake"},
                       {"overtake", "LAPS_INC -> overtake"}}},

        {"LAPS_SYMBOLS", {{"op_arit_sum", "LAPS_SYMBOLS -> op_arit_sum"},
                       {"op_arit_sub", "LAPS_SYMBOLS -> op_arit_sub"},
                       {"op_arit_mult", "LAPS_SYMBOLS -> op_arit_mult"},
                       {"op_arit_div", "LAPS_SYMBOLS -> op_arit_div"}}},

        {"INIT_LAPS", {{"id", "ID_OR_VALUE -> id"},
                       {"integer", "ID_OR_VALUE -> integer"}}},
         
        {"CIRCUIT", {{"circuit", "CIRCUIT -> circuit symbol_parameter_init <CIRCUIT_LOG> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"}}},

        {"CIRCUIT_LOG", {{"id", "CIRCUIT_LOG -> id <CIRCUIT_LOG'>"},
                         {"integer", "CIRCUIT_LOG -> integer <CIRCUIT_LOG'>"},
                         {"double", "CIRCUIT_LOG -> double <CIRCUIT_LOG'>"}}},

        {"CIRCUIT_LOG'", {{"op_arit_sum", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_sub", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_mult", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_div", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_pow", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_minor", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_bigger", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_equal", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_double_equal", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_minor_equal", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_bigger_equal", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_not_equal", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_and", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_or", "CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"$", "CIRCUIT_LOG' -> ε"}}},

        {"LOOPS_SYMBOLS", {{"op_arit_sum", "LOOPS_SYMBOLS -> <ARIT_SYMBOLS>"},
                           {"op_arit_sub", "LOOPS_SYMBOLS -> <ARIT_SYMBOLS>"},
                           {"op_arit_mult", "LOOPS_SYMBOLS -> <ARIT_SYMBOLS>"},
                           {"op_arit_div", "LOOPS_SYMBOLS -> <ARIT_SYMBOLS>"},
                           {"op_arit_pow", "LOOPS_SYMBOLS -> <ARIT_SYMBOLS>"},
                           {"op_rel_minor", "LOOPS_SYMBOLS -> <REL_SYMBOLS>"},
                           {"op_rel_bigger", "LOOPS_SYMBOLS -> <REL_SYMBOLS>"},
                           {"op_rel_equal", "LOOPS_SYMBOLS -> <REL_SYMBOLS>"},
                           {"op_rel_double_equal", "LOOPS_SYMBOLS -> <REL_SYMBOLS>"},
                           {"op_rel_minor_equal", "LOOPS_SYMBOLS -> <REL_SYMBOLS>"},
                           {"op_rel_bigger_equal", "LOOPS_SYMBOLS -> <REL_SYMBOLS>"},
                           {"op_rel_not_equal", "LOOPS_SYMBOLS -> <REL_SYMBOLS>"},
                           {"op_rel_and", "LOOPS_SYMBOLS -> <LOG_SYMBOLS>"}, //arit?
                           {"op_rel_or", "LOOPS_SYMBOLS -> <LOG_SYMBOLS>"}}},  //arit? na tabela ta arit

        {"ARIT_SYMBOLS", {{"op_arit_sum", "ARIT_SYMBOLS -> op_arit_sum"},
                           {"op_arit_sub", "ARIT_SYMBOLS -> op_arit_sub"},
                           {"op_arit_mult", "ARIT_SYMBOLS -> op_arit_mult"},
                           {"op_arit_div", "ARIT_SYMBOLS -> op_arit_div"},
                           {"op_arit_pow", "ARIT_SYMBOLS -> op_arit_pow"}}},

        {"REL_SYMBOLS", {{"op_rel_minor", "REL_SYMBOLS -> op_rel_minor"},
                         {"op_rel_bigger", "REL_SYMBOLS -> op_rel_bigger"},
                         {"op_rel_double_equal", "REL_SYMBOLS -> op_rel_double_equal"},
                         {"op_rel_minor_equal", "REL_SYMBOLS -> op_rel_minor_equal"},
                         {"op_rel_bigger_equal", "REL_SYMBOLS -> op_rel_bigger_equal"},
                         {"op_rel_not_equal", "REL_SYMBOLS -> op_rel_not_equal"}}},

        {"LOG_SYMBOLS", {{"op_log_e", "LOG_SYMBOLS -> op_log_e"},
                 {"op_log_or", "LOG_SYMBOLS -> op_log_or"}}},

        {"PIT", {{"pitEntry", "PIT -> pitEntry symbol_parameter_init <PIT_LOG> symbol_parameter_end symbol_block_init <CODE_BLOCK> symbol_block_end <PIT_EXIT>"}}},
        
        {"PIT_LOG", {{"id", "PIT_LOG -> id <PIT_LOG'>"},
                     {"integer", "PIT_LOG -> integer <PIT_LOG'>"},
                     {"double", "PIT_LOG -> double <PIT_LOG'>"}}},

        {"PIT_LOG'", {{"op_arit_sum", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_sub", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_mult", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_div", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_pow", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_minor", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_bigger", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_equal", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_double_equal", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_minor_equal", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_bigger_equal", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_not_equal", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_and", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_or", "PIT_LOG' -> <LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"$", "PIT_LOG' -> ε"}}},

        {"PIT_EXIT", {{"pitExit", "PIT_EXIT -> pitExit symbol_parameter_init <CODE_BLOCK> symbol_block_end"},
                       {"$", "PIT_EXIT -> ε"}}},


    };
    return grammarRules;
}