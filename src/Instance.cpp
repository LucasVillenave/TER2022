#include "Instance.hpp"
using namespace std;


Solution* Instance::getTrivialSolution(){
       if (hasA == 0){addA();}

       vector<bool> openVNF;
       vector<vector<bool>>  useVNFforDemand;
       vector<vector<vector<bool>>>  useEdgeForDemandStart;
       vector<vector<vector<bool>>>  useEdgeForDemandEnd;

      cout << " here we have " << nbNodes << " nodes " << endl;

       for (int i=0 ; i<nbNodes-1; i++){
         vector<bool> tmp1;
         vector<vector<bool>> tmp2;
         vector<vector<bool>> tmp3;
         
         for (int j=0; j<nbNodes-1; j++){
           vector<bool> tmptmp2;
           vector<bool> tmptmp3;

           for (int k=0; k<nbDemands; k++){
            tmptmp2.push_back(false);
            tmptmp3.push_back(false);
           }

           tmp2.push_back(tmptmp2);
           tmp3.push_back(tmptmp3);
         }
         vector<bool> tmptmp2;
         vector<bool> tmptmp3;

         for (int k=0; k<nbDemands; k++){
          tmptmp2.push_back(demandsStart[k]==i);
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

       vector<bool> tmp1;
       vector<vector<bool>> tmp2;
       vector<vector<bool>> tmp3;

       for (int i=0; i<nbNodes; i++){
         vector<bool> tmptmp3;
         vector<bool> tmptmp2;

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

int Instance::check(Solution* sol, int VNFCapacity){
    int r = flowCheck(sol);
    if (r!=1){
        return r;
    }
    return capacityCheck(sol,VNFCapacity);
}

int Instance::flowCheck(Solution* sol){
    int n = nbNodes;
    if (sol-> openVNF.size()!=n){
        cout << sol-> openVNF.size() << " != " << n;
        cout << "/!\\ solution given hasn't the same number of nodes as graph checking with" << endl;
        return 0;
    }
    if (sol-> useVNFforDemand[0].size()!=nbDemands){
        cout << sol->useVNFforDemand[0].size() << " != " << nbDemands;
        cout << "/!\\ solution given hasn't the same number of demands as graph checking with" << endl;
        return 0;
    }

    for (int k=0;k<nbDemands;k++){
        int kVNF = -1;
        for (int i=0;i<n;i++){
            if (sol->useVNFforDemand[i][k]==1){
                if (kVNF==-1){
                    kVNF = i;
                }else{
                    // using 2 or more vnf for a demand
                    return -102;
                }
            }
        }
        if (kVNF==-1){
            // not using any vnf for a demand
            return -2;
        }

        int switch1 = 0;
        int switch2 = 0;
        int switch3 = 0;
        int switch4 = 0;

        for (int i=0;i<n;i++){
            if (sol->useEdgeForDemandStart[demandsStart[k]][i][k]==1){
                switch1++;
            }
            if (sol->useEdgeForDemandStart[i][kVNF][k]==1){
                switch2++;
            }
            if (sol->useEdgeForDemandEnd[i][demandsEnd[k]][k]==1){
                switch3++;
            }
            if (sol->useEdgeForDemandEnd[kVNF][i][k]==1){
                switch4++;
            }
        }

        if (kVNF == demandsEnd[k]){
            switch3++;
            switch4++;
        }
        if (kVNF == demandsStart[k]){
            switch1++;
            switch2++;
        }

        if (switch1!=1){
            cout << "switch of "<< switch1 << endl;
            cout << "on demand " << k << endl;
            return -3;
        }
        if (switch2!=1){
            cout << "switch of "<< switch2 << endl;
            cout << "on demand " << k << endl;
            return -4;
        }
        if (switch3!=1){
            cout << "switch of "<< switch3 << endl;
            cout << "on demand " << k << endl;
            return -5;
        }
        if (switch4!=1){
            cout << "switch of "<< switch4 << endl;
            cout << "on demand " << k << endl;
            return -6;
        }
        // flow 1 start from start, end to vnf
        // flow 2 start from vnf, end to end

        for (int i=0;i<n;i++){
            if (i!=kVNF && i!=demandsStart[k] && i!=demandsEnd[k]){
                int counter1 = 0;
                int counter2 = 0;
                for (int j=0;j<n;j++){
                    if (sol->useEdgeForDemandStart[j][i][k]==1){
                        counter1++;
                    }
                    if (sol->useEdgeForDemandStart[i][j][k]==1){
                        counter1--;
                    }
                    if (sol->useEdgeForDemandEnd[j][i][k]==1){
                        counter2++;
                    }
                    if (sol->useEdgeForDemandEnd[i][j][k]==1){
                        counter2--;
                    }
                }

                if (counter1!=0){
                    cout << endl << i << endl;
                    cout << endl << k << endl;
                    return -7;
                }
                if (counter2!=0){
                    return -8;
                }
                //flow conservation
            }
        }
    }
    return 1;
}

    void Instance::addA()
    {
       vector<int> a;
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
           adjacencyMatrix[i].push_back(0);
           a.push_back(0);
         }
         s=0;
       }
       a.push_back(0);
       this->adjacencyMatrix.push_back(a);
       nbNodes++;
       this->hasA = 1;
     }

    void Instance::print()
    {
       cout << "Network with " << nbNodes << " nodes\n";

       cout << "Arc capacity: " << arcCapacity << "\n";
       cout << "Service capacity: " << serviceCapacity << "\n";

       cout << "Low VNF Capacity:" << lowVNFCapacity << "\n";
       cout << "Medium VNF Capacity:" << mediumVNFCapacity << "\n";
       cout << "High VNF Capacity:" << highVNFCapacity << "\n";

       cout << nbDemands << " demands:\n";
       for(int demandIndex=0;demandIndex<nbDemands;demandIndex++)
       {
         cout << "Demand " << demandIndex << ", " << demands[demandIndex] << " from node " << demandsStart[demandIndex] << " to node " << demandsEnd[demandIndex] << "\n";
       }

       cout << "Adjacency Matrix:\n";
       for(vector<int> line:adjacencyMatrix)
       {
         for(int arcValue:line)
         {
           if (arcValue>=0){
             cout<<" ";
           }
           cout << arcValue;
           for (int i=0;i<3-logsize(arcValue);i++){
             cout<<" ";
           }
         }
         cout << "\n";
       }
     }

int Instance::capacityCheck(Solution* sol, int VNFcapacity){
    for (int i=0;i<nbNodes-hasA;i++){
        for (int j=i+1;j<nbNodes-hasA;j++){
            int arcSum=0;
            for (int k=0;k<nbDemands;k++){
                arcSum += demands[k]*(sol->useEdgeForDemandEnd[i][j][k] + sol->useEdgeForDemandStart[i][j][k]);
            }
            if (arcSum>arcCapacity){
                return -101;
            }
        }

        int VNFSum = 0;
        for (int k=0;k<nbDemands;k++){
            VNFSum += demands[k]*sol->useVNFforDemand[i][k];
        }
        if (VNFSum > VNFcapacity){
            return -2;
        }
    }
    return 1;
}