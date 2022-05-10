#include "Instance.hpp"
#include "parser.hpp"
#include "modelSolving.hpp"
#include "metaHeuristics.hpp"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;



int main(int   argc,char *argv[])
{
  string file = "france.txt";

  clean(file);
  Instance* i = load(file);

  i->arcCapacity = i->lowVNFCapacity/2;
  int VNFCapacity = i->highVNFCapacity;
  int kf = (i->nbNodes/10)+1;
  int kd = (i->nbDemands/2)+1;

  unsigned long t = time(NULL);
  unsigned long timeout = t+120;

  Solution* sol = AFRL(i,VNFCapacity,kf,timeout);
  // Solution* sol = AFRLA(i,VNFCapacity,kf,kd,timeout);

  cout << "program exited after " << time(NULL)-t << "sec of treatment" << endl;

  if (sol==NULL || (i->check(sol,VNFCapacity)!=1) ){
    cout << "couldn't return a feasable solution"<<endl;
  }else{
    cout << "returning a solution of value " << sol->getValue() <<endl;
  }
}
