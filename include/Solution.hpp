#ifndef SOLUTION
#define SOLUTION
#include <vector>


class Solution{

  public:

    std::vector<bool> openVNF;
    std::vector<std::vector<bool>> useVNFforDemand;

    std::vector<std::vector<std::vector<bool>>> useEdgeForDemandStart;
    std::vector<std::vector<std::vector<bool>>> useEdgeForDemandEnd;

    Solution(std::vector<bool>  openVNF,std::vector<std::vector<bool>>  useVNFforDemand,
                       std::vector<std::vector<std::vector<bool>>>  useEdgeForDemandStart,
                       std::vector<std::vector<std::vector<bool>>>  useEdgeForDemandEnd);
    void print(bool verbose=false);
    void save();
    int getValue();
};

#endif
