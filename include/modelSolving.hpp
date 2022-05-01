#ifndef MODELSOLVING
#define MODELSOLVING

#include "Instance.hpp"
#include "Solution.hpp"

int generateArcCapacity(Instance* i);

Solution* SPMD(Solution* sol, Instance* i, int VNFCapacity, int VNFfix);

Solution* SP(Instance* i, int VNFCapacity, int VNFlb);

#endif