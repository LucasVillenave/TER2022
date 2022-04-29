#include "modelSolving.hpp"
#include "gurobi_c++.h"
#include <iostream>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

//ToDo
int arcCapacity(Instance* i){
    int s = 0;
    for (int d:i->demands){
        s+=d;
    }
    return s;
}

Solution* kOptL(Solution* sol,Instance* instance){
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

        cout<<"--> Creating the Objective"<<endl;

        GRBLinExpr obj = 0;
		for(int i=0;i<n-1;i++){
            for(int k=0;k<m;k++){
                obj+=z[i][k];
            }
		}
		model.setObjective(obj, GRB_MAXIMIZE);

        cout<<"--> Creating constraints"<<endl;

        cout<<"--> Constraint : affect each demand to VNF (16)"<<endl;

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
                model.addConstr(redundancy<=0,name.str());
                name.str("");
            }
        }

        cout<<"--> Constraint : arc capacity (4)"<<endl;

        for (int j=0;j<n;j++){
            for (int i=0;i<n;i++){
                GRBLinExpr capacityCtr = 0;
                for (int k=0; k<m;k++){
                    capacityCtr += x1[i][j][k] + x2[i][j][k];
                }
                name << "capacity_on_arc_" << i << "_" << j;
                model.addConstr(capacityCtr <= arcCapacity ,name.str());
                name.str("");
            }
        }

        cout<<"--> Constraint : flow 1 conservation (17.1)"<<endl;

        for (int k=0;k<m;k++){          
            GRBLinExpr flow1 = 0;
            int i = instance->demandsStart[k];
            for (int j=0; j<n;j++){
                flow1 += x1[i][j][k] - x1[j][i][k] + z[i][k];
            }
            name << "flow_conservation_of_demand_" << k << "_on_" << i << "_wich_is_demandStart";
            model.addConstr(flow1 == 0 ,name.str());
            name.str("");
        }

        // cout<<"--> Constraint : flow 1 conservation (17.2)"<<endl;

        // for (int k=0;k<m;k++){
        //     for (int i=0;i<n;i++){
        //         if (instance->demandsStart[k]!=i){          
        //             GRBLinExpr flow1 = 0;
        //             for (int j=0; j<n;j++){
        //                 flow1 += x1[i][j][k] - x1[j][i][k] + z[i][k];
        //             }
        //             name << "flow_conservation_of_demand_" << k << "_on_" << i;
        //             model.addConstr(flow1 == 0 ,name.str());
        //             name.str("");
        //         } 
        //     } 
        // }
        // rend model infaisable !

        cout<<"--> setting model"<<endl;
        model.set(GRB_DoubleParam_TimeLimit, 600.0);
		model.set(GRB_IntParam_Threads,1);

        cout<<"--> optimize"<<endl;
        model.optimize();
		model.write("model.lp");

        int status = model.get(GRB_IntAttr_Status);
		if (status == GRB_OPTIMAL || (status== GRB_TIME_LIMIT && model.get(GRB_IntAttr_SolCount)>0)){
			cout << "Succes! (Status: " << status << ")" << endl;
			cout << "Runtime : " << model.get(GRB_DoubleAttr_Runtime) << " seconds"<<endl;

			cout<<"--> Printing results "<<endl;
			model.write("solution.sol");
			cout << "Objective value = "<< model.get(GRB_DoubleAttr_ObjVal)  << endl;

            for (int k=0;k<m;k++){
                for (int i=0;i<n;i++){
                    if(z[i][k].get(GRB_DoubleAttr_X)>0){
                        cout << "z["<<i<<"][" << k << "] is used"<< endl;
                    }
                }
            }

            // for(int i=0;i<n;i++){
            //     for(int j=0;j<n;j++){
            //         for (int k=0;k<n;k++){
            //             if(x[i][j][k].get(GRB_DoubleAttr_X)>0){
            //                 cout << "x["<<i<<"][" << j << "][" << k << "] is used on flow"<< endl;
            //             }
            //         }
            //     }
			// }
        }
    } catch(GRBException e) {
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	} catch(...) {

    }

    return sol;
}