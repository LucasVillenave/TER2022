#ifndef INSTANCE
#define INSTANCE
#include "Solution.hpp"
#include <iostream>
#include <vector>


class Instance{

 public:

     int nbNodes;

     std::vector<std::vector<int>> adjacencyMatrix;

     int lowVNFCapacity;
     int mediumVNFCapacity;
     int highVNFCapacity;

     int hasA=0;

     int nbDemands;
     std::vector<int> demandsStart;
     std::vector<int> demandsEnd;
     std::vector<int> demands;

     int arcCapacity;
     int serviceCapacity;

     Instance(int nbNodes,std::vector<std::vector<int>> adjacencyMatrix,
              int lowVNFCapacity,int mediumVNFCapacity,int highVNFCapacity,
              int nbDemands,std::vector<int> demandsStart,std::vector<int> demandsEnd,std::vector<int> demands,
              int arcCapacity,int serviceCapacity){

         this->nbNodes=nbNodes;
         this->adjacencyMatrix=adjacencyMatrix;

         this->highVNFCapacity=highVNFCapacity;
         this->mediumVNFCapacity=mediumVNFCapacity;
         this->lowVNFCapacity=lowVNFCapacity;

         this->nbDemands=nbDemands;
         this->demandsStart=demandsStart;
         this->demandsEnd=demandsEnd;
         this->demands=demands;

         this->arcCapacity=arcCapacity;
         this->serviceCapacity=serviceCapacity;
     }

    void print();

    void addA();

    Solution* getTrivialSolution();

    int check(Solution* sol);

    int flowCheck(Solution* sol);
};



#endif
