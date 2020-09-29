#include "determinate.cpp"
#include "min_automat.cpp"
#include "noeps.cpp"


void out(const answer_type& answer) {
    for (int j = 0; j < answer.first.size(); ++j) {
        for (const auto& e: answer.first[j]) {
            std::cout << j << ' ' << e.first << ' ' << e.second << std::endl;
        }
    }

    for (int i : answer.second) {
        std::cout << i << ' ';
    }
    
    std::cout << std::endl;
}


int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    
    auto p = get_min_automate("test.in");
    out(p);


    return 0;
}
