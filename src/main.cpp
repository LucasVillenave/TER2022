
#include "parser.hpp"
#include <iostream>
#include <vector>


int main(int   argc,char *argv[])
{
  std::vector<std::vector<int>> matrixos = {{0,1,0},{1,0,1},{0,1,0}};
  std::vector<int> demandsStart = {0,0};
  std::vector<int> demandsEnd = {1,2};
  std::vector<int> demands = {5,7};
  Instance testInstance = Instance(3,matrixos,50,100,150,2,demandsStart,demandsEnd,demands,10,40);
  testInstance.print();

  int** edges = new int* [3];
  for (int i=0;i<3;i++){
    edges[i] = new int [3];
    for (int j=0;j<3;j++){
      edges[i][j] = -1;
    }
  }
  edges [0][1] = 1;
  edges [0][2] = 1;
  edges [1][1] = 1;

  Gwrite(3,2,2,edges,demands, demandsEnd, demandsStart,"testeu.txt");

  clean("abilene.txt");
  Instance i = load("abilene.txt");
  i.print();
}
