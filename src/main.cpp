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

  i->arcCapacity = 2000;

  // i->print();

  Instance* iA = new Instance(i->nbNodes,i->adjacencyMatrix,
              i->lowVNFCapacity,i->mediumVNFCapacity,i->highVNFCapacity,
              i->nbDemands,i->demandsStart,i->demandsEnd,i->demands,
              i->arcCapacity,i->serviceCapacity);
  iA->addA();

  // iA->print();

  Solution* sol = iA->getTrivialSolution();
  sol->print(true);
  std::cout << iA->check(sol,iA->highVNFCapacity) << std::endl;
  std::cout << std::endl;

  Solution* SPMDSol = SPMD(sol,iA,iA->highVNFCapacity,iA->nbNodes,12);

  int kf = (i->nbNodes/10)+1;
  
  std::cout <<std::endl << "solution found, ameliorating" <<std::endl <<std::endl;

  int tmpVal = SPMDSol->getValue();
  Solution* spSol = SP(i,i->highVNFCapacity,0,12,1,kf,SPMDSol);
  while(tmpVal>spSol->getValue()){
    tmpVal = spSol->getValue();
    spSol = SP(i,i->highVNFCapacity,0,12,1,kf,spSol);
  }

  std::cout << "return a feasible solution : " << std::endl << i->check(spSol,i->highVNFCapacity) <<std::endl;
}
