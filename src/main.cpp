
#include "parser.hpp"
#include <iostream>


int main(int   argc,char *argv[])
{
    int** u;

    Instance *g = new Instance(12, u);
    clean("../instances/abilene.txt");
    std::cout << g->nbNodes << std::endl;

}
