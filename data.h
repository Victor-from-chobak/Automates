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
    
    edge(int construct_to, char construct_letter) : to(construct_to), letter(construct_letter) {}
    edge(const edge& other) : to(other.to), letter(other.letter) {}

    edge& operator=(const edge& other) {
        to = other.to;
        letter = other.letter;
        return *this;
    }

    edge(const std::pair<int, char>& other) : to(other.first), letter(other.second) {}

    bool operator==(const edge& other) const {
        return (to == other.to && letter == other.letter);
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

class Automat {

public:

    static const int DEFAULT = -1;
    
    Graph graph = {};
    std::vector<bool> terminal = {};
    int states = 0;
    int edges_amount = 0;
    int terminal_amount = 0;

    Automat() = default;
    void swap(Automat& other) noexcept {
        std::swap(states, other.states);
        std::swap(edges_amount, other.edges_amount);
        std::swap(terminal_amount, other.terminal_amount);
        std::swap(graph, other.graph);
        std::swap(terminal, other.terminal);
    }

    Automat(int _states, int _edges_amount, int _terminal_amount, const Graph& _graph, const std::vector<bool>& term) : 
           states(_states), edges_amount(_edges_amount), terminal_amount(_terminal_amount), graph(_graph), terminal(term) {}

    Automat(const Automat& other) : 
            states(other.states), edges_amount(other.edges_amount), terminal_amount(other.terminal_amount), 
            graph(other.graph), terminal(other.terminal) {}

    Automat(Automat&& other) : 
        states(other.states), edges_amount(other.edges_amount), terminal_amount(other.terminal_amount), 
        graph(std::move(other.graph)), terminal(std::move(other.terminal)) {

        other.states = 0;
        other.edges_amount = 0;
        other.terminal_amount = 0;
    }

    Automat& operator=(const Automat& other) {
        
        if (this != &other) {
            Automat(other).swap(*this);
        }

        return *this;
    }

    Automat& operator=(Automat&& other) {
        
        if (this != &other) {
            Automat(std::move(other)).swap(*this);
        }

        return *this;
    }

    bool operator==(const Automat& other) const {
        return ((states == other.states) && (edges_amount == other.edges_amount) && (terminal_amount == other.terminal_amount)
                && (graph == other.graph) && (terminal == other.terminal));
    }

    void resize(int new_states_number) {
        states = new_states_number;
        graph.resize(new_states_number);
        terminal.resize(new_states_number, false);
    }
    
    template<typename Edge>
    void add_edge(int vertex, Edge&& edge) {
        ++edges_amount;
        graph[vertex].push_back(std::forward<Edge>(edge));
    }

    void add_terminal(int vertex) {
        ++terminal_amount;
        terminal[vertex] = true;
    }

    void renumber_vertexes();

};

std::istream& operator>>(std::istream& in, Automat& automata) {
    in >> automata.states >> automata.edges_amount >> automata.terminal_amount;
    automata.resize(automata.states);
    
    for (int j = 0; j < automata.edges_amount; ++j) {
        int from;
        int to;
        char letter;
        in >> from >> to >> letter;

        automata.graph[from].push_back({to, letter});
    }

    for (int i = 0; i < automata.terminal_amount; ++i) {
        int vertex;
        in >> vertex;
        automata.terminal[vertex] = true;
    }
    
    return in;
}

std::ostream& operator<<(std::ostream& out, const Automat& automata) {
    
    std::cout << automata.states << ' ' << automata.edges_amount << ' ' << automata.terminal_amount << '\n';

    out << "EDGES\n";

    for (int i = 0; i < automata.states; ++i) {
        for (const edge& edge: automata.graph[i]) {
            out << i << ' ' << edge.to << ' ' << edge.letter << '\n';
        }
    }
    
    out << "TERMINAL\n";

    for (int i = 0; i < automata.states; ++i) {
        out << automata.terminal[i] << ' ';
    }

    out << '\n';

    return out;
}


void Automat::renumber_vertexes() {
    int new_number = 0;
    std::vector<bool> was(states);
    std::queue<int> queue;
    std::vector<int> mapping(states, static_cast<int>(DEFAULT)); // new numbers

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
    
    Automat new_Automat;
    new_Automat.resize(new_number);
    
    for (int node = 0; node < states; ++node) {
        int vertex = mapping[node];
        
        if (vertex == DEFAULT) {
            continue;
        }

        if (terminal[node]) {
            new_Automat.add_terminal(vertex);
        }

        for (const edge& current_edge: graph[node]) {
            
            int other = mapping[current_edge.to];
            char letter = current_edge.letter;
            edge new_edge(other, letter);
            
            if (other == DEFAULT) {
                continue;
            }

            new_Automat.add_edge(vertex, new_edge);
        }
    }
    
    *this = (new_Automat);

}

