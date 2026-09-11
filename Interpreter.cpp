//
// Created by benji on 9/11/26.
//

#include "Interpreter.h"


void Interpreter::run() {
    while (current_node) {
        current_node->run();

        current_node = current_node->get_next_node();
    }
}