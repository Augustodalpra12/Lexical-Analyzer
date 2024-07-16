#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include <tuple>

using namespace std;

map<int, tuple<string, string>> lex;

regex integer("[0-9]+");
regex integer_signal("(\\+|-)?[0-9]+");
regex double_regex("(\\+|-)?[0-9]+(\\.[0-9]+)?(E(\\+|-)?[0-9]+)?");
regex char_regex("[a-zA-Z]");
regex digit("[0-9]");

regex symbol_id("[_]");
regex symbol_parameter_init("[(]");
regex symbol_parameter_end("[)]");

regex symbol_op_init("[{]");
regex symbol_op_end("[}]");
regex symbol_op_mid("[;]");

regex id("[a-zA-Z]([a-zA-Z0-9]|[_])*");
regex comma(",");

regex reserved_loops("(laps|circuit)");
regex reserved_condition("(pitEntry|pitExit)");
regex reserved_arit("(overtake|brake)");
regex reserved_main("(race)");
regex reserved_comment("(Radio)");
regex reserved_types("(int|double|char|boolean|str)");
regex reserved_prt("(prt)");
regex reserved_scn("(scn)");  


regex op_log_and("&&");
regex op_log_or("\\|\\|");  // Dupla contrabarra para escapar o pipe "|"
regex op_log_not("!");

regex end_line("\\.");

regex op_arit_sum("\\+");
regex op_arit_sub("-");
regex op_arit_mult("\\*");
regex op_arit_div("/");
regex op_arit_pow("\\^");

regex op_rel_minor("<");
regex op_rel_bigger(">");
regex op_rel_equal("=");
regex op_rel_mEqual("≤");
regex op_rel_bEqual("≥");
regex op_rel_notEqual("≠");

regex spaces("[\\s\t\n]+");
// regex space(" ");
// regex space("\\s"); // espaço n ta funcionando
regex all_symbols(".");
regex comment("Radio[{][.\\s\t\n]*[}]");


bool get_op_arit(string token) {
    int lastIndex;
    if (!lex.empty()) {
        auto last = lex.rbegin(); // rbegin() aponta para o último elemento
        lastIndex = last->first;
        lastIndex++;

    } else {
        lastIndex = 0;
    }
    if (regex_match(token, op_arit_sum)) {
        lex[lastIndex] = make_tuple("op_arit_sum", token);
        return true;
    } else if(regex_match(token, op_arit_sub)) {
        lex[lastIndex] = make_tuple("op_arit_sub", token);
        return true;
    } else if(regex_match(token, op_arit_mult)) {
        lex[lastIndex] = make_tuple("op_arit_mult", token);
        return true;
    } else if(regex_match(token, op_arit_div)) {
        lex[lastIndex] = make_tuple("op_arit_div", token);
        return true;
    } else if(regex_match(token, op_arit_pow)) {
        lex[lastIndex] = make_tuple("op_arit_pow", token);
        return true;
    }
    return false;
}

bool get_op_rel(string token) {
    int lastIndex;
    if (!lex.empty()) {
        auto last = lex.rbegin(); // rbegin() aponta para o último elemento
        lastIndex = last->first;
        lastIndex++;

    } else {
        lastIndex = 0;
    }
    if (regex_match(token, op_rel_minor)) {
        lex[lastIndex] = make_tuple("op_rel_minor", token);
        return true;
    } else if(regex_match(token, op_rel_bigger)) {
        lex[lastIndex] = make_tuple("op_rel_bigger", token);
        return true;
    } else if(regex_match(token, op_rel_equal)) {
        lex[lastIndex] = make_tuple("op_rel_equal", token);
        return true;
    } else if(regex_match(token, op_rel_mEqual)) {
        lex[lastIndex] = make_tuple("op_rel_mEqual", token);
        return true;
    } else if(regex_match(token, op_rel_bEqual)) {
        lex[lastIndex] = make_tuple("op_rel_bEqual", token);
        return true;
    } else if(regex_match(token, op_rel_notEqual)) {
        lex[lastIndex] = make_tuple("op_rel_notEqual", token);
        return true;
    }
    return false;
}

