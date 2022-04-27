#include "Instance.hpp"
#include "parser.hpp"
#include <iostream>
#include <vector>
#include "ilconcert/iloenv.h"


int main(int   argc,char *argv[])
{
  std::string file = "atlanta.txt";

  clean(file);
  Instance i = load(file);
  i.print();
  std::printf("%d",i.arcCapacity);
  i.addA();
  i.print();
  Solution* sol = i.getTrivialSolution();
  sol->print(true);
  std::cout << "\n";


}
