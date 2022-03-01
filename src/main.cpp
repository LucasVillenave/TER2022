
#include "parser.hpp"
#include <iostream>


int main(int   argc,char *argv[])
{
  std::vector<std::vector<int>> matrixos = {{0,1,0},{1,0,0},{0,0,1}};
  Instance testInstance = Instance(3,matrixos);
  testInstance.print();

}
