#ifndef SOLUTION
#define SOLUTION
#include <vector>


class Solution{

  public:

    std::vector<bool> openVNF;
    std::vector<std::vector<bool>> useVNFforDemand;

    std::vector<std::vector<std::vector<bool>>> useEdeForDemandStart;
    std::vector<std::vector<std::vector<bool>>> useEdeForDemandEnd;

    float solvingTime;

    Solution(std::vector<bool>  openVNF,std::vector<std::vector<bool>>  useVNFforDemand,
                       std::vector<std::vector<std::vector<bool>>>  useEdeForDemandStart,
                       std::vector<std::vector<std::vector<bool>>>  useEdeForDemandEnd);
    void print();
    void save();
    int getValue();
    bool check(bool verbose);
};

#endif
