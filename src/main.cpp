
#include "parser.hpp"
#include <iostream>


int main(int   argc,char *argv[])
{
    int** u;

    TER::Instance *g = new TER::Instance(12, u);
    TER::clean("abilene");
    std::cout << g->nbNodes << std::endl;

}
