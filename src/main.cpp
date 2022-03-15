
#include "parser.hpp"
#include <iostream>


int main(int   argc,char *argv[])
{
  std::vector<std::vector<int>> matrixos = {{0,1,0},{1,0,1},{0,1,0}};
  std::vector<int> demandsStart = {0,0};
  std::vector<int> demandsEnd = {1,2};
  std::vector<int> demands = {5,7};
  Instance testInstance = Instance(3,matrixos,50,100,150,2,demandsStart,demandsEnd,demands,10,40);
  testInstance.print();

  //clean("../instances/abilene.txt");
}
