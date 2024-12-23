S -> <BEGIN>

RESERVED_TYPES -> typeInt | typeDouble 

BEGIN -> typeInt reserved_main symbol_parameter_init 
symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end

CODE_BLOCK -> <ATTRIBUTION> <CODE_BLOCK> | <ATTRIBUTION_BOOL> <CODE_BLOCK> | <PRINT> <CODE_BLOCK> | <SCAN> <CODE_BLOCK> | 
<LAPS> <CODE_BLOCK> | <CIRCUIT> <CODE_BLOCK> | <PIT> <CODE_BLOCK> | <ATTRIBUTION_STR> <CODE_BLOCK> | <ATTRIBUTION_CHAR> <CODE_BLOCK> | ε

EXPRESSION -> <BOOL_EXPR> <EXPRESSION'> end_line 
EXPRESSION' -> op_arit_sum <MULT_DIV> <EXPRESSION'> | op_arit_sub <MULT_DIV> <EXPRESSION'> | ε 

BOOL_EXPR -> <MULT_DIV> <BOOL_EXPR'>
BOOL_EXPR' -> op_log_e <MULT_DIV> <BOOL_EXPR'> | op_log_or <MULT_DIV> <BOOL_EXPR'> | ε

MULT_DIV -> <POW> <MULT_DIV'>
MULT_DIV' -> op_arit_mult <POW> <MULT_DIV'> | op_arit_div <POW> <MULT_DIV'> | ε

POW -> <VAR> <POW'>
POW' -> op_arit_pow <VAR> <POW'> | ε

VAR -> symbol_parameter_init <EXPRESSION> symbol_parameter_end | id | integer | double | bool_false | bool_true

# EXPRESSÃO

# ATRIBUIÇÃO

ATTRIBUTION -> <RESERVED_TYPES> <ATTRIBUTION'> | <ATTRIBUTION'>
ATTRIBUTION' -> id <ATTRIBUTION''>
ATTRIBUTION'' -> op_rel_equal <ATTRIBUTION_VALUE> 

ATTRIBUTION_VALUE -> <EXPRESSION> | bool_false end_line | bool_true end_line | quotes all_except_quotes quotes end_line  

ATTRIBUTION_BOOL -> typeBoolean id <ATTRIBUTION_BOOL'>  
ATTRIBUTION_BOOL' -> op_rel_equal <ATTRIBUTION_BOOL''> | end_line
ATTRIBUTION_BOOL'' -> bool_false end_line | bool_true end_line | <ID_OR_VALUE> <ATTRIBUTION_BOOL'''> end_line | op_rel_not <ID_OR_VALUE> <ATTRIBUTION_BOOL'''> end_line 
ATTRIBUTION_BOOL''' -> <LOG_SYMBOLS> <ID_OR_VALUE> <ATTRIBUTION_BOOL'''>  | ε 

ATTRIBUTION_STR -> typeStr id <ATTRIBUTION_STR'>
ATTRIBUTION_STR' -> op_rel_equal quotes all_except_quotes quotes end_line | end_line


# ATRIBUIÇÃO

# PRINT

PRINT -> reserved_prt symbol_parameter_init <ID_OR_STRING> symbol_parameter_end end_line
ID_OR_STRING -> quotes all_except_quotes quotes <ID_OR_STRING'> | id <ID_OR_STRING'> | integer <ID_OR_STRING'> | double <ID_OR_STRING'>
ID_OR_STRING' -> op_arit_sum <ID_OR_STRING''> <ID_OR_STRING'> | ε
ID_OR_STRING'' -> quotes all_except_quotes quotes | id | integer | double

# PRINT

# SCAN

SCAN -> reserved_scn symbol_parameter_init id symbol_parameter_end end_line

# SCAN

# LAPS

LAPS -> laps symbol_parameter_init <INIT_LAPS>  op_rel_equal <ID_OR_VALUE> symbol_op_mid id <REL_SYMBOLS> <ID_OR_VALUE> symbol_op_mid id op_rel_equal <LAPS_INC> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end
INIT_LAPS -> typeInt id | id
LAPS_INC -> overtake | brake | id <LAPS_SYMBOLS> <ID_OR_VALUE>
<LAPS_SYMBOLS> -> op_arit_sum | op_arit_sub | op_arit_mult | op_arit_div
<ID_OR_VALUE> -> id | integer     

# LAPS

# CIRCUIT

CIRCUIT -> circuit symbol_parameter_init <CIRCUIT_LOG> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end
CIRCUIT_LOG -> id <CIRCUIT_LOG'> | integer <CIRCUIT_LOG'> | double <CIRCUIT_LOG'> 
CIRCUIT_LOG' -> <LOOPS_SYMBOLS> <CIRCUIT_LOG> | ε
LOOPS_SYMBOLS -> <REL_SYMBOLS> | <LOG_SYMBOLS> |  <ARIT_SYMBOLS>


<ARIT_SYMBOLS> -> op_arit_sum | op_arit_sub | op_arit_div | op_arit_mult | op_arit_pow
LOG_SYMBOLS -> op_log_e | op_log_or 
<REL_SYMBOLS> -> op_rel_minor | op_rel_bigger | op_rel_minor_equal | op_rel_bigger_equal | op_rel_double_equal | op_rel_not_equal

# PIT

PIT-> pitEntry symbol_parameter_init <PIT_LOG> symbol_parameter_end symbol_block_init <CODE_BLOCK> symbol_block_end <PIT_EXIT>
PIT_LOG-> id <PIT_LOG'> | integer <PIT_LOG'> | double <PIT_LOG'> 
PIT_LOG'-> <LOOPS_SYMBOLS> <PIT_LOG> | ε
PIT_EXIT -> pitExit symbol_parameter_init CODE_BLOCK symbol_block_end | ε
