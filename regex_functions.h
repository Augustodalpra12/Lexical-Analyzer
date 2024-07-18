#ifndef REGEX_FUNCTIONS_H
#define REGEX_FUNCTIONS_H
#include <map>
#include <tuple>
#include <regex>
#include "regex_definitions.h"
using namespace std;

bool get_op_init(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, symbol_op_init))
    {
        lex[lastIndex] = make_tuple("symbol_op_init", token);
        return true;
    }
    return false;
}
bool get_op_end(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, symbol_op_end))
    {
        lex[lastIndex] = make_tuple("symbol_op_end", token);
        return true;
    }
    return false;
}

bool get_op_mid(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, symbol_op_mid))
    {
        lex[lastIndex] = make_tuple("symbol_op_mid", token);
        return true;
    }
    return false;
}

bool get_parameter_init(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, symbol_parameter_init))
    {
        lex[lastIndex] = make_tuple("symbol_parameter_init", token);
        return true;
    }
    return false;
}

bool get_parameter_end(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, symbol_parameter_end))
    {
        lex[lastIndex] = make_tuple("symbol_parameter_end", token);
        return true;
    }
    return false;
}

bool get_op_arit(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, op_arit_sum))
    {
        lex[lastIndex] = make_tuple("op_arit_sum", token);
        return true;
    }
    else if (regex_match(token, op_arit_sub))
    {
        lex[lastIndex] = make_tuple("op_arit_sub", token);
        return true;
    }
    else if (regex_match(token, op_arit_mult))
    {
        lex[lastIndex] = make_tuple("op_arit_mult", token);
        return true;
    }
    else if (regex_match(token, op_arit_div))
    {
        lex[lastIndex] = make_tuple("op_arit_div", token);
        return true;
    }
    else if (regex_match(token, op_arit_pow))
    {
        lex[lastIndex] = make_tuple("op_arit_pow", token);
        return true;
    }
    return false;
}

bool get_op_rel(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, op_rel_minor))
    {
        lex[lastIndex] = make_tuple("op_rel_minor", token);
        return true;
    }
    else if (regex_match(token, op_rel_bigger))
    {
        lex[lastIndex] = make_tuple("op_rel_bigger", token);
        return true;
    }
    else if (regex_match(token, op_rel_equal))
    {
        lex[lastIndex] = make_tuple("op_rel_equal", token);
        return true;
    }
    else if (regex_match(token, op_rel_mEqual))
    {
        lex[lastIndex] = make_tuple("op_rel_mEqual", token);
        return true;
    }
    else if (regex_match(token, op_rel_bEqual))
    {
        lex[lastIndex] = make_tuple("op_rel_bEqual", token);
        return true;
    }
    else if (regex_match(token, op_rel_notEqual))
    {
        lex[lastIndex] = make_tuple("op_rel_notEqual", token);
        return true;
    }
    return false;
}

bool get_special_char(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, symbol_op_init))
    {
        lex[lastIndex] = make_tuple("symbol_op_init", token);
        return true;
    }
    else if (regex_match(token, symbol_op_end))
    {
        lex[lastIndex] = make_tuple("symbol_op_end", token);
        return true;
    }
    else if (regex_match(token, symbol_parameter_init))
    {
        lex[lastIndex] = make_tuple("symbol_parameter_init", token);
        return true;
    }
    else if (regex_match(token, symbol_parameter_end))
    {
        lex[lastIndex] = make_tuple("symbol_parameter_end", token);
        return true;
    }
    else if (regex_match(token, symbol_op_mid))
    {
        lex[lastIndex] = make_tuple("symbol_op_mid", token);
        return true;
    }
    return false;
}

bool get_init_comment(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, symbol_op_init))
    {
        lex[lastIndex] = make_tuple("symbol_op_init", token);
        return true;
    }
    return false;
}

bool get_end_comment(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, symbol_op_end))
    {
        lex[lastIndex] = make_tuple("symbol_op_end", token);
        return true;
    }
    return false;
}
bool get_token(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, reserved_loops))
    {
        lex[lastIndex] = make_tuple("reserved_loops", token);
        return true;
    }
    else if (regex_match(token, reserved_condition))
    {
        lex[lastIndex] = make_tuple("reserved_condition", token);
        return true;
    }
    else if (regex_match(token, reserved_arit))
    {
        lex[lastIndex] = make_tuple("reserved_arit", token);
        return true;
    }
    else if (regex_match(token, reserved_main))
    {
        lex[lastIndex] = make_tuple("reserved_main", token);
        return true;
    }
    else if (regex_match(token, reserved_types))
    {
        lex[lastIndex] = make_tuple("reserved_types", token);
        return true;
    }
    else if (regex_match(token, reserved_comment))
    {
        lex[lastIndex] = make_tuple("reserved_comment", token);
        return true;
    }
    else if (regex_match(token, reserved_prt))
    {
        lex[lastIndex] = make_tuple("reserved_prt", token);
        return true;
    }
    else if (regex_match(token, reserved_scn))
    {
        lex[lastIndex] = make_tuple("reserved_scn", token);
        return true;
    }
    else if (regex_match(token, id))
    {
        lex[lastIndex] = make_tuple("id", token);
        return true;
        // cout << "Token encontrado: " << token << endl;
        return true;
    }
    return false;
}

bool get_integer(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, integer_signal))
    {
        lex[lastIndex] = make_tuple("integer_signal", token);
        return true;
    }
    else if (regex_match(token, integer))
    {
        lex[lastIndex] = make_tuple("integer", token);
        return true;
    }
    return false;
}

bool get_double(string token, map<int, tuple<string, string>> &lex)
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
    if (regex_match(token, double_regex))
    {
        lex[lastIndex] = make_tuple("double", token);
        return true;
    }
    return false;
}

// bool get_comment_token(string token, map<int, tuple<string, string>>& lex) {
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