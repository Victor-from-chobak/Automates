#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <map>
#include <string>


using graph = std::vector<std::vector<std::pair<int, char> > >;

template<typename T>
void debug(const std::vector<std::vector<T> >& ar) {
    for (int i = 0; i < ar.size(); ++i) {
        for (int j = 0; j < ar[i].size(); ++j) {
            std::cout << ar[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}


std::pair<graph, std::vector<bool> > get_minimal(const graph& g, const graph& ag, const std::vector<bool>& isterm, int n) {

    std::vector<std::vector<bool> > different(n, std::vector<bool>(n, false));
    std::queue<std::pair<int, int> > q;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            different[i][j] = isterm[i] ^ isterm[j];
            different[j][i] = isterm[i] ^ isterm[j];
            if (different[i][j] ) {   
                q.push({i, j});
            }
        }
    }

    while (!q.empty() ) {
        std::pair<int, int> p = q.front();
        q.pop();
        int u = p.first;
        int v = p.second;

        for (const auto& e1: ag[u]) {
            for (const auto& e2: ag[v]) {
                
                if (e1.second != e2.second) {
                    continue;
                }

                int w1 = e1.first;
                int w2 = e2.first;

                if (!different[w1][w2]) {
                    different[w1][w2] = true;
                    different[w2][w1] = true;
                    q.push({w1, w2});
                }
            }
        }
    }

    
    std::vector<int> classes(n, -1);
    int cur = -1;

    for (int i = 0; i < n; ++i) {
        if (classes[i] > -1) {
            continue;
        }
        
        ++cur;
        classes[i] = cur;
        for (int j = 0; j < n; ++j) {
            if (classes[j] > -1) {
                continue;
            }
            
            if (different[i][j] ) {
                continue;
            }

            classes[j] = cur;
        }
    }
    

    graph ans;
    ans.resize(cur + 1);

    std::map<std::pair<int, char>, int> ma;

    for (int i = 0; i < n; ++i) {
        for (const auto& e: g[i]) {
            int c1 = classes[i];
            int c2 = classes[e.first];
            ma[{c1, e.second}] = c2;
        }
    }
    
    for (const auto& e: ma) {
        ans[e.first.first].push_back({e.second, e.first.second});
    }
        

    std::vector<bool> new_term(cur + 1, false);

    for (int j = 0; j < n; ++j) {
        int c = classes[j];
        if (isterm[j]) {
            new_term[c] = true;
        }
    }

    return {ans, new_term};
}



std::pair<graph, std::vector<bool> > get_min_automate(const std::string& file_name) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    
    freopen(file_name.c_str(), "r", stdin); 

    int n, m, t;
    std::cin >> n >> m >> t;
 
    graph g;
    graph ag;

    g.resize(n);
    ag.resize(n);
    std::vector<bool> terminal(n, false);
    
    for (int i = 0; i < m; ++i) {
        int u;
        int v;
        char c;
        std::cin >> u >> v >> c;
        
        g[u].push_back({v, c});
        ag[v].push_back({u, c});
    }
    
    for (int i = 0; i < t; ++i) {
        int x;
        std::cin >> x;
        terminal[x] = true;
    }
    
    std::pair<graph, std::vector<bool> > answer = get_minimal(g, ag, terminal, n);
    
    return answer;
}