bool get_special_char(string token) {
    int lastIndex;
    if (!lex.empty()) {
        auto last = lex.rbegin(); // rbegin() aponta para o último elemento
        lastIndex = last->first;
        lastIndex++;

    } else {
        lastIndex = 0;
    }
    if (regex_match(token, symbol_op_init)) {
        lex[lastIndex] = make_tuple("symbol_op_init", token);
        return true;
    } else if(regex_match(token, symbol_op_end)) {
        lex[lastIndex] = make_tuple("symbol_op_end", token);
        return true;
    } else if(regex_match(token, symbol_parameter_init)) {
        lex[lastIndex] = make_tuple("symbol_parameter_init", token);
        return true;   
    } else if(regex_match(token, symbol_parameter_end)) {
        lex[lastIndex] = make_tuple("symbol_parameter_end", token);
        return true;
    } else if(regex_match(token, symbol_op_mid)) {
        lex[lastIndex] = make_tuple("symbol_op_mid", token);
        return true;
    }
    return false;
}
bool get_token(string token){
    int lastIndex;
    if (!lex.empty()) {
        auto last = lex.rbegin(); // rbegin() aponta para o último elemento
        lastIndex = last->first;
        lastIndex++;

    } else {
        lastIndex = 0;
    }
    if(regex_match(token, reserved_loops)) {
        lex[lastIndex] = make_tuple("reserved_loops", token);
        return true;
    } else if (regex_match(token, reserved_condition)) {
        lex[lastIndex] = make_tuple("reserved_condition", token);
        return true;
    } else if (regex_match(token, reserved_arit)) {
        lex[lastIndex] = make_tuple("reserved_arit", token);
        return true;
    } else if (regex_match(token, reserved_main)) {
        lex[lastIndex] = make_tuple("reserved_main", token);
        return true;
    } else if (regex_match(token, reserved_comment)) {
        lex[lastIndex] = make_tuple("reserved_comment", token);
        
        return true;
    } else if (regex_match(token, reserved_types)) {
        lex[lastIndex] = make_tuple("reserved_types", token);
        
        return true;
    } else if(regex_match(token, reserved_prt)){
        lex[lastIndex] = make_tuple("reserved_prt", token);
        return true;
    } else if(regex_match(token, reserved_scn)){
        lex[lastIndex] = make_tuple("reserved_scn", token);
        return true;
    } else if (regex_match(token, id)) {
        lex[lastIndex] = make_tuple("id", token);
        return true;
        // cout << "Token encontrado: " << token << endl;
        return true;
    } 
    return false;   
}

bool get_integer(string token){
    int lastIndex;
    if (!lex.empty()) {
        auto last = lex.rbegin(); // rbegin() aponta para o último elemento
        lastIndex = last->first;
        lastIndex++;

    } else {
        lastIndex = 0;
    }
    if(regex_match(token, integer_signal)) {
        lex[lastIndex] = make_tuple("integer_signal", token);
        return true;
    } else if (regex_match(token, integer)) {
        lex[lastIndex] = make_tuple("integer", token);
        return true;
    }
    return false;
}

bool get_double(string token){
    int lastIndex;
    if (!lex.empty()) {
        auto last = lex.rbegin(); // rbegin() aponta para o último elemento
        lastIndex = last->first;
        lastIndex++;
    } else {
        lastIndex = 0;
    }
    if(regex_match(token, double_regex)) {
        lex[lastIndex] = make_tuple("double", token);
        return true;
    }
    return false;
}

