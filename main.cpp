#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include <tuple>
#include "regex_definitions.h"
#include "regex_functions.h"
using namespace std;

map<int, tuple<string, string>> lex;

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
        int ascii_value = static_cast<int>(c);
        cout << "Caractere lido: " << c << " ASCII: " << ascii_value << endl;
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
                    
                    if(get_integer(token, lex)) {
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
                    
                    if(get_double(token, lex)) {
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
                    if(get_token(token, lex)) {
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
                arquivo.putback(c); //{
                cout << "caso 14 " << token << endl;
                if(get_special_char(token, lex)) {
                    estado_atual = 1;   
                    token.clear();
                } else {
                    estado_atual = 2;
                }
                // if(regex_match(string(1, c), symbol_op_init) || regex_match(string(1, c), symbol_op_end) || regex_match(string(1, c), symbol_parameter_init) || regex_match(string(1, c), symbol_parameter_end) || regex_match(string(1, c), symbol_op_mid)) {
                //     estado_atual = 14;
                //     token += c;
                // } else {
                //     if(get_special_char(token, lex)) {
                //         estado_atual = 1;
                //         token.clear();
                //         arquivo.putback(c);
                //     } else {
                //         estado_atual = 2;
                //     }
                // }
                break;
            case 15:
                if (regex_match(string(1,c), op_rel_minor) || regex_match(string(1,c), op_rel_bigger) || regex_match(string(1,c), op_rel_equal) || regex_match(string(1,c), op_rel_mEqual) || regex_match(string(1,c), op_rel_bEqual) || regex_match(string(1,c), op_rel_notEqual)) {
                    estado_atual = 15;
                    token += c;
                } else {
                    if(get_op_rel(token, lex)) {
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
                    if(get_op_arit(token, lex)) {
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
