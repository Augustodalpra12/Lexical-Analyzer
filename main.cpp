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

    while (true)
    { // Loop infinito para permanecer no switch
        if (!arquivo.get(c))
        {
            break; // Sai do loop se não conseguir ler o caractere
        }
        // if (regex_match(string(1,c), line_feed)) {
        //     linha_atual++;
        // }
        if (c == '\n')
        {
            linha_atual++;
        }
        int ascii_value = static_cast<int>(c);
        // cout << "Caractere lido: " << c << " ASCII: " << ascii_value << endl;
        //     cout << "estado atual" << estado_atual << endl << endl;
        switch (estado_atual)
        {
        case 1:
            if (regex_match(string(1, c), op_arit_sum))
            {
                estado_atual = 3;
                token += c;
            }
            else if (regex_match(string(1, c), op_arit_sub))
            {
                estado_atual = 4;
                token += c;
            }
            else if (regex_match(string(1, c), integer))
            {
                estado_atual = 5;
                token += c;
            }
            else if (regex_match(string(1, c), char_regex))
            {
                estado_atual = 10;
                token += c;
            }
            else if (regex_match(string(1, c), spaces))
            {
                // cout << "Espaco: token ->" << token << endl;
                estado_atual = 1;
            }
            else if (regex_match(string(1, c), end_line))
            {
                // cout << "ta finando no ponto" << endl;
                estado_atual = 1;
            }
            else if (regex_match(string(1, c), symbol_op_init))
            {
                // cout << "entrou no if do {}" << c << endl;
                estado_atual = 30;
                token += c;
            }
            else if (regex_match(string(1, c), symbol_op_end))
            {
                estado_atual = 31;
                token += c;
            }
            else if (regex_match(string(1, c), symbol_parameter_init))
            {
                estado_atual = 32;
                token += c;
            }
            else if (regex_match(string(1, c), symbol_parameter_end))
            {
                estado_atual = 33;
                token += c;
            }
            else if (regex_match(string(1, c), symbol_op_mid))
            {
                estado_atual = 34;
                token += c;
            }
            else if (regex_match(string(1, c), op_rel_minor) || regex_match(string(1, c), op_rel_bigger) || regex_match(string(1, c), op_rel_equal) || regex_match(string(1, c), op_rel_mEqual) || regex_match(string(1, c), op_rel_bEqual) || regex_match(string(1, c), op_rel_notEqual))
            {
                estado_atual = 15;
                token += c;
            }
            else if (regex_match(string(1, c), op_arit_sum) || regex_match(string(1, c), op_arit_sub) || regex_match(string(1, c), op_arit_mult) || regex_match(string(1, c), op_arit_div) || regex_match(string(1, c), op_arit_pow))
            {
                estado_atual = 16;
                token += c;
            }
            else
            {
                estado_atual = 2;
                token += c;
                erro_linha = linha_atual;
            }
            break;
        case 2:
            // if(regex_match(string(1, c), end_line)) {
            //     estado_atual = 1;
            //     token.clear();
            // } else {
            cout << "Erro na linha " << erro_linha << ": " << token << endl;
            token.clear();
            estado_atual = 1;
            // }
            break;
        case 3:
            if (regex_match(string(1, c), integer))
            {
                estado_atual = 5;
                token += c;
            }
            else
            {
                estado_atual = 2;
                token += c;
            }
            break;
        case 4:
            if (regex_match(string(1, c), integer))
            {
                estado_atual = 5;
                token += c;
            }
            else
            {
                estado_atual = 2;
                token += c;
            }
            break;
        case 5:
            if (regex_match(string(1, c), integer))
            {
                estado_atual = 5;
                token += c;
            }
            else if (regex_match(string(1, c), comma))
            {
                estado_atual = 7;
                token += c;
            }
            else
            {

                if (get_integer(token, lex))
                {
                    estado_atual = 1;
                    token.clear();
                    arquivo.putback(c);
                }
                else
                {
                    estado_atual = 2;
                }
            }
            break;
        case 7:
            if (regex_match(string(1, c), integer))
            {
                estado_atual = 8;
                token += c;
            }
            else
            {
                estado_atual = 2;
                token += c;
            }
            break;
        case 8:
            if (regex_match(string(1, c), integer))
            {
                estado_atual = 8;
                token += c;
            }
            else
            {

                if (get_double(token, lex))
                {
                    estado_atual = 1;
                    token.clear();
                    arquivo.putback(c);
                }
                else
                {
                    estado_atual = 2;
                }
            }
            break;
        case 10:
            if (regex_match(string(1, c), id))
            {
                estado_atual = 10;
                token += c;
            }
            else
            {
                if (get_token(token, lex))
                {
                    // cout << "getou o token " << endl;
                    // cout << "token: " << token << endl;
                    if (regex_match(token, reserved_comment))
                    {
                        // cout << "fez o regex do token commnent" << endl;
                        estado_atual = 17;
                    }
                    else
                    {
                        estado_atual = 1;
                    }
                    token.clear();
                    arquivo.putback(c);
                }
                else
                {
                    estado_atual = 2;
                }
            }
            break;
        case 12:
            if (regex_match(string(1, c), all_except_close_brace))
            {
                estado_atual = 12;
            }
            else if (get_end_comment(string(1, c), lex))
            {
                estado_atual = 1;
                token.clear();
            }
            else
            {
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
            // cout<< "token no 14 " << token << endl;
            // cout << "caso 14 " << token << endl;
            if (get_special_char(token, lex))
            {
                // cout << "getou token special char" << endl;
                // cout << "token " << token << endl;
                estado_atual = 1;
                token.clear();
            }
            else
            {
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
            if (regex_match(string(1, c), op_rel_minor) || regex_match(string(1, c), op_rel_bigger) || regex_match(string(1, c), op_rel_equal) || regex_match(string(1, c), op_rel_mEqual) || regex_match(string(1, c), op_rel_bEqual) || regex_match(string(1, c), op_rel_notEqual))
            {
                estado_atual = 15;
                token += c;
            }
            else
            {
                if (get_op_rel(token, lex))
                {
                    estado_atual = 1;
                    token.clear();
                    arquivo.putback(c);
                }
                else
                {
                    estado_atual = 2;
                }
            }
            break;
        case 16:
            if (regex_match(string(1, c), op_arit_sum) || regex_match(string(1, c), op_arit_sub) || regex_match(string(1, c), op_arit_mult) || regex_match(string(1, c), op_arit_div) || regex_match(string(1, c), op_arit_pow))
            {
                estado_atual = 16;
                token += c;
            }
            else
            {
                if (get_op_arit(token, lex))
                {
                    estado_atual = 1;
                    token.clear();
                    arquivo.putback(c);
                }
                else
                {
                    estado_atual = 2;
                }
            }
            break;

        case 17:
            token += c;
            // cout << "estado atual 17 " << token << endl;
            if (get_init_comment(token, lex))
            {
                estado_atual = 12;
                token.clear();
            }
            else
            {
                estado_atual = 2;
            }
            // cout << "estado atual dps do 17 " << estado_atual << endl;
            break;
        case 30:
            arquivo.putback(c); //{
            // cout<< "token no 14 " << token << endl;
            // cout << "caso 14 " << token << endl;
            if (get_op_init(token, lex))
            {
                // cout << "getou token special char" << endl;
                // cout << "token " << token << endl;
                estado_atual = 1;
                token.clear();
            }
            else
            {
                estado_atual = 2;
            }
            break;

        case 31:
            arquivo.putback(c); //{
            // cout<< "token no 14 " << token << endl;
            // cout << "caso 14 " << token << endl;
            if (get_op_end(token, lex))
            {
                // cout << "getou token special char" << endl;
                // cout << "token " << token << endl;
                estado_atual = 1;
                token.clear();
            }
            else
            {
                estado_atual = 2;
            }
            break;

        case 32:
            arquivo.putback(c); //{
            // cout<< "token no 14 " << token << endl;
            // cout << "caso 14 " << token << endl;
            if (get_parameter_init(token, lex))
            {
                // cout << "getou token special char" << endl;
                // cout << "token " << token << endl;
                estado_atual = 1;
                token.clear();
            }
            else
            {
                estado_atual = 2;
            }
            break;

        case 33:
            arquivo.putback(c); //{
            // cout<< "token no 14 " << token << endl;
            // cout << "caso 14 " << token << endl;
            if (get_parameter_end(token, lex))
            {
                // cout << "getou token special char" << endl;
                // cout << "token " << token << endl;
                estado_atual = 1;
                token.clear();
            }
            else
            {
                estado_atual = 2;
            }
            break;

        case 34:
            arquivo.putback(c); //{
            // cout<< "token no 14 " << token << endl;
            // cout << "caso 14 " << token << endl;
            if (get_op_mid(token, lex))
            {
                // cout << "getou token special char" << endl;
                // cout << "token " << token << endl;
                estado_atual = 1;
                token.clear();
            }
            else
            {
                estado_atual = 2;
            }
            break;
        }
    }

    // for (const auto& pair : lex) {
    //     // cout << "frio ne" << endl;
    //     // cout << pair.first << ": " << pair.second << endl;
    // }
    if (!token.empty())
    {
        switch (estado_atual)
        {
        case 5:
            get_integer(token, lex);
            break;
        case 8:
            get_double(token, lex);
            break;
        case 10:
            get_token(token, lex);
            break;
        case 14:
            get_special_char(token, lex);
            break;
        case 15:
            get_op_rel(token, lex);
            break;
        case 16:
            get_op_arit(token, lex);
            break;
        case 17:
            get_init_comment(token, lex);
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
