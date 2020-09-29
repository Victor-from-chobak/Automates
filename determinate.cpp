#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <queue>


using graph = std::vector<std::vector<std::pair<int, char> > >;
using answer_type = std::pair<graph, std::vector<bool> >;

void bfs(const graph& g, int n, const std::vector<bool>& isterm, graph& ng, std::vector<bool>& nterm) {
    
    std::queue<int> q;
    int M = (1 << n);
    q.push(1);
    std::vector<bool> was(M, false);
    std::vector<int> mapping(M, -1);
    int cur = 0;

    while (!q.empty()) {
        int mask = q.front();
        q.pop();
        mapping[mask] = cur;
        ++cur;

        std::map<char, int> nmask;
        

        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) {
                continue;
            }
            
            if (isterm[i]) {
                nterm[mask] = true;
            }

            for (const auto& e: g[i]) {
                nmask[e.second] |= (1 << e.first);
            }
            
        }
        
        for (const auto& p: nmask) {
            
            ng[mask].push_back({p.second, p.first});
            
            if (was[p.second]) {
                continue;
            }

            q.push(p.second);
            was[p.second] = true;
        }

    }

    graph ans(cur);
    std::vector<bool> aterm(cur, false);
    
    for (int i = 1; i < M; ++i) {
         
        int u = mapping[i];

        if (u == -1) {
            continue;
        }

        if (nterm[i]) {
            aterm[u] = true;
        }
        
        for (const auto& e: ng[i]) {
            int v = mapping[e.first];
            ans[u].push_back({v, e.second});
        }
        
    }

    ng = std::move(ans);
    nterm = std::move(aterm);

}



answer_type determinate(const std::string& file_name) {
    
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
    std::vector<bool> nterm((1 << n), false);
    ng.resize((1 << n));

    
    bfs(g, n, term, ng, nterm);
    
    return {ng, nterm};
}
