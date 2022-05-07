#ifndef MODELSOLVING
#define MODELSOLVING

#include "Instance.hpp"
#include "Solution.hpp"

int generateArcCapacity(Instance* i);

// return a solution of I if feasable, IA otherwise
Solution* SPMD(Solution* sol, Instance* i, int VNFCapacity, int VNFfix, int demandToCheck);

Solution* SP(Instance* i, int VNFCapacity, int VNFlb, int demandToCheck, int kOpt=0, int kf=0, Solution* kOptSol=NULL);

#endif