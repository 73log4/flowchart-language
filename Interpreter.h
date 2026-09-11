//
// Created by benji on 9/11/26.
//

#ifndef FLOWCHART_LANGUAGE_FLOWCHARTGRAPH_H
#define FLOWCHART_LANGUAGE_FLOWCHARTGRAPH_H
#include "CMD.h"
#include <vector>

class Interpreter {
public:
    std::vector<CMD*> all_nodes;
    CMD* current_node;

    ~Interpreter() {
        for (const auto* ptr : all_nodes)
            delete ptr;
    }

    explicit Interpreter(CMD* start, const std::vector<CMD*>& all_nodes) {
        current_node = start;
        this->all_nodes = all_nodes;
    }

    void run();

};


#endif //FLOWCHART_LANGUAGE_FLOWCHARTGRAPH_H