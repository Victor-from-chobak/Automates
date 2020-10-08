#include "data.h"
#include <map>
#pragma once

void determinate_bfs(const Automat& automata, Automat& new_automate) {
    
    std::queue<int> queue;
    int new_size = (1 << automata.states);
    new_automate.resize(new_size);
    queue.push(1);
    std::vector<bool> was(new_size, false);
    was[1] = true;

    while (!queue.empty()) {
        int mask = queue.front();
        queue.pop();

        std::map<char, int> map_masks;

        for (int i = 0; i < automata.states; ++i) {
            if (!(mask & (1 << i))) {
                continue;
            }
            
            if (automata.terminal[i]) {
                new_automate.add_terminal(mask);
            }

            for (const edge& edge: automata.graph[i]) {
                map_masks[edge.letter] |= (1 << edge.to);
            }
            
        }
        
        for (const auto& [letter, vertex]: map_masks) {
            
            edge new_edge(vertex, letter);

            new_automate.add_edge(mask, new_edge);
            
            if (was[vertex]) {
                continue;
            }

            queue.push(vertex);
            was[vertex] = true;
        }

    }
}


Automat determinate(const Automat& automata) {
    
    Automat new_automate;

    determinate_bfs(automata, new_automate);
    
    for (int state = 0; state < new_automate.states - 1; ++state) {
        new_automate.graph[state] = std::move(new_automate.graph[state + 1]);
        for (edge& edge: new_automate.graph[state]) {
            edge.to -= 1;
        }
        new_automate.terminal[state] = new_automate.terminal[state + 1];
    }

    new_automate.renumber_vertexes();

    return new_automate;
}

