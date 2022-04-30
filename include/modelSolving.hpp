#ifndef MODELSOLVING
#define MODELSOLVING

#include "Instance.hpp"
#include "Solution.hpp"

int arcCapacity(Instance* i);

Solution* SPMD(Solution* sol, Instance* i, int VNFCapacity, int VNFfix);

#endif