#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include <tuple>
#include "regex_definitions.h"
#include "regex_functions.h"
using namespace std;

map<int, tuple<string, string, int>> lex;

int main()
{
    ifstream file("exemploSprint.senna");

    if (!file)
    {
        cerr << "Erro ao abrir o file!" << endl;
        return 1;
    }

    char c;
    string token;
    int current_state = 1;
    int current_line = 1;
    int error_line = 1;
    string red_flag = "\U0001F6A9";
    string line;

    while (true)
    { // Loop infinito para permanecer no switch
        if (!file.get(c))
        {
            break; // Sai do loop se não conseguir ler o caractere
        }
        // if (regex_match(string(1,c), line_feed)) {
        //     current_line++;
        // }
        if (regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2))
        {
            current_line++;
        }
        int ascii_value = static_cast<int>(c);
        // if(ascii_value != 10) {
            // cout << "Caractere lido: " << c << " ASCII: " << ascii_value << endl;

        // } // 13 = \r

        //     cout << "estado atual" << current_state << endl << endl;
        switch (current_state)
        {

            case 1:
                if(regex_match(string(1, c), char_regex)){
                    current_state = 2;
                    token += c;
                }  else if(regex_match(string(1, c), integer)) {
                    current_state = 4;
                    token += c;
                } else if (regex_match(string(1, c), quotes)) {
                    current_state = 7;
                    token = token + c;
                } else if (regex_match(string(1, c), reserved_comment)) {
                    current_state = 11;
                    token = token + c;
                } else if(regex_match(string(1, c), symbol_op_init)) {
                    current_state = 14;
                    token += c;
                } else if(regex_match(string(1, c), symbol_op_end)) {
                    current_state = 15;
                    token += c;
                }else if(regex_match(string(1, c), symbol_parameter_init)) {
                    current_state = 16;
                    token += c;
                }else if( regex_match(string(1, c), symbol_parameter_end)) {
                    current_state = 17;
                    token += c;
                }else if(regex_match(string(1, c), symbol_op_mid)) {
                    current_state = 18;
                    token += c;
                } else if(regex_match(string(1, c), end_line)) {
                    current_state = 19;
                    token += c;
                } else if(regex_match(string(1, c), op_rel_minor) || regex_match(string(1, c), op_rel_bigger) || regex_match(string(1, c), op_rel_equal) || regex_match(string(1, c), op_rel_not)) {
                    current_state = 20;
                    token += c;
                }  else if(regex_match(string(1, c), spaces) || regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    current_state = 21;
                    token += c;
                } else if(regex_match(string(1, c), op_arit_sum) || regex_match(string(1, c), op_arit_sub) || regex_match(string(1, c), op_arit_mult) || regex_match(string(1, c), op_arit_div) || regex_match(string(1, c), op_arit_pow)) {
                    current_state = 22;
                    token += c;
                }  else if (regex_match(string(1, c), op_log_e)) {
                    current_state = 23;
                    token = token + c;
                }else if (regex_match(string(1, c), op_log_or)) {
                    current_state = 24;
                    token = token + c;
                }else {
                    
                    current_state = 25;
                    error_line = current_line;
                    token += c;

                }
                break;

            case 14:
                file.putback(c); //{
                decrease_line(current_line, c);
                
                if (get_braces_init(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }
                break;

            case 15:
                file.putback(c); //{
                decrease_line(current_line, c);
                if (get_parameters_init(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }
                
                break;

            case 21:
                file.putback(c);
                decrease_line(current_line, c);
                if (get_arit(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }

                break;
            case 19:
                file.putback(c);
                decrease_line(current_line, c);
                if (get_logic(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {

                    current_state = 24;
                    error_line = current_line;
                }

                break;
            case 4:
                if (regex_match(string(1, c), integer)) {
                    current_state = 4;
                    token += c;
                } else if(regex_match(string(1, c), comma)) {
                    current_state = 5;
                    token += c;
                } else {
                    current_state = 6;
                    file.putback(c);
                    decrease_line(current_line, c);
                }
                break;
            case 6:
                file.putback(c);
                decrease_line(current_line, c);
                if (get_integer(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }

                break;
            case 5:
                if(regex_match(string(1, c), integer)) {
                    current_state = 9;
                    token += c;
                } else {
                    current_state = 24;
                    error_line = current_line;


                }
                break;
            case 9:
                if (regex_match(string(1, c), integer)) {
                    current_state = 9;
                    token += c;
                } else {
                    current_state = 10;
                    file.putback(c);
                    decrease_line(current_line, c);
                }
                break;

            case 10:
                file.putback(c);
                decrease_line(current_line, c);
                if (get_double(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }

                break;
            case 2:
                if (regex_match(string(1, c), id) || regex_match(string(1, c), symbol_id)){
                    current_state = 2;
                    token += c;
                } else {
                    file.putback(c);
                    current_state = 3;
                    decrease_line(current_line, c);
                }
                break;

            case 3:
                file.putback(c);
                decrease_line(current_line, c);
                if (get_token(token, lex, current_line)){

                        // if (regex_match(token, reserved_comment)){
                        //     // cout << "fez o regex do token commnent" << endl;
                        //     current_state = 15;
                        // } else {
                        //     current_state = 1;
                        // }
                        current_state = 1;
                        token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }

                break;

            case 20:
                file.putback(c);
                decrease_line(current_line, c);
                if (regex_match(token, spaces) || regex_match(token, line_feed) || regex_match(token, line_feed2))
                {
                    current_state = 1;
                } else {
                    current_state = 24;
                    error_line = current_line;
                    cout << "token invalido: " << token << endl;
                }

                token.clear();
                break;
            case 24:
                file.putback(c);
                decrease_line(current_line, c);
                cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                current_state = 1;
                // int lastIndex;
                //  if (!lex.empty())
                // {
                //     auto last = lex.rbegin(); // rbegin() aponta para o último elemento
                //     lastIndex = last->first;
                //     lastIndex++;
                // }
                // else
                // {
                //     lastIndex = 0;
                // }

                // line = "Linha Erro: " + to_string(error_line);
                // lex[lastIndex] = make_tuple(line, token);
                
                // }

                token.clear();
                break;
            // case 15:
            //     if(regex_match(string(1, c), symbol_op_init)){
            //         current_state = 16;
            //     } else {
            //         current_state = 24;
            //         error_line = current_line;


            //     }
            //     break;

            // case 16:
            //     if(regex_match(string(1, c), all_except_close_brace)){
            //         current_state = 16;
            //     } else if (regex_match(string(1, c), symbol_op_end)){
            //         current_state = 17;
            //     } else {
            //         current_state = 24;
            //         error_line = current_line;

            //     }
            //     break;

            // case 17:
            //     file.putback(c);
            //     decrease_line(current_line, c);
            //     current_state = 1;

            //     break;

            case 18:
                file.putback(c);
                decrease_line(current_line, c);
                if(get_dot(token, lex, current_line)) {
                    current_state = 1;
                }
                else{
                    current_state = 24;
                    error_line = current_line;
                }

                token.clear();
                break;
            
            case 7:
                 file.putback(c); //{
                decrease_line(current_line, c);
                
                if (get_quotes(token, lex, current_line)) {
                    current_state = 8;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }
                break;
            case 8:
                // file.putback(c); //{
                decrease_line(current_line, c);
                if(regex_match(string(1, c), all_except_quotes)){
                    current_state = 8;
                    token += c;
                } else if (regex_match(string(1, c), quotes)){
                    // cout << "quotes" << endl;
                    current_state = 9;
                    if(get_text_between_quotes(token, lex, current_line)) {
                        // cout << "get_text_between_quotes"  << endl;
                    }
                    token.clear();
                    file.putback(c);
                } else {
                    current_state = 24;
                    error_line = current_line;

                }
                break;
            // case 9:
            //     // file.putback(c); //{
            //     decrease_line(current_line, c);
            //     token = c;
            //     if (get_quotes(token, lex, current_line)) {
            //         current_state = 1;
            //         token.clear();
            //     }  else {
            //         current_state = 24;
            //         error_line = current_line;

            //     }
            //     break;

            case 22:
                file.putback(c); //{
                decrease_line(current_line, c);
                
                if (get_log_e(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }
                break;
            case 23:
                file.putback(c); //{
                decrease_line(current_line, c);
                
                if (get_log_or(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }
                break;
            case 11:
                file.putback(c); //{
                decrease_line(current_line, c);
                
                if (regex_match(token, reserved_comment)) {
                    current_state = 11;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }
                break;
                // if(regex_match(string(1, c), symbol_op_init)){
                //     current_state = 16;
                // } else {
                //     current_state = 14;
                //     error_line = current_line;


                // }
                // break;
                // file.putback(c); //{
            case 12:
                if(regex_match(string(1, c), all_except_at) || regex_match(string(1, c), portuguese)){
                    current_state = 11;
                } else if (regex_match(string(1, c), reserved_comment)){
                    current_state = 12;
                } else {
                    current_state = 14; 
                    error_line = current_line;

                }
                break;
            case 13:
                file.putback(c);
                decrease_line(current_line, c);
                current_state = 1;

                break;
            case 15:
                file.putback(c); //{
                decrease_line(current_line, c);
                
                if (get_braces_end(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }
                break;
            case 16:
                file.putback(c); //{
                decrease_line(current_line, c);
                if (get_parameters_end(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }
                
                break;
            case 17:
                file.putback(c); //{
                decrease_line(current_line, c);
                if (get_parameters_mid(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 24;
                    error_line = current_line;

                }
                
                break;
        }   

        //     case 20:
        //         file.putback(c);
        //         if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
        //             current_line--;
        //         }
        //         if (get_quotes(token, lex, current_line)) {
        //             current_state = 21;
        //             token.clear();
        //         } else {
        //             current_state = 14;
        // error_line = current_line;
        // }
    }

       if (!token.empty())
    {
        switch (current_state)
        {
            case 2:
                if (!get_braces_init(token, lex, current_line))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 3:
                if (!get_parameters_init(token, lex, current_line))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 4:
                if (!get_arit(token, lex, current_line))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 5:
                if (!get_logic(token, lex, current_line))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 7:
                if (!get_integer(token, lex, current_line))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 10:
                if (!get_double(token, lex, current_line))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 12:
                if (!get_token(token, lex, current_line))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 13:
                if (!(regex_match(token, spaces) || regex_match(token, line_feed) || regex_match(token, line_feed2)))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 24:
                // fazer o case 14 nao está identificando o erro
                if(regex_match(string(1, c), restricted_symbols )|| regex_match(string(1, c), restricted_symbols)) {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;

            case 18:
                if (!get_dot(token, lex, current_line))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 19:
                if (!get_quotes(token, lex, current_line))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 22:
                if (!get_log_e(token, lex, current_line))
                {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 23:
                if (!get_log_or(token, lex, current_line)) {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 27:
                if (!get_braces_end(token, lex, current_line)) {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 28:
                if (!get_parameters_end(token, lex, current_line)) {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
            case 29:
                if (!get_parameters_mid(token, lex, current_line)) {
                    cout << "Erro na linha " << error_line << ": " << token << endl;
                }
                break;
                
        }
    }

    for (const auto &pair : lex)
    {
        int key = pair.first;
        string id = get<0>(pair.second);    // Acessa o primeiro elemento da tupla
        string token = get<1>(pair.second); // Acessa o segundo elemento da tupla
        int line = get<2>(pair.second);
        cout << key << ": [" << id << ", '" << token << "', '" << line << "']" << endl;
    }

    return 0;
}
