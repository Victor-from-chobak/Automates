#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <queue>

// # = eps

using graph = std::vector<std::vector<std::pair<int, char> > >;
using setEdge = std::set<std::pair<int, char> >;
using answer_type = std::pair<graph, std::vector<bool> >;

void dfs(int v, const graph& g, std::vector<bool>& was, setEdge& w, bool& term, const std::vector<bool>& isterm) {
    
    was[v] = true;

    term |= isterm[v];

    for (const auto& e: g[v]) {
        
        int u = e.first;
        char c = e.second;
        
        if (c != '#') {
            w.insert(e);
            continue;
        }
        
        if (was[u] ) {
            continue;
        }

        dfs(u, g, was, w, term, isterm);
    }


}

answer_type renumber_graph(const graph& g, const std::vector<bool>& isterm) {
    size_t n = g.size();
    graph ng;
    size_t cur = 0;

    std::vector<bool> was(n, false);
    std::queue<int> q;
    std::vector<int> mapping(n, -1);

    q.push(0);
    was[0] = true;
    
    while (!q.empty() ) {

        int v = q.front();
        q.pop();
        mapping[v] = cur;
        ++cur;

        for (const auto& e: g[v]) {
            if (was[e.first] ) {
                continue;
            }
            
            q.push(e.first);
            was[e.first] = true;
        }
    }
    
    ng.resize(cur);
    std::vector<bool> nterm(cur, false);

    for (int i = 0; i < n; ++i) {
        int w1 = mapping[i];

        if (w1 == -1) {
            continue;
        }
        
        if (isterm[i]) {
            nterm[w1] = true;
        }
        
        for (const auto& e: g[i]) {
            int u = e.first;
            char c = e.second;
            int w1 = mapping[i];
            int w2 = mapping[u];

            if ((w1 == -1) || (w2 == -1)) {
                continue;
            }

            ng[w1].push_back({w2, c});
        }
    }

    return {ng, nterm};
}


answer_type get_noeps(const std::string& file_name) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    
    freopen(file_name.c_str(), "r", stdin);

    graph g;

    int n, m, t;
    
    std::cin >> n >> m >> t;

    g.resize(n);

    for (int j = 0; j < m; ++j) {
        int u, v;
        char c;
        std::cin >> u >> v >> c;

        g[u].push_back({v, c});
    }
    
    std::vector<bool> term(n, false);

    for (int j = 0; j < t; ++j) {
        int x;
        std::cin >> x;
        term[x] = true;
    }

    graph ng;
    std::vector<bool> nterm(n, false);
    ng.resize(n);

    for (int i = 0; i < n; ++i) {
        setEdge w;
        std::vector<bool> was(n, false);
        bool vterm = false;
        dfs(i, g, was, w, vterm, term);

        for (const auto& e: w) {
            ng[i].push_back(e);
        }

        nterm[i] = vterm;
    }
    
    return renumber_graph(ng, nterm);
}