int main(){
    ifstream arquivo("exemplo.txt");

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    char c;
    string token;
    int estado_atual = 1;

    while (true) {  // Loop infinito para permanecer no switch
        if (!arquivo.get(c)) {
            break;  // Sai do loop se não conseguir ler o caractere
        }
        // cout << "Caractere lido: " << c << endl;
        
        switch (estado_atual) {
            case 1:
                if(regex_match(string(1, c), op_arit_sum)) {
                    estado_atual = 3;
                    token += c;
                } else if(regex_match(string(1, c), op_arit_sub)) {
                    estado_atual = 4;
                    token += c;
                } else if(regex_match(string(1, c), integer)) {
                    estado_atual = 5;
                    token += c;
                } else if(regex_match(string(1, c), char_regex)) {
                    estado_atual = 10;
                    token += c;
                } else if(regex_match(string(1, c), symbol_op_init)) {
                    estado_atual = 12;
                    token += c;
                } else if(regex_match(string(1, c), spaces)) {
                    // cout << "Espaco: token ->" << token << endl;
                    estado_atual = 1;
                } else if(regex_match(string(1, c), end_line)) {
                    estado_atual = 1;
                } else if (regex_match(string(1, c), symbol_op_init) || regex_match(string(1, c), symbol_op_end) || regex_match(string(1, c), symbol_parameter_init) || regex_match(string(1, c), symbol_parameter_end) || regex_match(string(1, c), symbol_op_mid)) {
                    estado_atual = 14;
                    token += c;

                } else if (regex_match(string(1,c), op_rel_minor) || regex_match(string(1,c), op_rel_bigger) || regex_match(string(1,c), op_rel_equal) || regex_match(string(1,c), op_rel_mEqual) || regex_match(string(1,c), op_rel_bEqual) || regex_match(string(1,c), op_rel_notEqual)) {
                    estado_atual = 15;
                    token += c;

                } else if(regex_match(string(1, c), op_arit_sum) || regex_match(string(1, c), op_arit_sub) || regex_match(string(1, c), op_arit_mult) || regex_match(string(1, c), op_arit_div) || regex_match(string(1, c), op_arit_pow)) {
                    estado_atual = 16;
                    token += c;  
                } else {
                    estado_atual = 2;
                    token += c;
                }
                break;
            case 2:
                // if(regex_match(string(1, c), end_line)) {
                //     estado_atual = 1;
                //     token.clear();
                // } else {
                cout << "Erro:" << token << endl;
                token.clear();
                estado_atual = 1;
                // }
                break;
            case 3:
                if(regex_match(string(1, c), integer)) {
                    estado_atual = 5;
                    token += c;
                } else {
                    estado_atual = 2;
                    token += c;
                }
                break;
            case 4:
                if(regex_match(string(1, c), integer)) {
                    estado_atual = 5;
                    token += c;
                } else {
                    estado_atual = 2;
                    token += c;
                }
                break;
            case 5:
                if(regex_match(string(1, c), integer)) {
                    estado_atual = 5;
                    token += c;
                } else if (regex_match(string(1, c), comma)) {
                    estado_atual = 7;
                    token += c;
                } else {
                    
                    if(get_integer(token)) {
                        estado_atual = 1;
                        token.clear();
                        arquivo.putback(c);
                    } else {
                        estado_atual = 2;
                    }
                }
                break;
            case 7:
                if(regex_match(string(1, c), integer)) {
                    estado_atual = 8;
                    token += c;
                } else {
                    estado_atual = 2;
                    token += c;
                }
                break;
            case 8:
                if(regex_match(string(1, c), integer)) {
                    estado_atual = 8;
                    token += c;
                } else {
                    
                    if(get_double(token)) {
                        estado_atual = 1;
                        token.clear();
                        arquivo.putback(c);
                    } else {
                        estado_atual = 2;
                    }
                }
                break;
            case 10:
                if(regex_match(string(1, c), id)) {
                    estado_atual = 10;
                    token += c;
                } else {
                    if(get_token(token)) {
                        estado_atual = 1;
                        token.clear();
                        arquivo.putback(c);
                    } else {
                        estado_atual = 2;
                    }
                }
                break;
            case 12:
                if(regex_match(string(1, c), all_symbols)) {
                    estado_atual = 12;
                    token += c;
                } else if (regex_match(string(1, c), symbol_op_end)) {
                    estado_atual = 13;
                    token += c;
                } else {
                    estado_atual = 2;
                    token += c;
                }
                break;
            case 13:
                // final do comentario
                token.clear();
                estado_atual = 1;
                break;
            case 14:
                if(regex_match(string(1, c), symbol_op_init) || regex_match(string(1, c), symbol_op_end) || regex_match(string(1, c), symbol_parameter_init) || regex_match(string(1, c), symbol_parameter_end) || regex_match(string(1, c), symbol_op_mid)) {
                    estado_atual = 10;
                    token += c;
                } else {
                    if(get_special_char(token)) {
                        estado_atual = 1;
                        token.clear();
                        arquivo.putback(c);
                    } else {
                        estado_atual = 2;
                    }
                }
                break;
            case 15:
                if (regex_match(string(1,c), op_rel_minor) || regex_match(string(1,c), op_rel_bigger) || regex_match(string(1,c), op_rel_equal) || regex_match(string(1,c), op_rel_mEqual) || regex_match(string(1,c), op_rel_bEqual) || regex_match(string(1,c), op_rel_notEqual)) {
                    estado_atual = 15;
                    token += c;
                } else {
                    if(get_op_rel(token)) {
                        estado_atual = 1;
                        token.clear();
                        arquivo.putback(c);
                    } else {
                        estado_atual = 2;
                    }
                }
                break;
            case 16:
                if(regex_match(string(1, c), op_arit_sum) || regex_match(string(1, c), op_arit_sub) || regex_match(string(1, c), op_arit_mult) || regex_match(string(1, c), op_arit_div) || regex_match(string(1, c), op_arit_pow)) {
                    estado_atual = 16;
                    token += c;  
                } else {
                    if(get_op_arit(token)) {
                        estado_atual = 1;
                        token.clear();
                        arquivo.putback(c);
                    } else {
                        estado_atual = 2;
                    }
                }
                break;
        }
    }

    // for (const auto& pair : lex) {
    //     // cout << "frio ne" << endl;
    //     // cout << pair.first << ": " << pair.second << endl;
    // }
    cout << "tamanho: " << lex.size() << endl;
    for (const auto& pair : lex) {
        int key = pair.first;
        string id = get<0>(pair.second);   // Acessa o primeiro elemento da tupla
        string token = get<1>(pair.second); // Acessa o segundo elemento da tupla
        cout << key << ": [" << id << ", '" << token << "']" << endl;
    }

    return 0;
}
