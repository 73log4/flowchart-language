//
// Created by benji on 9/11/26.
//

#include "CMD.h"
#include <iostream>

void Print::run() {
    std::cout << ms.load();
}

CMD *Print::get_next_node() const {
    return next_node;
}

void AssignVar::run() {
    variables[name] = value.load();
}

CMD *AssignVar::get_next_node() const {
    return next_node;
}

CMD *IfRegex::get_next_node() const {
    if (std::regex_match(value.load(), regex))
        return true_branch;
    return false_branch;
}

void Input::run() {
    std::cin >> variables[in_var];
}

CMD *Input::get_next_node() const {
    return next_node;
}

CMD *Jump::get_next_node() const {
    return node;
}

CMD *Switch::get_next_node() const {
    for (const auto &[value_, node]: cases)
        if (value_ == value)
            return node;

    return nullptr;
}

std::string clean_bash_line(const std::string &line) {
    std::string result;
    size_t size = line.size();
    for (int i = 0; i < size; i++) {
        if (line[i] == '{') {
            //search for substring
            std::string sub_string;
            int idx = i + 1;
            while (line[idx] != '}') {
                sub_string += line[idx];
                idx++;
            }

            if (variables.contains(sub_string))
                result += variables[sub_string];
            else
                throw; //Non existing variable

            i = idx;
        } else
            result += line[i];
    }

    return result;
}

void ExecuteBash::run() {
    std::system(clean_bash_line(bash_line).c_str());
}

CMD *ExecuteBash::get_next_node() const {
    return next_node;
}
