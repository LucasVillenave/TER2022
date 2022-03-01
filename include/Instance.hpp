#ifndef GRAPH
#define GRAPH
#include <iostream>
#include <vector>


class Instance{

 public:
     //nb nodes
     int nbNodes;

     //capacity matrix, equal -1 if nodes aren't adjacent
     std::vector<std::vector<int>> capacityMatrix;

     //different services levels as described in the paper
     int highVNFCapacity;
     int mediumVNFCapacity;
     int lowVNFCapacity;

     int nbDemands;
     int* demandsStart;
     int* demandsEnd;
     int* demands;

     Instance(int nbNodes,std::vector<std::vector<int>> capacityMatrix){
         this->nbNodes=nbNodes;
         this->capacityMatrix=capacityMatrix;
     }

     void print()
     {
       std::cout << "Network with " << nbNodes << " nodes\n";
       std::cout << "Adjacency list with capacities:\n";
       for(std::vector<int> line:capacityMatrix)
       {
         for(int arcValue:line)
         {
           std::cout << arcValue << " ";
         }
         std::cout << "\n";
       }
     }
};


#endif
