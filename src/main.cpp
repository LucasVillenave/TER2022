#include "Instance.cpp"
#include "parser.hpp"
#include <iostream>
#include <vector>


int main(int   argc,char *argv[])
{
  std::string file = "polska.txt";

  clean(file);
  Instance i = load(file);
  i.print();
  std::printf("%d",i.arcCapacity);
  Instance iA = (* new Instance(i.nbNodes,i.adjacencyMatrix,
              i.lowVNFCapacity,i.mediumVNFCapacity,i.highVNFCapacity,
              i.nbDemands,i.demandsStart,i.demandsEnd,i.demands,
              i.arcCapacity,i.serviceCapacity));
  iA.addA();
  iA.print();
  Solution* sol = iA.getTrivialSolution();
  sol->print(true);
  std::cout << iA.check(sol,iA.highVNFCapacity) << std::endl;
  std::cout << "\n";


}
