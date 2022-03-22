#include "Instance.hpp"
#include "parser.hpp"
#include "Solution.hpp"
#include <iostream>
#include <vector>


int main(int   argc,char *argv[])
{


  // std::vector<std::vector<int>> matrixos = {{0,1,0},{1,0,1},{0,1,0}};
  // std::vector<int> demandsStart = {0,0};
  // std::vector<int> demandsEnd = {1,2};
  // std::vector<int> demands = {5,7};
  // Instance testInstance = Instance(3,matrixos,50,100,150,2,demandsStart,demandsEnd,demands,10,40);
  // testInstance.print();

  // int** edges = new int* [3];
  // for (int i=0;i<3;i++){
  //   edges[i] = new int [3];
  //   for (int j=0;j<3;j++){
  //     edges[i][j] = -1;
  //   }
  // }
  // edges [0][1] = 1;
  // edges [0][2] = 1;
  // edges [1][1] = 1;

  // Gwrite(3,2,2,edges,demands, demandsEnd, demandsStart,"testeu.txt");

  // std::vector<bool> openVNF = {false,true,false};
  // std::vector<std::vector<bool>> useVNFforDemand = {{false,false},{true,true},{false,false}};
  // std::vector<std::vector<std::vector<bool>>> useEdeForDemandStart = { {{false,false},{true,true},{false,false}},
  //                                                                      {{false,false},{false,false},{false,false}},
  //                                                                      {{false,false},{false,false},{false,false}}  };
  // std::vector<std::vector<std::vector<bool>>> useEdeForDemandEnd = { {{false,false},{false,false},{false,false}},
  //                                                                     {{false,false},{false,false},{false,true}},
  //                                                                     {{false,false},{false,false},{false,false}}  };

  // Solution sol = Solution(openVNF,useVNFforDemand,useEdeForDemandStart,useEdeForDemandEnd);
  // sol.print();
  // std::cout << sol.getValue()<<"\n";
  // return 1;



  std::string file = "atlanta.txt";

  std::cout << std::endl <<"my fking problem" << std::endl<< std::endl;
  clean(file);
  std::cout << std::endl <<"nearly not my fking problem" << std::endl<< std::endl;
  Instance i = load(file);
  std::cout << std::endl <<"not my fking problem" << std::endl<< std::endl;
  i.print();
  std::cout << "\n";


}
