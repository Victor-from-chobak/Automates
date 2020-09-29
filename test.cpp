#include <gtest/gtest.h>
#include "min_automat.cpp"
#include "noeps.cpp"
#include "determinate.cpp"

TEST(min_test1, simple_test) {
    std::string file_name = "./tests/min_test1.in";
    auto p = get_min_automate(file_name);
    graph g = {{{1, 'a'}}, {{1, 'a'}}} ;
    std::vector<bool> term = {0, 1};
    
    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}

TEST(min_test2, nothing_to_do_test) {
   
    std::string file_name = "./tests/min_test2.in";
    auto p = get_min_automate(file_name);
    graph g = {{{1, 'a'}, {1, 'b'}}, {{1, 'a'}, {1, 'b'}}};
    std::vector<bool> term = {0, 1};

    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}

TEST(min_test3, full_graph_test) {
    
    std::string file_name = "./tests/min_test3.in";
    auto p = get_min_automate(file_name);
    graph g = {{{1, 'a'}, {0, 'b'}}, {{1, 'a'}, {0, 'b'}}};
    std::vector<bool> term = {0, 1};

    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}

TEST(min_test4, small_fda) {

    std::string file_name = "./tests/min_test4.in";
    auto p = get_min_automate(file_name);
    graph g = {{{0, 'a'}, {1, 'b'} }, {{2, 'a'}, {1, 'b'}}, {{0, 'a'}, {3, 'b'}}, {{3, 'a'}, {3, 'b'}}};
    std::vector<bool> term = {0, 0, 0, 1};

    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}

TEST(noeps_test1, simple_test) {

    std::string file_name = "./tests/noeps_test1.in";
    auto p = get_noeps(file_name);
    graph g = { {} };
    std::vector<bool> term = {1};


    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}

TEST(noeps_test2, adding_edge_and_terminate) {

    std::string file_name = "./tests/noeps_test2.in";
    auto p = get_noeps(file_name);
    graph g = {{ {1, 'a'}, {2, 'b'} }, {{3, 'a'} }, { {4, 'c'} }, {}, {} };
    std::vector<bool> term = {0, 1, 0, 0, 1};


    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}

TEST(noeps_test3, only_one_normal_edge) {

    std::string file_name = "./tests/noeps_test3.in";
    auto p = get_noeps(file_name);
    graph g = { { {1, 'a'} }, {} } ;
    std::vector<bool> term = {1, 0};

    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}

TEST(noeps_test4, wihout_eps_edges) {
    std::string file_name = "./tests/det_test3.in";
    auto p = get_noeps(file_name);
    graph g = { {{0, 'a'}, {1, 'a'}, {2, 'a'}}, {{3, 'b'}}, {{3, 'b'}}, {{3, 'a'}, {4, 'a'}}, {{1, 'a'}, {5, 'b'}}, {{3, 'b'}} };
    std::vector<bool> term = {0, 0, 1, 0, 0, 1};

    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}


TEST(det_test1, simple_test) {

    std::string file_name = "./tests/det_test1.in";
    auto p = determinate(file_name);
    graph g = { { {1, 'a'} }, {{1, 'b'} } } ;
    std::vector<bool> term = {0, 1};

    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}


TEST(det_test2, already_determined) {

    std::string file_name = "./tests/det_test2.in";
    auto p = get_noeps(file_name);
    graph g = { { {1, 'a'}, {2, 'b'}}, {{0, 'a'}, {2, 'b'}}, {{3, 'a'}}, {{1, 'a'}, {2, 'b'} }};
    std::vector<bool> term = {0, 1, 1, 0};

    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}


TEST(det_test3, random_nka) {

    std::string file_name = "./tests/det_test3.in";
    auto p = determinate(file_name);
    graph g = { { {1, 'a'} }, {{1, 'a'}, {2, 'b'}}, {{3, 'a'}}, {{4, 'a'}, {5, 'b'}}, {{4, 'a'}, {6, 'b'}}, {{2, 'b'}}, {{3, 'a'}, {2, 'b'}} };
    std::vector<bool> term = {0, 1, 0, 0, 0, 1, 1};


    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}

TEST(det_test4, random_nka) {

    std::string file_name = "./tests/det_test4.in";
    auto p = determinate(file_name);
    graph g = { { {1, 'a'}, {2, 'b'} }, { {1, 'a'}, {2, 'b'} }, { {3, 'a'} },{ {4, 'a'}, {5, 'b'}}, {{3, 'a'}}, {{4, 'a'}, {2, 'b'}} };
    std::vector<bool> term = {0, 0, 1, 1, 1, 0};


    EXPECT_EQ(p.first, g);
    EXPECT_EQ(p.second, term);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

