#include "data.h"
#pragma once

using bool_table = std::vector<std::vector<bool> >;


bool_table get_different_vertexes(const Automat& aut, const Graph& rev_graph) {
    bool_table different(aut.states, std::vector<bool>(aut.states, false));
    std::queue<std::pair<int, int> > queue;

    for (int i = 0; i < aut.states; ++i) {
        for (int j = i + 1; j < aut.states; ++j) {
            different[i][j] = aut.terminal[i] ^ aut.terminal[j];
            different[j][i] = aut.terminal[i] ^ aut.terminal[j];
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


Automat make_automat_on_classes(const Automat& aut, const std::vector<int>& equality_classes) {
    
    size_t classes_amount = equality_classes.back();
    Automat answer;
    answer.resize(classes_amount);

    std::map<std::pair<int, char>, int> mapping;

    for (int vertex = 0; vertex < aut.states; ++vertex) {
        for (const edge& edge: aut.graph[vertex]) {
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

    for (int vertex = 0; vertex < aut.states; ++vertex) {
        int vertex_class = equality_classes[vertex];
        
        if (aut.terminal[vertex] && !answer.terminal[vertex_class]) {
            answer.add_terminal(vertex_class);
        }
    }

    return answer;

}


Automat get_minimal(const Automat& aut, const Graph& rev_graph) {

    std::vector<std::vector<bool> > different = get_different_vertexes(aut, rev_graph);
       
    std::vector<int> equality_classes(aut.states, static_cast<int>(Automat::DEFAULT));
    int current_class = -1;

    for (int i = 0; i < aut.states; ++i) {
        if (equality_classes[i] != Automat::DEFAULT) {
            continue;
        }
        
        ++current_class;
        equality_classes[i] = current_class;
        for (int j = 0; j < aut.states; ++j) {
            if (equality_classes[j] > -1) {
                continue;
            }
            
            if (different[i][j] ) {
                continue;
            }

            equality_classes[j] = current_class;
        }
    }
    
    equality_classes.push_back(current_class + 1);

    return make_automat_on_classes(aut, equality_classes);
}


Automat get_min_automate(const Automat& aut) {
    
    Graph reversed_edges;
    reversed_edges.resize(aut.states);
    
    for (int vertex = 0; vertex < aut.states; ++vertex) {
        for (const edge& cur_edge: aut.graph[vertex]) {
            edge rev_edge(vertex, cur_edge.letter);
            reversed_edges[cur_edge.to].push_back(rev_edge);
        }
    }

    return get_minimal(aut, reversed_edges);
}
