#include <gtest/gtest.h>
#include "data.h"
#include "min_automate.h"
#include "noeps.h"
#include "determinate.h"

automat get_data(std::string& file_name) {
    automat answer;
    std::ifstream fin(file_name.c_str());
    fin >> answer;
    return answer;
}


TEST(min_test1, simple_test) {
    std::string file_name = "./tests/min_test1.in";
    automat aut = get_min_automate(get_data(file_name));
    int n = 2;
    int m = 2;
    int t = 1;
    Graph g = {{{1, 'a'}}, {{1, 'a'}}} ;
    std::vector<bool> term = {0, 1};
    
    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}

TEST(min_test2, nothing_to_do_test) {
   
    std::string file_name = "./tests/min_test2.in";
    automat aut = get_min_automate(get_data(file_name));
    Graph g = {{{1, 'a'}, {1, 'b'}}, {{1, 'a'}, {1, 'b'}}};
    std::vector<bool> term = {0, 1};

    int n = 2;
    int m = 4;
    int t = 1;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}

TEST(min_test3, full_graph_test) {
    
    std::string file_name = "./tests/min_test3.in";
    automat aut = get_min_automate(get_data(file_name));
    Graph g = {{{1, 'a'}, {0, 'b'}}, {{1, 'a'}, {0, 'b'}}};
    std::vector<bool> term = {0, 1};

    int n = 2;
    int m = 4;
    int t = 1;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}

TEST(min_test4, small_fda) {

    std::string file_name = "./tests/min_test4.in";
    automat aut = get_min_automate(get_data(file_name));
    Graph g = {{{0, 'a'}, {1, 'b'} }, {{2, 'a'}, {1, 'b'}}, {{0, 'a'}, {3, 'b'}}, {{3, 'a'}, {3, 'b'}}};
    std::vector<bool> term = {0, 0, 0, 1};
    
    int n = 4;
    int m = 8;
    int t = 1;
    
    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}

TEST(min_test5, good_fda) {

    std::string file_name = "./tests/min_test5.in";
    automat aut = get_min_automate(get_data(file_name));
    Graph g = {{{1, 'a'}, {0, 'b'} }, {{1, 'a'}, {2, 'b'}}, {{2, 'a'}, {3, 'b'}}, {{0, 'a'}, {2, 'b'}}};
    std::vector<bool> term = {0, 0, 1, 1};
    
    int n = 4;
    int m = 8;
    int t = 2;
    
    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}


TEST(noeps_test1, simple_test) {

    std::string file_name = "./tests/noeps_test1.in";
    automat aut = get_noeps(get_data(file_name));
    Graph g = { {} };
    std::vector<bool> term = {1};
    
    int n = 1;
    int m = 0;
    int t = 1;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}

TEST(noeps_test2, adding_edge_and_terminate) {

    std::string file_name = "./tests/noeps_test2.in";
    automat aut = get_noeps(get_data(file_name));
    Graph g = {{ {1, 'a'}, {2, 'b'} }, {{3, 'a'} }, { {4, 'c'} }, {}, {} };
    std::vector<bool> term = {0, 1, 0, 0, 1};
    
    int n = 5;
    int m = 4;
    int t = 2;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(answer, aut);
}

TEST(noeps_test3, only_one_normal_edge) {

    std::string file_name = "./tests/noeps_test3.in";
    automat aut = get_noeps(get_data(file_name));
    Graph g = { { {1, 'a'} }, {} } ;
    std::vector<bool> term = {1, 0};

    int n = 2;
    int m = 1;
    int t = 1;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}

TEST(noeps_test4, wihout_eps_edges) {
    std::string file_name = "./tests/det_test3.in";
    automat aut = get_noeps(get_data(file_name));
    Graph g = { {{0, 'a'}, {1, 'a'}, {2, 'a'}}, {{3, 'b'}}, {{3, 'b'}}, {{3, 'a'}, {4, 'a'}}, {{1, 'a'}, {5, 'b'}}, {{3, 'b'}} };
    std::vector<bool> term = {0, 0, 1, 0, 0, 1};

    int n = 6;
    int m = 10;
    int t = 2;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}

TEST(noeps_test5, good_test_with_reduced_vertex) {
    
    std::string file_name = "./tests/noeps_test4.in";
    automat aut = get_noeps(get_data(file_name));
    Graph g = { {{0, 'a'}, {1, 'b'}, {2, 'a'}, {2, 'b'}, {3, 'b'}}, {{0, 'a'}, {1, 'b'}, {2, 'a'}, {2, 'b'}, {3, 'b'}}, {{0, 'a'}, {2, 'a'}, {2, 'b'}, {3, 'b'}}, {{2, 'a'}} };
    std::vector<bool> term = {1, 1, 1, 1};

    int n = 4;
    int m = 15;
    int t = 4;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}


TEST(det_test1, simple_test) {

    std::string file_name = "./tests/det_test1.in";
    automat aut = determinate(get_data(file_name));
    Graph g = { { {1, 'a'} }, {{1, 'b'} } } ;
    std::vector<bool> term = {0, 1};

    int n = 2;
    int m = 2;
    int t = 1;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}


TEST(det_test2, already_determined) {

    std::string file_name = "./tests/det_test2.in";
    automat aut = determinate(get_data(file_name));
    Graph g = { { {1, 'a'}, {2, 'b'}}, {{0, 'a'}, {2, 'b'}}, {{3, 'a'}}, {{1, 'a'}, {2, 'b'} }};
    std::vector<bool> term = {0, 1, 1, 0};
    
    int n = 4;
    int m = 7;
    int t = 2;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}


TEST(det_test3, random_nka) {

    std::string file_name = "./tests/det_test3.in";
    automat aut = determinate(get_data(file_name));
    Graph g = { { {1, 'a'} }, {{1, 'a'}, {2, 'b'}}, {{3, 'a'}}, {{4, 'a'}, {5, 'b'}}, {{4, 'a'}, {6, 'b'}}, {{2, 'b'}}, {{3, 'a'}, {2, 'b'}} };
    std::vector<bool> term = {0, 1, 0, 0, 0, 1, 1};
    
    int n = 7;
    int m = 11;
    int t = 3;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}

TEST(det_test4, random_nka) {

    std::string file_name = "./tests/det_test4.in";
    automat aut = determinate(get_data(file_name));
    Graph g = { { {1, 'a'}, {2, 'b'} }, { {1, 'a'}, {2, 'b'} }, { {3, 'a'} },{ {4, 'a'}, {5, 'b'}}, {{3, 'a'}}, {{4, 'a'}, {2, 'b'}} };
    std::vector<bool> term = {0, 0, 1, 1, 1, 0};
    
    int n = 6;
    int m = 10;
    int t = 3;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}

TEST(det_test5, exponential_growth) {

    std::string file_name = "./tests/det_test5.in";
    automat aut = determinate(get_data(file_name));
    Graph g = { { {1, 'a'}, {0, 'b'} }, { {2, 'a'}, {3, 'b'} }, { {4, 'a'}, {5, 'b'} }, { {6, 'a'}, {7, 'b'} }, { {4, 'a'}, {5, 'b'} }, 
                { {6, 'a'}, {7, 'b'} }, { {2, 'a'}, {3, 'b'} }, { {1, 'a'}, {0, 'b'} } };
    
    std::vector<bool> term = {0, 0, 0, 0, 1, 1, 1, 1};
    
    int n = 8;
    int m = 16;
    int t = 4;

    automat answer(n, m, t, g, term);

    EXPECT_EQ(aut, answer);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


