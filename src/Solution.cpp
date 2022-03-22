#include "Solution.hpp"
#include <iostream>


int Solution::getValue()
{
  int value = 0;
  for(bool isVNFopen:openVNF)
  {
    if(isVNFopen){value++;}
  }
  return value;
}


Solution::Solution(std::vector<bool>  openVNF,std::vector<std::vector<bool>>  useVNFforDemand,
                   std::vector<std::vector<std::vector<bool>>>  useEdeForDemandStart,
                   std::vector<std::vector<std::vector<bool>>>  useEdeForDemandEnd)
{
  this->openVNF=openVNF;
  this->useVNFforDemand=useVNFforDemand;

  this->useEdeForDemandStart=useEdeForDemandStart;
  this->useEdeForDemandEnd=useEdeForDemandEnd;

  this->solvingTime=-1.0;
}


void Solution::print()
{
  for(int nodeIndex=0;nodeIndex<openVNF.size();nodeIndex++)
  {
    if(openVNF[nodeIndex])
    {
      std::cout << "VNF opened on node " << openVNF.size() << ":\n";

      for(int demandIndex=0;demandIndex<useVNFforDemand[0].size();demandIndex++)
      {
        if(useVNFforDemand[nodeIndex][demandIndex])
        {
          std::cout << "Used for demand " << demandIndex << "\n";
        }
      }
    }
  }
}
