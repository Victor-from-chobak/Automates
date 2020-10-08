#include <gtest/gtest.h>
#include "data.h"
#include "min_automate.h"
#include "noeps.h"
#include "determinate.h"

Automat get_data(std::string& file_name) {
    Automat answer;
    std::ifstream fin(file_name.c_str());
    fin >> answer;
    return answer;
}


TEST(min_test1, simple_test) {
    std::string file_name = "./tests/min_test1.in";
    Automat aut = get_min_automate(get_data(file_name));
    int states = 2;
    int edges_amount = 2;
    int terminal_amount = 1;
    Graph graph = {{{1, 'a'}}, {{1, 'a'}}} ;
    std::vector<bool> term = {0, 1};
    
    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}

TEST(min_test2, nothing_to_do_test) {
   
    std::string file_name = "./tests/min_test2.in";
    Automat aut = get_min_automate(get_data(file_name));
    Graph graph = {{{1, 'a'}, {1, 'b'}}, {{1, 'a'}, {1, 'b'}}};
    std::vector<bool> term = {0, 1};

    int states = 2;
    int edges_amount = 4;
    int terminal_amount = 1;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}

TEST(min_test3, full_graph_test) {
    
    std::string file_name = "./tests/min_test3.in";
    Automat aut = get_min_automate(get_data(file_name));
    Graph graph = {{{1, 'a'}, {0, 'b'}}, {{1, 'a'}, {0, 'b'}}};
    std::vector<bool> term = {0, 1};

    int states = 2;
    int edges_amount = 4;
    int terminal_amount = 1;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}

TEST(min_test4, small_fda) {

    std::string file_name = "./tests/min_test4.in";
    Automat aut = get_min_automate(get_data(file_name));
    Graph graph = {{{0, 'a'}, {1, 'b'} }, {{2, 'a'}, {1, 'b'}}, {{0, 'a'}, {3, 'b'}}, {{3, 'a'}, {3, 'b'}}};
    std::vector<bool> term = {0, 0, 0, 1};
    
    int states = 4;
    int edges_amount = 8;
    int terminal_amount = 1;
    
    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}

TEST(min_test5, good_fda) {

    std::string file_name = "./tests/min_test5.in";
    Automat aut = get_min_automate(get_data(file_name));
    Graph graph = {{{1, 'a'}, {0, 'b'} }, {{1, 'a'}, {2, 'b'}}, {{2, 'a'}, {3, 'b'}}, {{0, 'a'}, {2, 'b'}}};
    std::vector<bool> term = {0, 0, 1, 1};
    
    int states = 4;
    int edges_amount = 8;
    int terminal_amount = 2;
    
    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}


TEST(noeps_test1, simple_test) {

    std::string file_name = "./tests/noeps_test1.in";
    Automat aut = get_noeps(get_data(file_name));
    Graph graph = { {} };
    std::vector<bool> term = {1};
    
    int states = 1;
    int edges_amount = 0;
    int terminal_amount = 1;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}

TEST(noeps_test2, adding_edge_and_terminate) {

    std::string file_name = "./tests/noeps_test2.in";
    Automat aut = get_noeps(get_data(file_name));
    Graph graph = {{ {1, 'a'}, {2, 'b'} }, {{3, 'a'} }, { {4, 'c'} }, {}, {} };
    std::vector<bool> term = {0, 1, 0, 0, 1};
    
    int states = 5;
    int edges_amount = 4;
    int terminal_amount = 2;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(answer, aut);
}

TEST(noeps_test3, only_one_normal_edge) {

    std::string file_name = "./tests/noeps_test3.in";
    Automat aut = get_noeps(get_data(file_name));
    Graph graph = { { {1, 'a'} }, {} } ;
    std::vector<bool> term = {1, 0};

    int states = 2;
    int edges_amount = 1;
    int terminal_amount = 1;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}

