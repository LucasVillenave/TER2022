#include "metaHeuristics.hpp"
#include "modelSolving.hpp"
#include <ctime>

using namespace std;

Solution* findFeasableSol(Instance* i, int VNFCapacity, unsigned long timeout,int demandToCheck){

    Instance* iA = new Instance(i->nbNodes,i->adjacencyMatrix,
                                i->lowVNFCapacity,i->mediumVNFCapacity,i->highVNFCapacity,
                                i->nbDemands,i->demandsStart,i->demandsEnd,i->demands,
                                i->arcCapacity,i->serviceCapacity);
    iA->addA();
    Solution* sol = iA->getTrivialSolution();

    Solution* SPMDSol = SPMD(sol,iA,VNFCapacity,iA->nbNodes,timeout,demandToCheck);
    if (SPMDSol==NULL){
        return NULL;
    }

    if (SPMDSol->openVNF.size()!=i->nbNodes){
        cout << endl << "couldn't find a feasable solution on original graph !" << endl << endl;
        return NULL;
    }else{
        return SPMDSol;
    }
}

Solution* AFRL(Instance* instance, int VNFCapacity, int kf, unsigned long timeout,int demandToCheck){

    Solution* sol = findFeasableSol(instance,VNFCapacity, timeout);

    if (sol==NULL || (instance->check(sol,VNFCapacity)!=1) ){
        return NULL;
    }

    std::cout <<std::endl << "solution found, ameliorating" <<std::endl <<std::endl;

    int tmpVal = sol->getValue();
    Solution* spSol = SP(instance,VNFCapacity,0,timeout,demandToCheck,1,sol,kf);
    if (spSol==NULL){
        return sol;
    }
    Solution* tmpSol;

    while(tmpVal>spSol->getValue()){

        tmpVal = spSol->getValue();

        tmpSol = SP(instance,VNFCapacity,0,timeout,demandToCheck,1,spSol,kf);
        if(tmpSol==NULL){
            return spSol;
        }else{
            spSol = tmpSol;
        }
    }

    return spSol;
}

Solution* AFRLA(Instance* instance, int VNFCapacity, int kf, int kd, unsigned long timeout,int demandToCheck){

    Solution* sol = findFeasableSol(instance,VNFCapacity, timeout);

    if (sol==NULL || (instance->check(sol,VNFCapacity)!=1) ){
        return NULL;
    }

    std::cout <<std::endl << "solution found, ameliorating" <<std::endl <<std::endl;

    int tmpVal = sol->getValue();
    Solution* spSol = SP(instance,VNFCapacity,0,timeout,demandToCheck,2,sol,kf,kd);
    if (spSol==NULL){
        return sol;
    }
    Solution* tmpSol;

    while(tmpVal>spSol->getValue()){

        tmpVal = spSol->getValue();

        tmpSol = SP(instance,VNFCapacity,0,timeout,demandToCheck,2,spSol,kf,kd);
        if(tmpSol==NULL){
            return spSol;
        }else{
            spSol = tmpSol;
        }

        if (tmpVal==spSol->getValue()){
            tmpSol = SP(instance,VNFCapacity,0,timeout,demandToCheck,2,spSol,kf,kd*2);
            if(tmpSol==NULL){
                return spSol;
            }else{
                spSol = tmpSol;
            }
        }
    }

    return spSol;
}