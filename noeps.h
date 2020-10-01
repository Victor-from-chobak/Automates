#include <set>
#include "data.h"

// # = eps

void dfs_noeps(int v, const automat& aut, std::vector<bool>& was, std::set<edge, comp_for_edges>& edges, bool& term) {
    
    was[v] = true;

    term |= aut.terminal[v];

    for (const edge& edge: aut.graph[v]) {
        
        if (edge.letter != '#') {
            edges.insert(edge);
            continue;
        }
        
        if (was[edge.to] ) {
            continue;
        }

        dfs_noeps(edge.to, aut, was, edges, term);
    }

}


automat get_noeps(const automat& aut) {
    
    automat new_automat;
    new_automat.resize(aut.n);

    for (int i = 0; i < aut.n; ++i) {
        std::set<edge, comp_for_edges> edges;
        std::vector<bool> was(aut.n, false);
        bool vterm = false;
        dfs_noeps(i, aut, was, edges, vterm);

        for (const edge& edge: edges) {
           new_automat.add_edge(i, edge);
        }
        
        if (vterm) {
            new_automat.add_terminal(i);
        }
    }
    
    new_automat.renumber();

    return new_automat;
}
