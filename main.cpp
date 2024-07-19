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

int main()
{
    ifstream arquivo("exemplo.txt");

    if (!arquivo)
    {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    char c;
    string token;
    int estado_atual = 1;
    int linha_atual = 1;
    int erro_linha = 1;
    string red_flag = "\U0001F6A9";

    while (true)
    { // Loop infinito para permanecer no switch
        if (!arquivo.get(c))
        {
            break; // Sai do loop se não conseguir ler o caractere
        }
        // if (regex_match(string(1,c), line_feed)) {
        //     linha_atual++;
        // }
        if (regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2))
        {
            linha_atual++;
        }
        int ascii_value = static_cast<int>(c);
        // if(ascii_value != 10) {
            // cout << "Caractere lido: " << c << " ASCII: " << ascii_value << endl;
        
        // } // 13 = \r
        
        //     cout << "estado atual" << estado_atual << endl << endl;
        switch (estado_atual)
        {

            case 1:
                if(regex_match(string(1, c), symbol_op_init) || regex_match(string(1, c), symbol_op_end)) {
                    estado_atual = 2;
                    token += c;
                } else if(regex_match(string(1, c), symbol_parameter_init) || regex_match(string(1, c), symbol_parameter_end) || regex_match(string(1, c), symbol_op_mid)) {
                    estado_atual = 3;
                    token += c;
                } else if(regex_match(string(1, c), op_arit_sum) || regex_match(string(1, c), op_arit_sub) || regex_match(string(1, c), op_arit_mult) || regex_match(string(1, c), op_arit_div) || regex_match(string(1, c), op_arit_pow)) {
                    estado_atual = 4;
                    token += c;
                } else if(regex_match(string(1, c), op_rel_minor) || regex_match(string(1, c), op_rel_bigger) || regex_match(string(1, c), op_rel_equal) || regex_match(string(1, c), op_rel_not)) {
                    estado_atual = 5;
                    token += c;
                } else if(regex_match(string(1, c), integer)) {
                    estado_atual = 6;
                    token += c;
                } else if(regex_match(string(1, c), char_regex)){
                    estado_atual = 11;
                    token += c;
                } else if(regex_match(string(1, c), spaces) || regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    estado_atual = 13;
                    token += c;
                } else if(regex_match(string(1, c), end_line)) {
                    estado_atual = 18;
                    token += c;
                } else {
                    
                    estado_atual = 14;
                    erro_linha = linha_atual;
                    token += c;

                }
                break;

            case 2:
                arquivo.putback(c); //{
                if (get_braces(token, lex)) {
                    estado_atual = 1;
                    token.clear();
                } else {
                    estado_atual = 14;

                }
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                break;

            case 3:
                arquivo.putback(c); //{
                if (get_parameters(token, lex)) {
                    estado_atual = 1;
                    token.clear();
                } else {
                    estado_atual = 14;

                }
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                break;

            case 4:
                arquivo.putback(c);
                if (get_arit(token, lex)) {
                    estado_atual = 1;
                    token.clear();
                } else {
                    estado_atual = 14;

                }
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                break;
            case 5:
                arquivo.putback(c);
                if (get_logic(token, lex)) {
                    estado_atual = 1;
                    token.clear();
                } else {

                    estado_atual = 14;
                }
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                break;
            case 6:
                if (regex_match(string(1, c), integer)) {
                    estado_atual = 6;
                    token += c;
                } else if(regex_match(string(1, c), comma)) {
                    estado_atual = 8;
                    token += c;
                } else {
                    estado_atual = 7;
                    arquivo.putback(c);
                    if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                } 
                break;
            case 7:
                arquivo.putback(c);
                if (get_integer(token, lex)) {
                    estado_atual = 1;
                    token.clear();
                } else {
                    estado_atual = 14;

                }
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                break;
            case 8:
                if(regex_match(string(1, c), integer)) {
                    estado_atual = 9;
                    token += c;
                } else {
                    estado_atual = 14;

                    
                }
                break;
            case 9:
                if (regex_match(string(1, c), integer)) {
                    estado_atual = 9;
                    token += c;
                } else {
                    estado_atual = 10;
                    arquivo.putback(c);
                    if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                } 
                break;

            case 10:
                arquivo.putback(c);
                if (get_double(token, lex)) {
                    estado_atual = 1;
                    token.clear();
                } else {
                    estado_atual = 14;

                }
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                break;
            case 11:
                if (regex_match(string(1, c), id)){
                    estado_atual = 11;
                    token += c;
                } else {
                    arquivo.putback(c);
                    estado_atual = 12;
                    if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                }
                break;
            
            case 12:
                arquivo.putback(c);

                if (get_token(token, lex)){

                        if (regex_match(token, reserved_comment)){
                            // cout << "fez o regex do token commnent" << endl;
                            estado_atual = 15;
                        } else {
                            estado_atual = 1;
                        }
                        token.clear();
                } else {
                    estado_atual = 14;

                }
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                break;

            case 13:
                arquivo.putback(c);
                if (regex_match(token, spaces) || regex_match(token, line_feed) || regex_match(token, line_feed2))
                {
                    estado_atual = 1;
                } else {
                    estado_atual = 14;
                    cout << "token invalido: " << token << endl;
                }
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                token.clear();
                break;
            case 14:
                arquivo.putback(c);
                cout << red_flag << " Erro na linha: " << erro_linha << " Caracter Inválido:  " << token << endl;
                token.clear();
                estado_atual = 1;
                // }
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                break;
            case 15:
                if(regex_match(string(1, c), symbol_op_init)){
                    estado_atual = 16;
                } else {
                    estado_atual = 14;

                    
                }
                break;

            case 16:
                if(regex_match(string(1, c), all_except_close_brace)){
                    estado_atual = 16;
                } else if (regex_match(string(1, c), symbol_op_end)){
                    estado_atual = 17;
                } else {
                    estado_atual = 14;

                }
                break;

            case 17:
                arquivo.putback(c);
                estado_atual = 1;
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                break;

            case 18:
                arquivo.putback(c);
                
                if(get_dot(token, lex)) {
                    estado_atual = 1;
                }
                else{
                    estado_atual = 14;
                }
                if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    linha_atual--;
                }
                token.clear();
                break;
        }
    }

       if (!token.empty())
    {
        switch (estado_atual)
        {
            case 2:
                if (!get_braces(token, lex))
                {
                    cout << "Erro na linha " << erro_linha << ": " << token << endl;
                }
                break;
            case 3:
                if (!get_parameters(token, lex))
                {
                    cout << "Erro na linha " << erro_linha << ": " << token << endl;
                }
                break;
            case 4:
                if (!get_arit(token, lex))
                {
                    cout << "Erro na linha " << erro_linha << ": " << token << endl;
                }
                break;
            case 5:
                if (!get_logic(token, lex))
                {
                    cout << "Erro na linha " << erro_linha << ": " << token << endl;
                }
                break;
            case 7:
                if (!get_integer(token, lex))
                {
                    cout << "Erro na linha " << erro_linha << ": " << token << endl;
                }
                break;
            case 10:
                if (!get_double(token, lex))
                {
                    cout << "Erro na linha " << erro_linha << ": " << token << endl;
                }
                break;
            case 12:
                if (!get_token(token, lex))
                {
                    cout << "Erro na linha " << erro_linha << ": " << token << endl;
                }
                break;
            case 13:
                if (!(regex_match(token, spaces) || regex_match(token, line_feed) || regex_match(token, line_feed2)))
                {
                    cout << "Erro na linha " << erro_linha << ": " << token << endl;
                }
                break;
        }
    }

    cout << "tamanho: " << lex.size() << endl;
    for (const auto &pair : lex)
    {
        int key = pair.first;
        string id = get<0>(pair.second);    // Acessa o primeiro elemento da tupla
        string token = get<1>(pair.second); // Acessa o segundo elemento da tupla
        cout << key << ": [" << id << ", '" << token << "']" << endl;
    }

    return 0;
}
