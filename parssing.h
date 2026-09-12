#include <string>
#include <vector>
#include <iostream>




typedef std::vector<std::string> code_line;
typedef std::vector<code_line> code_block;

enum CMDType {
    Print,
    Input,
    Init,
    If,
    Exec,
    Jump,
    Switch,
    Exit,
};

// validity checks
bool is_legal_var_name(string var_name);
bool is_legal_string(string str);

bool is_print_line_legal(code_line line);
bool is_input_line_legal(code_line line);
bool is_init_line_legal(code_line line);
bool is_if_line_legal(code_line line);
bool is_exec_line_legal(code_line line);
bool is_jump_line_legal(code_line line);
bool is_switch_line_legal(code_line line);
bool is_exit_line_legal(code_line line);


CMDType get_cmd_type(code_line line);

bool is_line_legal(code_line line);

int parss_stage_2(code_block text_matrix);

code_block parss_stage_1(std::string text);

int parss_code(std::string text);
