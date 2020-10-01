#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <queue>
#pragma once

class edge {

public:
    int to = 0;
    char letter = 'a';
    
    edge(int v, char c) : to(v), letter(c) {}
    edge(const edge& other) : to(other.to), letter(other.letter) {}

    edge& operator=(const edge& other) {
        to = other.to;
        letter = other.letter;
        return *this;
    }

    edge(const std::pair<int, char>& other) : to(other.first), letter(other.second) {}

    bool operator==(const edge& other) const {
        return ((to == other.to) && (letter == other.letter));
    }

};


class comp_for_edges {

public:

    comp_for_edges() = default;
    
    bool operator ()(const edge& x, const edge& y) {
        return ((x.to < y.to) || ((x.to == y.to) && (x.letter < y.letter)));
    }

};

using Graph = std::vector<std::vector<edge> >;

std::istream& operator>>(std::istream& in, edge& object) {
    in >> object.to >> object.letter;
    return in;
}

std::ostream& operator<<(std::ostream& out, const edge& object) {
    out << object.to << ' ' << object.letter << '\n';
    return out;
}

class automat {

public:

    static const int DEFAULT = -1;
    
    Graph graph = {};
    std::vector<bool> terminal = {};
    int n = 0; //states 
    int m = 0; // edges
    int t = 0; //termial

    automat() = default;
    automat(int _q, int _m, int _t, const Graph& g, const std::vector<bool>& term) : n(_q), m(_m), t(_t), graph(g), terminal(term) {}
    automat(const automat& other) : n(other.n), m(other.m), t(other.t), graph(other.graph), terminal(other.terminal) {}
    automat(automat&& other) : n(other.n), m(other.m), t(other.t), graph(std::move(other.graph)), terminal(std::move(other.terminal)) {
        other.n = 0;
        other.m = 0;
        other.t = 0;
    }
    automat& operator=(const automat& other) {
        graph = other.graph;
        terminal = other.terminal;
        n = other.n;
        m = other.m;
        t = other.t;
        return *this;
    }
    automat& operator=(automat&& other) {
        graph = std::move(other.graph);
        terminal = std::move(other.terminal);
        n = other.n;
        m = other.m;
        t = other.t;
        other.n = 0;
        other.m = 0;
        other.t = 0;
        return *this;
    }

    bool operator==(const automat& other) const {
        return ((n == other.n) && (m == other.m) && (t == other.t) && (graph == other.graph) && (terminal == other.terminal));
    }

    void resize(int q) {
        n = q;
        graph.resize(q);
        terminal.resize(q, false);
    }
    
    template<typename Edge>
    void add_edge(int vertex, Edge&& edge) {
        ++m;
        graph[vertex].push_back(std::forward<Edge>(edge));
    }

    void add_terminal(int vertex) {
        ++t;
        terminal[vertex] = true;
    }

    void renumber();

};

std::istream& operator>>(std::istream& in, automat& A) {
    in >> A.n >> A.m >> A.t;
    A.resize(A.n);
    
    for (int j = 0; j < A.m; ++j) {
        int u, v;
        char c;
        in >> u >> v >> c;

        A.graph[u].push_back({v, c});
    }


    for (int i = 0; i < A.n; ++i) {
        int x;
        in >> x;
        A.terminal[x] = true;
    }
    
    return in;
}

std::ostream& operator<<(std::ostream& out, const automat& A) {
    
    std::cout << A.n << ' ' << A.m << ' ' << A.t << '\n';

    out << "EDGES\n";

    for (int i = 0; i < A.n; ++i) {
        for (const edge& edge: A.graph[i]) {
            out << i << ' ' << edge.to << ' ' << edge.letter << '\n';
        }
    }
    
    out << "TERMINAL\n";

    for (int i = 0; i < A.n; ++i) {
        out << A.terminal[i] << ' ';
    }

    out << '\n';

    return out;
}


void automat::renumber() {
    int new_number = 0;
    std::vector<bool> was(n);
    std::queue<int> queue;
    std::vector<int> mapping(n, static_cast<int>(DEFAULT)); // new numbers

    queue.push(0);
    was[0] = true;
    
    //simple bfs

    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        mapping[vertex] = new_number;
        ++new_number;

        for (const edge& edge: graph[vertex]) {
            if (was[edge.to]) {
                continue;
            }

            was[edge.to] = true;
            queue.push(edge.to);
        }
   
    }
    
    automat new_automat;
    new_automat.resize(new_number);
    
    for (int j = 0; j < n; ++j) {
        int vertex = mapping[j];
        
        if (vertex == DEFAULT) {
            continue;
        }

        if (terminal[j]) {
            new_automat.add_terminal(vertex);
        }

        for (const edge& e: graph[j]) {
            
            int other = mapping[e.to];
            char letter = e.letter;
            edge new_e(other, letter);
            
            if (other == DEFAULT) {
                continue;
            }

            new_automat.add_edge(vertex, new_e);
        }
    }
    
    *this = (new_automat);

}


