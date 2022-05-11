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

  // Parameters, to be changed by user

  string file = "norway.txt";

  clean(file);
  Instance* i = load(file);

  i->arcCapacity = 1000;
  int VNFCapacity = i->lowVNFCapacity;
  int kf = (i->nbNodes/10)+1;
  int kd = (i->nbDemands/2)+1;
  int TO = 300;


  // semi-auto

  unsigned long t = time(NULL);
  unsigned long timeout = t+TO;

  Solution* sol;

  sol = SP(i,VNFCapacity,0,timeout);
  if (sol==NULL || (i->check(sol,VNFCapacity)!=1) ){
    cout << "couldn't return a feasable solution"<<endl;
    return EXIT_FAILURE;
  }
  int spVal = sol->getValue();
  int spt = time(NULL)-t;
  t = time(NULL);
  timeout = t+TO;

  sol = AFRL(i,VNFCapacity,kf,timeout);
  if (sol==NULL || (i->check(sol,VNFCapacity)!=1) ){
    cout << "couldn't return a feasable solution"<<endl;
    return EXIT_FAILURE;
  }
  int LVal = sol->getValue();
  int Lt = time(NULL)-t;
  t = time(NULL);
  timeout = t+TO;

  sol = AFRA(i,VNFCapacity,kd,timeout);
  if (sol==NULL || (i->check(sol,VNFCapacity)!=1) ){
    cout << "couldn't return a feasable solution"<<endl;
    return EXIT_FAILURE;
  }
  int AVal = sol->getValue();
  int At = time(NULL)-t;
  t = time(NULL);
  timeout = t+TO;

  sol = AFRLA(i,VNFCapacity,kf,kd,timeout);
  if (sol==NULL || (i->check(sol,VNFCapacity)!=1) ){
    cout << "couldn't return a feasable solution"<<endl;
    return EXIT_FAILURE;
  }
  int LAVal = sol->getValue();
  int LAt = time(NULL)-t;

  cout << "SP exited after " << spt << "sec of treatment" << endl;
  cout << "with a value of " << spVal << endl << endl;

  cout << "A exited after " << At << "sec of treatment" << endl;
  cout << "with a value of " << AVal << endl << endl;

  cout << "L exited after " << Lt << "sec of treatment" << endl;
  cout << "with a value of " << LVal << endl << endl;

  cout << "LA exited after " << LAt << "sec of treatment" << endl;
  cout << "with a value of " << LAVal << endl << endl;

  cout << i->arcCapacity << " " << i->nbNodes << " " << i->nbDemands << endl;
}
