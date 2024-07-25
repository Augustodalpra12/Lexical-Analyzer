#ifndef REGEX_FUNCTIONS_H
#define REGEX_FUNCTIONS_H
#include <map>
#include <tuple>
#include <regex>
#include "regex_definitions.h"
using namespace std;

void decrease_line(int &line, char c) {
    if(regex_match(string(1, c), line_feed) || regex_match(string(1, c), line_feed2)) {
        line--;
    }
    
}

int get_index(map<int, tuple<string, string, int>> &lex)
{
    int lastIndex;
    if (!lex.empty())
    {
        auto last = lex.rbegin(); // rbegin() aponta para o último elemento
        lastIndex = last->first;
        lastIndex++;
    }
    else
    {
        lastIndex = 0;
    }
    return lastIndex;
}

bool get_braces_init(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, symbol_op_init))
    {
        lex[lastIndex] = make_tuple("symbol_op_init", token, linha_atual);
        return true;
    } 
    return false;
}

bool get_braces_end(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if(regex_match(token, symbol_op_end)) {
        lex[lastIndex] = make_tuple("symbol_op_end", token, linha_atual);
        return true;
    }
    return false;
}

bool get_quotes(string token, map<int, tuple<string, string, int>> &lex, int linha_atual) {
    int lastIndex = get_index(lex);
    if (regex_match(token, quotes))
    {
        lex[lastIndex] = make_tuple("quotes", token, linha_atual);
        return true;
    } 
    return false;
}

bool get_parameters_init(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, symbol_parameter_init))
    {
        lex[lastIndex] = make_tuple("symbol_parameter_init", token, linha_atual);
        return true;
    } 
    return false;
}

bool get_parameters_mid(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if(regex_match(token, symbol_op_mid)) {
        lex[lastIndex] = make_tuple("symbol_parameter_end", token, linha_atual);
        return true;
    }
    return false;
}
bool get_parameters_end(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if(regex_match(token, symbol_parameter_end)) {
        lex[lastIndex] = make_tuple("symbol_parameter_end", token, linha_atual);
        return true;
    } 
    return false;
}

bool get_arit(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, op_arit_sum))
    {
        lex[lastIndex] = make_tuple("op_arit_sum", token, linha_atual);
        return true;
    }
    else if (regex_match(token, op_arit_sub))
    {
        lex[lastIndex] = make_tuple("op_arit_sub", token, linha_atual);
        return true;
    }
    else if (regex_match(token, op_arit_mult))
    {
        lex[lastIndex] = make_tuple("op_arit_mult", token, linha_atual);
        return true;
    }
    else if (regex_match(token, op_arit_div))
    {
        lex[lastIndex] = make_tuple("op_arit_div", token, linha_atual);
        return true;
    }
    else if (regex_match(token, op_arit_pow))
    {
        lex[lastIndex] = make_tuple("op_arit_pow", token, linha_atual);
        return true;
    }
    return false;
}

bool get_logic(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex;
    if (!lex.empty())
    {
        auto last = lex.rbegin(); // rbegin() a ponta para o último elemento
        lastIndex = last->first;
        lastIndex++;
    }
    else
    {
        lastIndex = 0;
    }
    if (regex_match(token, op_rel_minor))
    {
        lex[lastIndex] = make_tuple("op_rel_minor", token, linha_atual);
        return true;
    }
    else if (regex_match(token, op_rel_bigger))
    {
        lex[lastIndex] = make_tuple("op_rel_bigger", token, linha_atual);
        return true;
    }
    else if (regex_match(token, op_rel_equal))
    {
        lex[lastIndex] = make_tuple("op_rel_equal", token, linha_atual);
        return true;
    }
    else if (regex_match(token, op_rel_not))
    {
        lex[lastIndex] = make_tuple("op_rel_not", token, linha_atual);
        return true;
    }
    return false;
}


bool get_op_end(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, symbol_op_end))
    {
        lex[lastIndex] = make_tuple("symbol_op_end", token, linha_atual);
        return true;
    }
    return false;
}

bool get_op_mid(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, symbol_op_mid))
    {
        lex[lastIndex] = make_tuple("symbol_op_mid", token, linha_atual);
        return true;
    }
    return false;
}

bool get_parameter_init(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, symbol_parameter_init))
    {
        lex[lastIndex] = make_tuple("symbol_parameter_init", token, linha_atual);
        return true;
    }
    return false;
}

bool get_parameter_end(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, symbol_parameter_end))
    {
        lex[lastIndex] = make_tuple("symbol_parameter_end", token, linha_atual);
        return true;
    }
    return false;
}

bool get_integer(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex;
    if (!lex.empty())
    {
        auto last = lex.rbegin(); // rbegin() aponta para o último elemento
        lastIndex = last->first;
        lastIndex++;
    }  else  {
        lastIndex = 0;
    }
    if (regex_match(token, integer))
    {
        lex[lastIndex] = make_tuple("integer", token, linha_atual);
        return true;
    }
    return false;
}

bool get_double(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, double_regex))
    {
        lex[lastIndex] = make_tuple("double", token, linha_atual);
        return true;
    }
    return false;
}

