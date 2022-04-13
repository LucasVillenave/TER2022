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
       for(std::vector<int> line:adjacencyMatrix)
       {
         for(int arcValue:line)
         {
           if (arcValue>=0){
             std::cout<<" ";
           }
           std::cout << arcValue;
           for (int i=0;i<3-logsize(arcValue);i++){
             std::cout<<" ";
           }
         }
         std::cout << "\n";
       }
     }

     void addA(){

       std::vector<int> a;
       int s = 0;
       
       for (int i=0;i<nbNodes;i++){
         for (int j=0;j<nbDemands;j++){
           if ((demandsStart[j]==i || demandsEnd[j]==i) && s == 0){
             adjacencyMatrix[i].push_back(1);
             a.push_back(1);
             s = 1;
           }
         }
         if (s==0){
           adjacencyMatrix[i].push_back(-1);
           a.push_back(-1);
         }
         s=0;
       }
       a.push_back(-1);
       this->adjacencyMatrix.push_back(a);
       this->hasA = 1;
     }

     Solution* getTrivialSolution(){
       if (hasA == 0){addA();}

       std::vector<bool> openVNF;
       std::vector<std::vector<bool>>  useVNFforDemand;
       std::vector<std::vector<std::vector<bool>>>  useEdgeForDemandStart;
       std::vector<std::vector<std::vector<bool>>>  useEdgeForDemandEnd;

       for (int i=0 ; i<nbNodes; i++){
         std::vector<bool> tmp1;
         std::vector<std::vector<bool>> tmp2;
         std::vector<std::vector<bool>> tmp3;
         
         for (int j=0; j<nbNodes; j++){
           std::vector<bool> tmptmp2;
           std::vector<bool> tmptmp3;

           for (int k=0; k<nbDemands; k++){
            tmptmp2.push_back(false);
            tmptmp3.push_back(false);
           }

           tmp2.push_back(tmptmp2);
           tmp3.push_back(tmptmp3);
         }
         std::vector<bool> tmptmp2;
         std::vector<bool> tmptmp3;

         for (int k=0; k<nbDemands; k++){
          tmptmp2.push_back(demandsEnd[k]==i);
          tmptmp3.push_back(false);
          tmp1.push_back(false);
         }

         tmp2.push_back(tmptmp2);
         tmp3.push_back(tmptmp3);

         useEdgeForDemandStart.push_back(tmp2);
         useEdgeForDemandEnd.push_back(tmp3);
         useVNFforDemand.push_back(tmp1);
         openVNF.push_back(false);
       }

       std::vector<bool> tmp1;
       std::vector<std::vector<bool>> tmp2;
       std::vector<std::vector<bool>> tmp3;

       for (int i=0; i<nbNodes; i++){
         std::vector<bool> tmptmp3;
         std::vector<bool> tmptmp2;

         for (int j=0;j<nbDemands;j++){
          tmptmp3.push_back(demandsEnd[j]==i);
          tmptmp2.push_back(false);
         }
         tmp3.push_back(tmptmp3);
         tmp2.push_back(tmptmp2);
       }
       
       useEdgeForDemandStart.push_back(tmp2);
       useEdgeForDemandEnd.push_back(tmp3);

       for (int k=0; k<nbDemands; k++){
        tmp1.push_back(true);
       }

       useVNFforDemand.push_back(tmp1);
       openVNF.push_back(true);

      return new Solution(openVNF,useVNFforDemand,useEdgeForDemandStart,useEdgeForDemandEnd);
     }

     int logsize(int n)
     {
       int size = 1;
       if (n<0){
         n=-n;
       }
       while(n>10)
       {
         n=n/10;
         ++size;
       }
       return size;
     }
};



#endif
