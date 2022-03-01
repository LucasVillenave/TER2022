#ifndef GRAPH
#define GRAPH
#include <iostream>



class Instance{

 public:
     //nb nodes
     int nbNodes;

     //different services levels as described in the paper
     int highVNFCapacity;
     int mediumVNFCapacity;
     int lowVNFCapacity;

     //capacity matrix, equal -1 if nodes aren't adjacent
     int** capacityMatrix;

     int nbDemands;
     int* demandsStart;
     int* demandsEnd;
     int* demands;

     Instance(int nbNodes,int** capacityMatrix){
         this->nbNodes=nbNodes;
         this->capacityMatrix=capacityMatrix;
     }
};


#endif
