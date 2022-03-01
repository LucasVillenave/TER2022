
#include "parser.hpp"
#include <iostream>


int main(int   argc,char *argv[])
{
    int** u;

    TER::graph *g = new TER::graph(12, u);
    TER::clean("abilene");
    std::cout << g->getN() << std::endl;

}