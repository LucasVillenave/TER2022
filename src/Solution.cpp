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
                   std::vector<std::vector<std::vector<bool>>>  useEdgeForDemandStart,
                   std::vector<std::vector<std::vector<bool>>>  useEdgeForDemandEnd)
{

  this->openVNF=openVNF;
  this->useVNFforDemand=useVNFforDemand;

  this->useEdgeForDemandStart=useEdgeForDemandStart;
  
  this->useEdgeForDemandEnd=useEdgeForDemandEnd;
}


void Solution::print(bool verbose)
{
  for(int nodeIndex=0;nodeIndex<openVNF.size();nodeIndex++)
  {
    if(openVNF[nodeIndex])
    {
      std::cout << "VNF opened on node " << nodeIndex << ":\n";

      for(int demandIndex=0;demandIndex<useVNFforDemand[0].size();demandIndex++)
      {
        if(useVNFforDemand[nodeIndex][demandIndex])
        {
          std::cout << "Used for demand " << demandIndex << "\n";
        }
      }
    }
  }
  if (verbose == true){
    int nNodes = openVNF.size();
    int nDemand = useEdgeForDemandStart[0][0].size();
    for (int i=0;i<nNodes;i++){
      for (int j=0;j<nNodes;j++){
        for (int k=0;k<nDemand;k++){
          if(useEdgeForDemandStart[i][j][k]){
            std::cout << "edge " << i << " to " << j << " used on demand " << k << " for demand start" << std::endl;
          }
          if(useEdgeForDemandEnd[i][j][k]){
            std::cout << "edge " << i << " to " << j << " used on demand " << k << " for demand end" << std::endl;
          }
        }
      }
    }
  }
}
