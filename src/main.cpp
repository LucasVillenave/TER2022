#include "Instance.hpp"
#include "parser.hpp"
#include "modelSolving.hpp"
#include <iostream>
#include <vector>


int main(int   argc,char *argv[])
{
  std::string file = "polska.txt";

  clean(file);
  Instance* i = load(file);
  // i->print();
  Instance* iA = new Instance(i->nbNodes,i->adjacencyMatrix,
              i->lowVNFCapacity,i->mediumVNFCapacity,i->highVNFCapacity,
              i->nbDemands,i->demandsStart,i->demandsEnd,i->demands,
              i->arcCapacity,i->serviceCapacity);
  iA->addA();
  iA->print();
  Solution* sol = iA->getTrivialSolution();
  // sol->print(true);
  // std::cout << iA->check(sol,iA->highVNFCapacity) << std::endl;
  // std::cout << "\n";

  // SPMD(sol,iA,iA->highVNFCapacity,iA->nbNodes);



  i->arcCapacity = 1000;
  Solution* spSol = SP(i,i->highVNFCapacity,0);

  std::cout << "return a feasible solution : " << std::endl << i->check(spSol,i->highVNFCapacity) <<std::endl;
}
