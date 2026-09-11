#include "Interpreter.h"


int main() {

    std::string cmd = "echo {in_var_}";

    auto* jump = new Jump(nullptr);
    auto *print_f = new Print({"You Have FFFFaild\n", false}, jump);
    auto *t = new ExecuteBash(cmd, jump);
    auto *regex = new IfRegex({"in_var", true}, R"(\d)",
        t, print_f);
    auto *input = new Input("in_var", regex);
    auto *in_var = new AssignVar("in_var", {"", false}, input);

    jump->node = in_var;

    Interpreter it(in_var, {in_var, input, regex, print_f, t});

    it.run();
}