bool get_token(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, reserved_loops))
    {
        lex[lastIndex] = make_tuple("reserved_loops", token, linha_atual);
        return true;
    }
    else if (regex_match(token, reserved_condition))
    {
        lex[lastIndex] = make_tuple("reserved_condition", token, linha_atual);
        return true;
    }
    else if (regex_match(token, reserved_arit))
    {
        lex[lastIndex] = make_tuple("reserved_arit", token, linha_atual);
        return true;
    }
    else if (regex_match(token, reserved_main))
    {
        lex[lastIndex] = make_tuple("reserved_main", token, linha_atual);
        return true;
    }
    else if (regex_match(token, reserved_types))
    {
        lex[lastIndex] = make_tuple("reserved_types", token, linha_atual);
        return true;
    }
    else if (regex_match(token, reserved_comment))
    {
        return true;
    }
    else if (regex_match(token, reserved_prt))
    {
        lex[lastIndex] = make_tuple("reserved_prt", token, linha_atual);
        return true;
    }
    else if (regex_match(token, reserved_scn))
    {
        lex[lastIndex] = make_tuple("reserved_scn", token, linha_atual);
        return true;
    }
    else if (regex_match(token, id))
    {
        lex[lastIndex] = make_tuple("id", token, linha_atual);
        return true;
        // cout << "Token encontrado: " << token << endl;
        return true;
    }
    return false;
}

bool get_dot(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, end_line))
    {
        lex[lastIndex] = make_tuple("dot", token, linha_atual);
        return true;
    }
    return false;
}

bool get_text_between_quotes(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    // cout << "entrou na funcao" << endl;
    if (regex_match(token, all_except_quotes) || regex_match(token, portuguese)|| regex_match(token, space))
    {
        lex[lastIndex] = make_tuple("text_between_quotes", token, linha_atual);
        return true;
    }
    return false;
}


bool get_log_e(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, op_log_e))
    {
        lex[lastIndex] = make_tuple("op_log_e", token, linha_atual);
        return true;
    }
    return false;
}

bool get_log_or(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, op_log_or))
    {
        lex[lastIndex] = make_tuple("op_log_or", token, linha_atual);
        return true;
    }
    return false;
}

bool get_error(string token, map<int, tuple<string, string, int>> &lex, int linha_atual)
{
    int lastIndex = get_index(lex);
    if (regex_match(token, restricted_symbols))
    {
        lex[lastIndex] = make_tuple("error", token, linha_atual);
        return true;
    }
    return false;
}
// bool get_special_char(string token, map<int, tuple<string, string, int>> &lex)
// {
//     int lastIndex;
//     if (!lex.empty())
//     {
//         auto last = lex.rbegin(); // rbegin() aponta para o último elemento
//         lastIndex = last->first;
//         lastIndex++;
//     }
//     else
//     {
//         lastIndex = 0;
//     }
//     if (regex_match(token, symbol_op_init))
//     {
//         lex[lastIndex] = make_tuple("symbol_op_init", token);
//         return true;
//     }
//     else if (regex_match(token, symbol_op_end))
//     {
//         lex[lastIndex] = make_tuple("symbol_op_end", token);
//         return true;
//     }
//     else if (regex_match(token, symbol_parameter_init))
//     {
//         lex[lastIndex] = make_tuple("symbol_parameter_init", token);
//         return true;
//     }
//     else if (regex_match(token, symbol_parameter_end))
//     {
//         lex[lastIndex] = make_tuple("symbol_parameter_end", token);
//         return true;
//     }
//     else if (regex_match(token, symbol_op_mid))
//     {
//         lex[lastIndex] = make_tuple("symbol_op_mid", token);
//         return true;
//     }
//     return false;
// }

// bool get_init_comment(string token, map<int, tuple<string, string, int>> &lex)
// {
//     int lastIndex;
//     if (!lex.empty())
//     {
//         auto last = lex.rbegin(); // rbegin() aponta para o último elemento
//         lastIndex = last->first;
//         lastIndex++;
//     }
//     else
//     {
//         lastIndex = 0;
//     }
//     if (regex_match(token, symbol_op_init))
//     {
//         lex[lastIndex] = make_tuple("symbol_op_init", token);
//         return true;
//     }
//     return false;
// }

// bool get_end_comment(string token, map<int, tuple<string, string, int>> &lex)
// {
//     int lastIndex;
//     if (!lex.empty())
//     {
//         auto last = lex.rbegin(); // rbegin() aponta para o último elemento
//         lastIndex = last->first;
//         lastIndex++;
//     }
//     else
//     {
//         lastIndex = 0;
//     }
//     if (regex_match(token, symbol_op_end))
//     {
//         lex[lastIndex] = make_tuple("symbol_op_end", token);
//         return true;
//     }
//     return false;
// }




// bool get_comment_token(string token, map<int, tuple<string, string, int>>& lex) {
//         int lastIndex;
//     if (!lex.empty()) {
//         auto last = lex.rbegin(); // rbegin() aponta para o último elemento
//         lastIndex = last->first;
//         lastIndex++;
//     } else {
//         lastIndex = 0;
//     }
//     if(regex_match(token, reserved_comment)) {
//         lex[lastIndex] = make_tuple("reserved_comment", token);

//         return true;
//     }
//     return false;
// }

#endif // REGEX_FUNCTIONS_H