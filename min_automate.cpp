#include "data.h"
#pragma once

automat get_minimal(const automat& aut, const Graph& rev_graph) {

    std::vector<std::vector<bool> > different(aut.n, std::vector<bool>(aut.n, false));
    std::queue<std::pair<int, int> > queue;

    for (int i = 0; i < aut.n; ++i) {
        for (int j = i + 1; j < aut.n; ++j) {
            different[i][j] = aut.terminal[i] ^ aut.terminal[j];
            different[j][i] = aut.terminal[i] ^ aut.terminal[j];
            if (different[i][j] ) {
                queue.push({i, j});
            }
        }
    }

    while (!queue.empty() ) {
        std::pair<int, int> p = queue.front();
        queue.pop();
        int u = p.first;
        int v = p.second;

        for (const edge& edge1: rev_graph[u]) {
            for (const edge& edge2: rev_graph[v]) {
                
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

    
    std::vector<int> classes(aut.n, static_cast<int>(automat::DEFAULT));
    int current_class = -1;

    for (int i = 0; i < aut.n; ++i) {
        if (classes[i] != automat::DEFAULT) {
            continue;
        }
        
        ++current_class;
        classes[i] = current_class;
        for (int j = 0; j < aut.n; ++j) {
            if (classes[j] > -1) {
                continue;
            }
            
            if (different[i][j] ) {
                continue;
            }

            classes[j] = current_class;
        }
    }
    

    automat answer;
    answer.resize(current_class + 1);

    std::map<std::pair<int, char>, int> mapping;

    for (int v = 0; v < aut.n; ++v) {
        for (const edge& edge: aut.graph[v]) {
            int class1 = classes[v];
            int class2 = classes[edge.to];
            mapping[{class1, edge.letter}] = class2;
        }
    }
    
    for (const auto& pairs: mapping) {
        edge edge(pairs.second, pairs.first.second);
        answer.add_edge(pairs.first.first, edge);
    }
    
    std::vector<bool> new_term(current_class + 1, false);

    for (int v = 0; v < aut.n; ++v) {
        int vertex_class = classes[v];
        
        if (aut.terminal[v] && !answer.terminal[vertex_class]) {
            answer.add_terminal(vertex_class);
        }
    }

    return answer;
}



automat get_min_automate(const automat& aut) {
    
    Graph reversed_edges;
    reversed_edges.resize(aut.n);
    
    for (int v = 0; v < aut.n; ++v) {
        for (const edge& cur_edge: aut.graph[v]) {
            edge rev_edge(v, cur_edge.letter);
            reversed_edges[cur_edge.to].push_back(rev_edge);
        }
    }

    return get_minimal(aut, reversed_edges);
}
