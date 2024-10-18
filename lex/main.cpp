#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include <tuple>
#include "regex_definitions.h"
#include "regex_functions.h"
using namespace std;
// g++ -o main main.cpp regex_definitionsv2.cpp regex_functionsv2.cpp
map<int, tuple<string, string, int>> lex;

int main()
{
    ifstream file("./cod_examples/exemploSprint.senna");

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
    int comment_line = 0;
    int string_line = 0;
    int previous_state = 0;
    string red_flag = "\U0001F6A9";
    string line;

    while (true)
    { 
        if (!file.get(c))
        {
            break; // Sai do loop se não conseguir ler o caractere
        }
        if (regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2))
        {
            current_line++;
        }
        int ascii_value = static_cast<int>(c);

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
                    current_state = 9;
                    token = token + c;
                    string_line = current_line;
                } else if (regex_match(string(1, c), reserved_comment)) {
                    comment_line = current_line;
                    current_state = 13;
                    token = token + c;
                } else if(regex_match(string(1, c), symbol_op_init)) {
                    current_state = 15;
                    token += c;
                } else if(regex_match(string(1, c), symbol_op_end)) {
                    current_state = 16;
                    token += c;
                } else if(regex_match(string(1, c), symbol_parameter_init)) {
                    current_state = 17;
                    token += c;
                } else if( regex_match(string(1, c), symbol_parameter_end)) {
                    current_state = 18;
                    token += c;
                } else if(regex_match(string(1, c), symbol_op_mid)) {
                    current_state = 19;
                    token += c;
                } else if(regex_match(string(1, c), end_line)) {
                    current_state = 20;
                    token += c;
                } else if(regex_match(string(1, c), op_rel_minor) || regex_match(string(1, c), op_rel_bigger) || regex_match(string(1, c), op_rel_not)) {
                    current_state = 21;
                    token += c;
                } else if(regex_match(string(1, c), spaces) || regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
                    current_state = 22;
                    token += c;
                } else if(regex_match(string(1, c), op_arit_sum) || regex_match(string(1, c), op_arit_sub) || regex_match(string(1, c), op_arit_mult) || regex_match(string(1, c), op_arit_div) || regex_match(string(1, c), op_arit_pow)) {
                    current_state = 23;
                    token += c;
                } else if (regex_match(string(1, c), single_op_log_e)) {
                    current_state = 24;
                    token = token + c;
                } else if (regex_match(string(1, c), single_op_log_or)) {
                    current_state = 25;
                    token = token + c;
                } else if(regex_match(string(1, c), op_rel_equal)) {
                    current_state = 31;
                    token = token + c;
                } else {
                    current_state = 26;
                    error_line = current_line;
                    token += c;
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
                        current_state = 1;
                        token.clear();
                } else {
                    current_state = 26;
                    previous_state = 3;
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
                    current_state = 26;
                    error_line = current_line;
                    previous_state = 6;
                }
                break;

            case 5:
                if(regex_match(string(1, c), integer)) {
                    current_state = 7;
                    token += c;
                } else {
                    current_state = 26;
                    error_line = current_line;
                    previous_state = 5;
                }
                break;

            case 7:
                if (regex_match(string(1, c), integer)) {
                    current_state = 7;
                    token += c;
                } else {
                    current_state = 8;
                    file.putback(c);
                    decrease_line(current_line, c);
                }
                break;

            case 8:
                file.putback(c);
                decrease_line(current_line, c);
                if (get_double(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                    previous_state = 8;
                }
                break;
            
            case 9:
                file.putback(c);
                decrease_line(current_line, c);
                string_line = current_line;
                if (regex_match(token, quotes)) {
                    current_state = 10;
                } else {
                    current_state = 12;
                    error_line = current_line;
                }
                break;

            case 10:
                decrease_line(current_line, c);
                if(regex_match(string(1, c), all_except_quotes)){
                    current_state = 10;
                    token += c;
                } else if (regex_match(string(1, c), quotes)){
                    current_state = 11;
                    file.putback(c);
                } else {
                    current_state = 26;
                    error_line = current_line;
                    previous_state = 10;
                }
                break;

            case 11:
                decrease_line(current_line, c);
                token += c;
                if(get_text_between_quotes(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                }  else {
                    current_state = 26;
                    error_line = current_line;
                    previous_state = 11;
                }
                break;
            case 12:
                file.putback(c);
                decrease_line(current_line, c);
                cout << red_flag << " Erro na linha: " << string_line << " Caracter Inválido:  " << token << endl;
                current_state = 1;
                token.clear();
                break;
            
            case 13:
                if(regex_match(string(1, c), all_except_at) || regex_match(string(1, c), portuguese)){
                    current_state = 13;
                } else if (regex_match(string(1, c), reserved_comment)){
                    current_state = 14;
                } else {
                    current_state = 26; 
                    error_line = current_line;
                    previous_state = 13;
                }
                break;
            
            case 14:
                file.putback(c);
                decrease_line(current_line, c);
                token.clear();
                current_state = 1;
                break;
            
            case 15:
                file.putback(c); 
                decrease_line(current_line, c);
                if (get_braces_init(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                }
                break;

            case 16:
                file.putback(c); 
                decrease_line(current_line, c);
                if (get_braces_end(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                }
                break;

            case 17:
                file.putback(c); 
                decrease_line(current_line, c);
                if (get_parameters_init(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                }
                break;

            case 18:
                file.putback(c); 
                decrease_line(current_line, c);
                if (get_parameters_end(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                }
                break;
            
            case 19:
                file.putback(c); 
                decrease_line(current_line, c);
                if (get_parameters_mid(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                }
                break;

            case 20:
                file.putback(c);
                decrease_line(current_line, c);
                if(get_dot(token, lex, current_line)) {
                    current_state = 1;
                }
                else{
                    current_state = 26;
                    error_line = current_line;
                }
                token.clear();
                break;

            case 21:
                if(regex_match(string(1, c), op_rel_equal)) {
                    current_state = 30;
                    token += c;
                }
                else {
                    file.putback(c);
                    decrease_line(current_line, c);
                    current_state = 29;
                }
                break;

            
                
            case 22:
                file.putback(c);
                decrease_line(current_line, c);
                if (regex_match(token, spaces) || regex_match(token, line_feed) || regex_match(token, line_feed2))
                {
                    current_state = 1;
                } else {
                    current_state = 26;
                    error_line = current_line;
                }
                token.clear();
                break;

            case 23:
                file.putback(c);
                decrease_line(current_line, c);
                if (get_arit(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                }
                break;

            case 24:
                if (regex_match(string(1, c), single_op_log_e)) {
                    current_state = 27;
                    token +=c;
                } else {
                    current_state = 26;
                    error_line = current_line;
                    previous_state = 24;
                }
                break;

            case 25:
                if (regex_match(string(1, c), single_op_log_or)) {
                    current_state = 28;
                    token +=c;
                } else {
                    current_state = 26;
                    error_line = current_line;
                    previous_state = 25;
                }
                break;

            case 26:
                file.putback(c);
                decrease_line(current_line, c);
                switch(previous_state) {
                    case 3:
                        cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                        break;
                    case 5:
                        cout << red_flag << " Erro na linha: " << error_line << " Esperava um número (0-9), porém encontrou " << token << endl;
                        break;
                    case 6:
                        cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                        break;
                    case 8:
                        cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                        break;
                    case 10:
                        break;
                        cout << red_flag << " Erro na linha: " << error_line << " Esperava \" ou caracter dentro do alfabeto da linguagem, porém encontrou:  " << token << endl;
                    case 11:
                        cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                        break;
                    case 13:
                        cout << red_flag << " Erro na linha: " << error_line << " Esperava \"@\" ou caracter dentro do alfabeto da linguagem, porém encontrou:  " << token << endl;
                        break;
                    case 24:
                        cout << red_flag << " Erro na linha: " << error_line << " Esperava \"&\", porém encontrou: " << c << endl;
                        break;
                    case 25:
                        cout << red_flag << " Erro na linha: " << error_line << " Esperava \"|\", porém encontrou: " << token << endl;
                        break;
                    case 29:
                        cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                        break;
                    default:
                        cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                        break;

                }
                current_state = 1;
                token.clear();
                previous_state = 0;
                break;

            case 27:
                file.putback(c);
                decrease_line(current_line, c);
                if (get_log_e(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                }
                break;
            case 28:
                file.putback(c);
                decrease_line(current_line, c);
                if (get_log_or(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                }
                break;
            case 29:
                file.putback(c);
                decrease_line(current_line, c);
                // cout << "token: " << token << endl;
                if (get_single_symbol(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                    previous_state = 29;
                }
                break;          

            case 30:
                file.putback(c);
                decrease_line(current_line, c);
                if (get_double_symbol(token, lex, current_line)) {
                    current_state = 1;
                    token.clear();
                } else {
                    current_state = 26;
                    error_line = current_line;
                }
                break;
            case 31:
                if(regex_match(string(1, c), op_rel_equal)) {
                    current_state = 30;
                    token += c;
                }
                else {
                    file.putback(c);
                    decrease_line(current_line, c);
                    current_state = 29;
                }
                break;
                
        }   
    }

       if (!token.empty())
    {
        // error_line = current_line;
        switch (current_state)
        {
            case 3:
                if(!get_token(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;

                }
                break;

            case 6: 
                if(!get_integer(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;

                }
                break;
            case 8:
                if(!get_double(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;

                }
                break;
            case 9:
                if(!(get_text_between_quotes(token, lex, current_line))) {
                    cout << red_flag << " Erro na linha: " << string_line << " Faltou fechar o comentário com o caracter \"  " << endl;
                } else  {
                    cout << red_flag << " Erro na linha: " << string_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 10:
                if(!(get_text_between_quotes(token, lex, current_line))) {
                    cout << red_flag << " Erro na linha: " << string_line << " Faltou fechar o comentário com o caracter \"  " << endl;
                } else  {
                    cout << red_flag << " Erro na linha: " << string_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 11:
                if(!(get_text_between_quotes(token, lex, current_line))) {
                    cout << red_flag << " Erro na linha: " << string_line << " Faltou fechar o comentário com o caracter \"  " << endl;
                } else  {
                    cout << red_flag << " Erro na linha: " << string_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 13:
                if(!(regex_match(token, at_regex))) {
                    cout << red_flag << " Erro na linha: " << comment_line << " Faltou fechar o comentário com o caracter @:  " << endl;
                } else  {
                    cout << red_flag << " Erro na linha: " << comment_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 15:
                if(!get_braces_init(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 16:
                if(!get_braces_end(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 17:
                if(!get_parameters_init(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 18:
                if(!get_parameters_end(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 19:
                if(!get_parameters_mid(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 20:
                if(!get_dot(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 21:
                if(!get_single_symbol(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 23:
                if(!get_arit(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 24:
                if(!get_log_e(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 25:
                if(!get_log_or(token, lex, current_line)) {
                    cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;
                }
                break;
            case 26:    
                cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;

            // default:
            //     cout << red_flag << " Erro na linha: " << error_line << " Caracter Inválido:  " << token << endl;

        }
    }

    // for (const auto &pair : lex)
    // {
    //     int key = pair.first;
    //     string id = get<0>(pair.second); 
    //     string token = get<1>(pair.second); 
    //     int line = get<2>(pair.second);
    //     cout << key << ": [" << id << ", '" << token << "', '" << line << "']" << endl;
    // }
    ofstream outputFile("outputLex.txt");
    if (!outputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    // Itera sobre o mapa e grava no arquivo
    for (const auto &pair : lex) {
        int key = pair.first;
        string id = get<0>(pair.second); 
        string token = get<1>(pair.second); 
        int line = get<2>(pair.second);
        outputFile << key << ": [" << id << ", '" << token << "', '" << line << "']" << endl;
    }

    // Fecha o arquivo
    outputFile.close();
    cout << "Conteúdo salvo em 'output.txt'" << endl;
    return 0;
}
