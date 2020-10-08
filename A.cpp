#include "data.h"
#include "determinate.h"
#include "min_automate.h"
#include "noeps.h"


int main() {
    
    std::ifstream fin("test.in");
    Automat aut;
    fin >> aut;
    std::cout << aut;

    return 0;
}
