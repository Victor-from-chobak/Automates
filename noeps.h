#include <set>
#include "data.h"

// # = eps

void  bfs_noeps(Automat& new_automat, const Automat& automata) {

    for (int current_v = 0; current_v < automata.states; ++current_v) {

        std::set<edge, comp_for_edges> edges;
        std::vector<bool> was(automata.states, false);
    
        std::queue<int> queue;
        was[current_v] = true;
        bool is_terminal = false;
        queue.push(current_v);

        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            is_terminal |= automata.terminal[vertex];

            for (const edge& edge: automata.graph[vertex]) {
                if (edge.letter != '#') {
                    edges.insert(edge);
                    continue;
                }

                if (was[edge.to] ) {
                    continue;
                }
                
                queue.push(edge.to);

            }
        }

        if (is_terminal) {
            new_automat.add_terminal(current_v);
        }

        for (const edge& edge: edges) {
            new_automat.add_edge(current_v, edge);
        }
    }

}

Automat get_noeps(const Automat& automata) {
    
    Automat new_automat;
    new_automat.resize(automata.states);
    
    bfs_noeps(new_automat, automata);
    new_automat.renumber_vertexes();

    return new_automat;
}
