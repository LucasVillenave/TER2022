#include "modelSolving.hpp"
#include "gurobi_c++.h"
#include <iostream>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

Solution* SP(Instance* instance, int VNFCapacity, int VNFlb, int demandToCheck, int kOpt, int kf, Solution* kOptSol){

    Solution* returnSol;


    try{
        cout<<"--> Creating the Gurobi environment"<<endl;
		GRBEnv env = GRBEnv(true);

        env.start();

        cout<<"--> Creating the Gurobi model"<<endl;
		GRBModel model = GRBModel(env);

        cout<<"--> Creating the variables"<<endl;
        stringstream name;

        int n = instance-> nbNodes;
        int m = instance-> nbDemands;
        int arcCapacity = instance->arcCapacity;
        vector<vector<int>> adjacencyMatrix = instance->adjacencyMatrix;

        //creating the returnSol variables

        vector<bool> openVNF;
        vector<vector<bool>> useVNFforDemand;
        vector<vector<vector<bool>>> useEdgeForDemandStart;
        vector<vector<vector<bool>>> useEdgeForDemandEnd;

        for (int i=0; i<n; i++){
            vector<bool> tmpUseVNF;
            vector<vector<bool>> tmpStart;
            vector<vector<bool>> tmpEnd;

            for (int k=0; k<m; k++){
                tmpUseVNF.push_back(false);
            }

            for (int j=0; j<n; j++){
                vector<bool> tmptmpStart;
                vector<bool> tmptmpEnd;
                for (int k=0; k<m; k++){
                    tmptmpStart.push_back(false);
                    tmptmpEnd.push_back(false);
                }
                tmpStart.push_back(tmptmpStart);
                tmpEnd.push_back(tmptmpEnd);
            }
            openVNF.push_back(false);
            useVNFforDemand.push_back(tmpUseVNF);
            useEdgeForDemandStart.push_back(tmpStart);
            useEdgeForDemandEnd.push_back(tmpEnd);
        }



        // creating the model variables

        GRBVar*** x1 = new GRBVar** [n];
        for (int i=0;i<n;i++){
            x1[i] = new GRBVar* [n];
            for (int j=0;j<n;j++){
                x1[i][j] = new GRBVar [m];
                for (int k=0;k<m; k++){
                    name << "x1[" << i<<"][" << j << "][" << k << "]";
                    x1[i][j][k] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, name.str());
                    name.str("");
                }
            }
        }

        GRBVar*** x2 = new GRBVar** [n];
        for (int i=0;i<n;i++){
            x2[i] = new GRBVar* [n];
            for (int j=0;j<n;j++){
                x2[i][j] = new GRBVar [m];
                for (int k=0;k<m; k++){
                    name << "x2[" << i<<"][" << j << "][" << k << "]";
                    x2[i][j][k] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, name.str());
                    name.str("");
                }
            }
        }

        
        GRBVar* y = new GRBVar [n];
        for (int i=0;i<n; i++){
            name << "y[" << i<<"]";
            y[i] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, name.str());
            name.str("");
        }

        GRBVar** z = new GRBVar* [n];
        for (int i=0;i<n; i++){
            z[i] = new GRBVar [m];
            for (int k=0;k<m; k++){
                name << "z[" << i<<"]["<< k<<"]";
                z[i][k] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, name.str());
                name.str("");
            }
        }

        cout<<"--> Creating the Objective (1)"<<endl;

        GRBLinExpr obj = 0;
		for(int i=0;i<n;i++){
            obj+=y[i];
		}
		model.setObjective(obj, GRB_MINIMIZE);

        cout<<"--> Creating constraints"<<endl;

        cout<<"--> Constraint : affect each demand to VNF (2)"<<endl;

        for (int k=0;k<m;k++){
            GRBLinExpr aVNF = 0;
            for (int i=0;i<n;i++){
                aVNF += z[i][k];
            }
            name << "affectation_of_demand" << k;
            model.addConstr(aVNF==1,name.str());
            name.str("");
        }

        cout<<"--> Constraint : redundancy of y/z (3)"<<endl;

        for (int k=0;k<m;k++){
            for (int i=0;i<n;i++){
                GRBLinExpr redundancy = y[i] - z[i][k];
                name << "z[" << i << "][" << k << "]_<=_y[" << i << "]";
                model.addConstr(redundancy>=0,name.str());
                name.str("");
            }
        }

        cout<<"--> Constraint : arc capacity (4)"<<endl;

        for (int j=0;j<n;j++){
            for (int i=0;i<n;i++){
                if (adjacencyMatrix[i][j]==1){
                    GRBLinExpr capacityCtr = 0;
                    for (int k=0; k<m;k++){
                        capacityCtr += (x1[i][j][k] + x2[i][j][k])*instance->demands[k];
                    }
                    name << "capacity_on_arc_" << i << "_" << j;
                    model.addConstr(capacityCtr <= arcCapacity ,name.str());
                    name.str("");
                }
            }
        }

        cout<<"--> Constraint : flow 1 conservation (5.1)"<<endl;

        for (int k=0;k<m;k++){          
            GRBLinExpr flow1 = 0;
            int i = instance->demandsStart[k];
            flow1 += z[i][k];
            for (int j=0; j<n;j++){
                if (adjacencyMatrix[i][j]==1){
                    flow1 += x1[i][j][k] - x1[j][i][k];
                }
            }
            name << "flow_conservation_1_of_demand_" << k << "_on_" << i << "_wich_is_demandStart";
            model.addConstr(flow1 == 1 ,name.str());
            name.str("");
        }

        cout<<"--> Constraint : flow 1 conservation (5.2)"<<endl;

        for (int k=0;k<m;k++){
            for (int i=0;i<n;i++){
                if (instance->demandsStart[k]!=i){
                    GRBLinExpr flow1 = 0;
                    flow1 += z[i][k];
                    for (int j=0; j<n;j++){
                        if (adjacencyMatrix[i][j]==1){
                            flow1 += x1[i][j][k] - x1[j][i][k];
                        }
                    }
                    name << "flow_conservation_1_of_demand_" << k << "_on_" << i;
                    model.addConstr(flow1 == 0 ,name.str());
                    name.str("");
                } 
            } 
        }

        cout<<"--> Constraint : flow 2 conservation (6.1)"<<endl;

        for (int k=0;k<m;k++){          
            GRBLinExpr flow2 = 0;
            int i = instance->demandsEnd[k];
            flow2 -= z[i][k];
            for (int j=0; j<n;j++){
                if (adjacencyMatrix[i][j]==1){
                    flow2 += x2[i][j][k] - x2[j][i][k];
                }
            }
            name << "flow_conservation_2_of_demand_" << k << "_on_" << i << "_wich_is_demandEnd";
            model.addConstr(flow2 == -1 ,name.str());
            name.str("");
        }

        cout<<"--> Constraint : flow 2 conservation (6.2)"<<endl;

        for (int k=0;k<m;k++){
            for (int i=0;i<n;i++){
                if (instance->demandsEnd[k]!=i){          
                    GRBLinExpr flow2 = 0;
                    flow2 -= z[i][k];
                    for (int j=0; j<n;j++){
                        if (adjacencyMatrix[i][j]==1){
                            flow2 += x2[i][j][k] - x2[j][i][k];
                        }
                    }
                    name << "flow_conservation_2_of_demand_" << k << "_on_" << i;
                    model.addConstr(flow2 == 0 ,name.str());
                    name.str("");
                } 
            } 
        }

        cout<<"--> Constraint : one and only one exit (7)"<<endl;

        for (int k=0;k<m;k++){
            for (int i=0;i<n;i++){        
                GRBLinExpr sum = 0;
                for (int j=0; j<n;j++){
                    if (adjacencyMatrix[i][j]==1){
                        sum += x1[i][j][k] + x2[i][j][k];
                    }
                }
                name << "one_exit_of_demand_" << k << "_on_" << i;
                model.addConstr(sum <=1 ,name.str());
                name.str("");
            } 
        }

        cout<<"--> Constraint : one and only one enter (8)"<<endl;

        for (int k=0;k<m;k++){
            for (int i=0;i<n;i++){        
                GRBLinExpr sum = 0;
                for (int j=0; j<n;j++){
                    if (adjacencyMatrix[i][j]==1){
                        sum += x1[j][i][k] + x2[j][i][k];
                    }
                }
                name << "one_enter_of_demand_" << k << "_on_" << i;
                model.addConstr(sum <=1 ,name.str());
                name.str("");
            } 
        }

        cout<<"--> Constraint : VNF capacity (9)"<<endl;

        for (int i=0;i<n;i++){       
            GRBLinExpr sum = 0;
            sum -= VNFCapacity*y[i];
            for (int k=0; k<m;k++){
                sum += z[i][k]*instance->demands[k];
            }
            name << "VNF_capacity_of_" << i;
            model.addConstr(sum <=0 ,name.str());
            name.str("");
        }

        cout<<"--> Constraint : open at least VNFlb VNF (10)"<<endl;


        GRBLinExpr VNFcount = 0;
        for (int i=0;i<n;i++){       
            VNFcount+=y[i];
        }
        name << "VNF_count";
        model.addConstr(VNFcount >= VNFlb ,name.str());
        name.str("");

        switch (kOpt){
            case 0 :
                break;

            case 1:
                cout<<"----> Phase 2 : solution improvment by kopt (24)"<<endl;
                cout<<"--> kopt-L (25)"<<endl;
                if (kOptSol==NULL){
                    cout<<"--> should have been given a solution to improve"<<endl;
                }else{
                    GRBLinExpr kOptCtr = 0;

                    int sum = 0;

                    for (int i=0;i<n;i++){
                        if (kOptSol->openVNF[i]){
                            kOptCtr -= y[i];
                            sum ++;
                        }else{
                            kOptCtr += y[i];
                        }
                    }

                    name << "VNF_kopt";
                    model.addConstr(kOptCtr <= kf-sum ,name.str());
                    name.str("");
                }
                break;

            case 2 :
                cout<<"----> Phase 2 : solution improvment by kopt (24)"<<endl;
                cout<<"--> kopt-LA (25-26)"<<endl;

                cout<<"----> UNDER CONSTRUCTION <----"<<endl;

                break;

            default:
                break;
            
        }


        cout<<"----> setting model"<<endl;
        model.set(GRB_DoubleParam_TimeLimit, 120.0);
		model.set(GRB_IntParam_Threads,1);

        cout<<"----> optimize"<<endl;
        model.optimize();
		model.write("SPmodel.lp");

        int status = model.get(GRB_IntAttr_Status);
		if (status == GRB_OPTIMAL || (status== GRB_TIME_LIMIT && model.get(GRB_IntAttr_SolCount)>0)){
			cout << "Succes! (Status: " << status << ")" << endl;
			cout << "Runtime : " << model.get(GRB_DoubleAttr_Runtime) << " seconds"<<endl;

			cout<<"--> Printing results "<<endl;
			model.write("solution.sol");
			cout << "Objective value = "<< model.get(GRB_DoubleAttr_ObjVal)  << endl;

            for (int i=0;i<n;i++){
                if(y[i].get(GRB_DoubleAttr_X)>0){
                    openVNF[i] = true;
                    cout << "y["<<i<<"] is used"<< endl;
                }else{
                    openVNF[i] = false;
                }
            }
            for (int k=0;k<m;k++){
                for (int i=0;i<n;i++){
                    if(z[i][k].get(GRB_DoubleAttr_X)>0){
                        useVNFforDemand[i][k] = true;
                    }else{
                        useVNFforDemand[i][k] = false;
                    }
                }
            }
            for (int k=0;k<m;k++){
                for (int i=0;i<n;i++){
                    for (int j=0;j<n;j++){
                        if(x1[i][j][k].get(GRB_DoubleAttr_X)>0){
                            if (k==12){
                            }
                            useEdgeForDemandStart[i][j][k] = true;
                        }else{
                            useEdgeForDemandStart[i][j][k] = false;
                        }
                    }
                }
            }
            
            for (int k=0;k<m;k++){
                for (int i=0;i<n;i++){
                    for (int j=0;j<n;j++){
                        if(x2[i][j][k].get(GRB_DoubleAttr_X)>0){
                            useEdgeForDemandEnd[i][j][k] = true;
                        }else{
                            useEdgeForDemandEnd[i][j][k] = false;
                        }
                    }
                }
            }
            
            returnSol = new Solution(openVNF,useVNFforDemand,useEdgeForDemandStart,useEdgeForDemandEnd);

            if (demandToCheck>=0){
                for (int k=demandToCheck;k<demandToCheck+1;k++){
                    for (int i=0;i<n;i++){
                        if(z[i][k].get(GRB_DoubleAttr_X)>0){
                            cout << "z["<<i<<"][" << k << "] is used where demand start = " << instance->demandsStart[k]
                            << " and demand end = " << instance->demandsEnd[k] << endl;
                        }
                    }
                }

                for (int k=demandToCheck;k<demandToCheck+1;k++){
                    for (int i=0;i<n;i++){
                        for (int j=0;j<n;j++){
                            if(x1[i][j][k].get(GRB_DoubleAttr_X)>0){
                                cout << "x1["<<i<<"][" << j << "][" << k << "] is used"<< endl;
                            }
                        }
                    }
                }

                for (int k=demandToCheck;k<demandToCheck+1;k++){
                    for (int i=0;i<n;i++){
                        for (int j=0;j<n;j++){
                            if(x2[i][j][k].get(GRB_DoubleAttr_X)>0){
                                cout << "x2["<<i<<"][" << j << "][" << k << "] is used"<< endl;
                            }
                        }
                    }
                }
            }
        }
    } catch(GRBException e) {
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	} catch(...) {

    }

    return returnSol;
}