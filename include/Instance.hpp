#ifndef INSTANCE
#define INSTANCE
#include <iostream>
#include <vector>


class Instance{

 public:

     int nbNodes;
     std::vector<std::vector<int>> adjencyMatrix;

     int lowVNFCapacity;
     int mediumVNFCapacity;
     int highVNFCapacity;

     int nbDemands;
     std::vector<int> demandsStart;
     std::vector<int> demandsEnd;
     std::vector<int> demands;

     int arcCapacity;
     int serviceCapacity;

     Instance(int nbNodes,std::vector<std::vector<int>> adjencyMatrix,
              int lowVNFCapacity,int mediumVNFCapacity,int highVNFCapacity,
              int nbDemands,std::vector<int> demandsStart,std::vector<int> demandsEnd,std::vector<int> demands,
              int arcCapacity,int serviceCapacity){

         this->nbNodes=nbNodes;
         this->adjencyMatrix=adjencyMatrix;

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

     void print()
     {
       std::cout << "Network with " << nbNodes << " nodes\n";

       std::cout << "Arc capacity: " << arcCapacity << "\n";
       std::cout << "Service capacity: " << serviceCapacity << "\n";

       std::cout << "Low VNF Capacity:" << lowVNFCapacity << "\n";
       std::cout << "Medium VNF Capacity:" << mediumVNFCapacity << "\n";
       std::cout << "High VNF Capacity:" << highVNFCapacity << "\n";

       std::cout << nbDemands << " demands:\n";
       for(int demandIndex=0;demandIndex<nbDemands;demandIndex++)
       {
         std::cout << "Demand " << demandIndex << ", " << demands[demandIndex] << " from node " << demandsStart[demandIndex] << " to node " << demandsEnd[demandIndex] << "\n";
       }

       std::cout << "Adjacency list:\n";
       for(std::vector<int> line:adjencyMatrix)
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