TEST(noeps_test4, wihout_eps_edges) {
    std::string file_name = "./tests/det_test3.in";
    Automat aut = get_noeps(get_data(file_name));
    Graph graph = { {{0, 'a'}, {1, 'a'}, {2, 'a'}}, {{3, 'b'}}, {{3, 'b'}}, {{3, 'a'}, {4, 'a'}}, {{1, 'a'}, {5, 'b'}}, {{3, 'b'}} };
    std::vector<bool> term = {0, 0, 1, 0, 0, 1};

    int states = 6;
    int edges_amount = 10;
    int terminal_amount = 2;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}

TEST(noeps_test5, good_test_with_reduced_vertex) {
    
    std::string file_name = "./tests/noeps_test4.in";
    Automat aut = get_noeps(get_data(file_name));
    Graph graph = { {{0, 'a'}, {1, 'b'}, {2, 'a'}, {2, 'b'}, {3, 'b'}}, {{0, 'a'}, {1, 'b'}, {2, 'a'}, {2, 'b'}, {3, 'b'}}, {{0, 'a'}, {2, 'a'}, {2, 'b'}, {3, 'b'}}, {{2, 'a'}} };
    std::vector<bool> term = {1, 1, 1, 1};

    int states = 4;
    int edges_amount = 15;
    int terminal_amount = 4;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}


TEST(det_test1, simple_test) {

    std::string file_name = "./tests/det_test1.in";
    Automat aut = determinate(get_data(file_name));
    Graph graph = { { {1, 'a'} }, {{1, 'b'} } } ;
    std::vector<bool> term = {0, 1};

    int states = 2;
    int edges_amount = 2;
    int terminal_amount = 1;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}


TEST(det_test2, already_determined) {

    std::string file_name = "./tests/det_test2.in";
    Automat aut = determinate(get_data(file_name));
    Graph graph = { { {1, 'a'}, {2, 'b'}}, {{0, 'a'}, {2, 'b'}}, {{3, 'a'}}, {{1, 'a'}, {2, 'b'} }};
    std::vector<bool> term = {0, 1, 1, 0};
    
    int states = 4;
    int edges_amount = 7;
    int terminal_amount = 2;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}


TEST(det_test3, random_nka) {

    std::string file_name = "./tests/det_test3.in";
    Automat aut = determinate(get_data(file_name));
    Graph graph = { { {1, 'a'} }, {{1, 'a'}, {2, 'b'}}, {{3, 'a'}}, {{4, 'a'}, {5, 'b'}}, {{4, 'a'}, {6, 'b'}}, {{2, 'b'}}, {{3, 'a'}, {2, 'b'}} };
    std::vector<bool> term = {0, 1, 0, 0, 0, 1, 1};
    
    int states = 7;
    int edges_amount = 11;
    int terminal_amount = 3;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}

TEST(det_test4, random_nka) {

    std::string file_name = "./tests/det_test4.in";
    Automat aut = determinate(get_data(file_name));
    Graph graph = { { {1, 'a'}, {2, 'b'} }, { {1, 'a'}, {2, 'b'} }, { {3, 'a'} },{ {4, 'a'}, {5, 'b'}}, {{3, 'a'}}, {{4, 'a'}, {2, 'b'}} };
    std::vector<bool> term = {0, 0, 1, 1, 1, 0};
    
    int states = 6;
    int edges_amount = 10;
    int terminal_amount = 3;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}

TEST(det_test5, exponential_growth) {

    std::string file_name = "./tests/det_test5.in";
    Automat aut = determinate(get_data(file_name));
    Graph graph = { { {1, 'a'}, {0, 'b'} }, { {2, 'a'}, {3, 'b'} }, { {4, 'a'}, {5, 'b'} }, { {6, 'a'}, {7, 'b'} }, { {4, 'a'}, {5, 'b'} }, 
                { {6, 'a'}, {7, 'b'} }, { {2, 'a'}, {3, 'b'} }, { {1, 'a'}, {0, 'b'} } };
    
    std::vector<bool> term = {0, 0, 0, 0, 1, 1, 1, 1};
    
    int states = 8;
    int edges_amount = 16;
    int terminal_amount = 4;

    Automat answer(states, edges_amount, terminal_amount, graph, term);

    EXPECT_EQ(aut, answer);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


