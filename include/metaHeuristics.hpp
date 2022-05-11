#ifndef MeHe
#define MeHe

#include "Solution.hpp"
#include "Instance.hpp"


Solution* findFeasableSol(Instance* instance,int VNFCapacity, unsigned long timeout, int demandToCheck = -1);
Solution* AFRL(Instance* instance, int VNFCapacity, int kf, unsigned long timeout, int demandToCheck = -1);
Solution* AFRA(Instance* instance, int VNFCapacity, int kd, unsigned long timeout, int demandToCheck = -1);
Solution* AFRLA(Instance* instance, int VNFCapacity, int kf, int kd, unsigned long timeout, int demandToCheck = -1);

#endif