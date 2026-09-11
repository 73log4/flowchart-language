//
// Created by benji on 9/11/26.
//

#ifndef FLOWCHART_LANGUAGE_CMD_H
#define FLOWCHART_LANGUAGE_CMD_H
#include <regex>
#include <string>
#include <unordered_map>

inline std::unordered_map<std::string, std::string> variables;

class Value {
public:
    Value() = default;

    Value(const std::string &data, bool is_data_var) {
        this->data = data;
        this->is_data_var = is_data_var;
    }

    [[nodiscard]] std::string load() const {
        if (is_data_var)
            return variables[data];
        return data;
    }

    bool operator==(const Value & other) const {
        return load() == other.load();
    }

private:
    std::string data;
    bool is_data_var{};
};

class CMD {
public:
    virtual ~CMD() = default;

    virtual void run() = 0;

    [[nodiscard]] virtual CMD *get_next_node() const = 0;
};

class Print : public CMD {
public:
    Value ms;
    CMD *next_node;

    Print(Value ms, CMD *next_node) : ms(std::move(ms)) {
        this->next_node = next_node;
    }

    void run() override;

    [[nodiscard]] CMD *get_next_node() const override;
};

class AssignVar : public CMD {
public:

    AssignVar(const std::string &name, Value value, CMD *next_node)
        : value(std::move(value)) {
        this->name = name;
        this->next_node = next_node;
    }

    void run() override;

    [[nodiscard]] CMD *get_next_node() const override;

    std::string name;
    Value value;
    CMD *next_node;
};

class IfRegex : public CMD {
public:
    IfRegex(Value value, const std::string &regex, CMD *true_branch, CMD *false_branch)
        : value(std::move(value)), regex(regex) {
        this->true_branch = true_branch;
        this->false_branch = false_branch;
    }

    void run() override {
        //nothing
    }

    [[nodiscard]] CMD *get_next_node() const override;

private:
    Value value;
    std::regex regex;
    CMD *true_branch;
    CMD *false_branch;
};

class Input : public CMD {
public:
    Input(const std::string& in_var, CMD* next_node) {
        this->in_var = in_var;
        this->next_node = next_node;
    }

    void run() override;

    [[nodiscard]] CMD* get_next_node() const override;

private:
    std::string in_var;
    CMD* next_node;
};

class Jump : public CMD {
public:
    Jump(CMD* node) {
        this->node = node;
    }

    void run() override {}

    [[nodiscard]] CMD* get_next_node() const override;

    CMD* node;
};

class Switch : public CMD {
public:
    struct ValueNode {
        Value value;
        CMD* node{};
    };

    Switch(Value value, const std::vector<Value>& cases,
        const std::vector<CMD*>& case_nodes)
        : value(std::move(value))
    {
        for (int i = 0; i < cases.size(); i++)
            this->cases.emplace_back(cases[i], case_nodes[i]);

    }

    void run() override {}

    [[nodiscard]] CMD* get_next_node() const override;

private:
    Value value;
    std::vector<ValueNode> cases;
};

class ExecuteBash : public CMD {
public:
    ExecuteBash(const std::string& bash_line, CMD* next_node) {
        this->bash_line = bash_line;
        this->next_node = next_node;
    }

    void run() override;

    [[nodiscard]] CMD* get_next_node() const override;

private:
    std::string bash_line;
    CMD* next_node;
};

class Exit : public CMD {

    void run() override {}

    [[nodiscard]] CMD* get_next_node() const override {return nullptr;}

};
#endif //FLOWCHART_LANGUAGE_CMD_H
