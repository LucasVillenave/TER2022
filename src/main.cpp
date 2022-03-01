
#include "parser.hpp"
#include <iostream>


int main(int   argc,char *argv[])
{
    int** u;

    TER::graph *g = new TER::graph(12, u);
    
    std::cout << g->getN() << std::endl;

}