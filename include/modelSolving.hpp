#ifndef MODELSOLVING
#define MODELSOLVING

#include "Instance.hpp"
#include "Solution.hpp"

int generateArcCapacity(Instance* i);

// return a solution of I if feasable, IA otherwise
Solution* SPMD(Solution* sol, Instance* i, int VNFCapacity, int VNFfix, unsigned long timeoutint, int demandToCheck=-1);

Solution* SP(Instance* i, int VNFCapacity, int VNFlb, unsigned long timeout, int demandToCheck=-1,
            int kOpt=0, Solution* kOptSol=NULL, int kf=-1, int kd=-1);

#endif