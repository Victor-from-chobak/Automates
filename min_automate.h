#include "data.h"
#pragma once

using bool_table = std::vector<std::vector<bool> >;


bool_table get_different_vertexes(const Automat& automata, const Graph& rev_graph) {
    bool_table different(automata.states, std::vector<bool>(automata.states, false));
    std::queue<std::pair<int, int> > queue;

    for (int i = 0; i < automata.states; ++i) {
        for (int j = i + 1; j < automata.states; ++j) {
            different[i][j] = automata.terminal[i] ^ automata.terminal[j];
            different[j][i] = automata.terminal[i] ^ automata.terminal[j];
            if (different[i][j] ) {
                queue.push({i, j});
            }
        }
    }

    while (!queue.empty() ) {
        auto [from, to]  = queue.front();
        queue.pop();

        for (const edge& edge1: rev_graph[from]) {
            for (const edge& edge2: rev_graph[to]) {
                
                if (edge1.letter != edge2.letter) {
                    continue;
                }

                int vertex1 = edge1.to;
                int vertex2 = edge2.to;

                if (!different[vertex1][vertex2]) {
                    different[vertex1][vertex2] = true;
                    different[vertex2][vertex1] = true;
                    queue.push({vertex1, vertex2});
                }
            }
        }
    }
    
    return different;
}


Automat make_automat_on_classes(const Automat& automata, const std::vector<int>& equality_classes) {
    
    size_t classes_amount = equality_classes.back();
    Automat answer;
    answer.resize(classes_amount);

    std::map<std::pair<int, char>, int> mapping;

    for (int vertex = 0; vertex < automata.states; ++vertex) {
        for (const edge& edge: automata.graph[vertex]) {
            int class1 = equality_classes[vertex];
            int class2 = equality_classes[edge.to];
            mapping[{class1, edge.letter}] = class2;
        }
    }
    
    for (const auto& [map_edge, to]: mapping) {
        const auto [from, letter] = map_edge;
        edge edge(to, letter);
        answer.add_edge(from, edge);
    }
    
    std::vector<bool> new_term(classes_amount, false);

    for (int vertex = 0; vertex < automata.states; ++vertex) {
        int vertex_class = equality_classes[vertex];
        
        if (automata.terminal[vertex] && !answer.terminal[vertex_class]) {
            answer.add_terminal(vertex_class);
        }
    }

    return answer;

}


Automat get_minimal(const Automat& automata, const Graph& rev_graph) {

    std::vector<std::vector<bool> > different = get_different_vertexes(automata, rev_graph);
       
    std::vector<int> equality_classes(automata.states, static_cast<int>(Automat::DEFAULT));
    int current_class = -1;

    for (int state = 0; state < automata.states; ++state) {
        if (equality_classes[state] != Automat::DEFAULT) {
            continue;
        }
        
        ++current_class;
        equality_classes[state] = current_class;
        for (int sub_state = 0; sub_state < automata.states; ++sub_state) {
            if (equality_classes[sub_state] > -1) {
                continue;
            }
            
            if (different[state][sub_state] ) {
                continue;
            }

            equality_classes[sub_state] = current_class;
        }
    }
    
    equality_classes.push_back(current_class + 1);

    return make_automat_on_classes(automata, equality_classes);
}


Automat get_min_automate(const Automat& automata) {
    
    Graph reversed_edges;
    reversed_edges.resize(automata.states);
    
    for (int vertex = 0; vertex < automata.states; ++vertex) {
        for (const edge& cur_edge: automata.graph[vertex]) {
            edge rev_edge(vertex, cur_edge.letter);
            reversed_edges[cur_edge.to].push_back(rev_edge);
        }
    }

    return get_minimal(automata, reversed_edges);
}
