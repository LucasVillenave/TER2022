#include "Instance.hpp"
#include "parser.hpp"
#include "Solution.hpp"
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

  std::cout << "\n";

  std::vector<bool> openVNF = {false,true,false};
  std::vector<std::vector<bool>> useVNFforDemand = {{false,false},{true,true},{false,false}};
  std::vector<std::vector<std::vector<bool>>> useEdeForDemandStart = { {{false,false},{true,true},{false,false}},
                                                                       {{false,false},{false,false},{false,false}},
                                                                       {{false,false},{false,false},{false,false}}  };
  std::vector<std::vector<std::vector<bool>>> useEdeForDemandEnd = { {{false,false},{false,false},{false,false}},
                                                                      {{false,false},{false,false},{false,true}},
                                                                      {{false,false},{false,false},{false,false}}  };

  Solution sol = Solution(openVNF,useVNFforDemand,useEdeForDemandStart,useEdeForDemandEnd);
  sol.print();
  std::cout << sol.getValue()<<"\n";

  //clean("../instances/abilene.txt");
  return 1;
}
