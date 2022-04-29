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

Solution* kOptL(Solution* sol,Instance* i){
    try{
        cout<<"--> Creating the Gurobi environment"<<endl;
		GRBEnv env = GRBEnv(true);

        env.start();

        cout<<"--> Creating the Gurobi model"<<endl;
		GRBModel model = GRBModel(env);

        cout<<"--> Creating the variables"<<endl;
        stringstream name;

        int n = i-> nbNodes;
        int m = i-> nbDemands;
        GRBVar*** x1 = new GRBVar** [n];
        for (int i=0;i<n;++i){
            x1[i] = new GRBVar* [n];
            for (int j=0;j<n;++j){
                x1[i][j] = new GRBVar [n];
                for (int k=0;k<n; ++k){
                    name << "x1[" << i<<"][" << j << "][" << k << "]";
                    x1[i][j][k] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, name.str());
                    name.str("");
                }
            }
        }

        GRBVar*** x2 = new GRBVar** [n];
        for (int i=0;i<n;++i){
            x2[i] = new GRBVar* [n];
            for (int j=0;j<n;++j){
                x2[i][j] = new GRBVar [n];
                for (int k=0;k<n; ++k){
                    name << "x2[" << i<<"][" << j << "][" << k << "]";
                    x2[i][j][k] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, name.str());
                    name.str("");
                }
            }
        }

        cout<<"--> Creating the Objective"<<endl;

        GRBLinExpr obj = 0;
		for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                for (int k=0;k<n; k++){
			        obj+=x1[i][j][k];
                }
            }
		}
		model.setObjective(obj, GRB_MINIMIZE);

        // cout<<"--> Creating constraints"<<endl;

        // cout<<"--> Constraint : initially get out of 0"<<endl;

        // GRBLinExpr source = 0;
        // for (int i=0;i<n;i++){
        //     source += x[0][i][0];
        // }
        // name << "initial from 0";
        // model.addConstr(source==1,name.str());
        // name.str("");

        // cout<<"--> Constraint : finnaly return to 0"<<endl;

        // GRBLinExpr destination = 0;
        // for (int i=0;i<n;i++){
        //     destination += x[i][0][n-1];
        // }
        // name << "destination to 0";
        // model.addConstr(destination==1,name.str());
        // name.str("");

        // cout<<"--> Constraint : do not return/get out of 0 in between start and end"<<endl;

        // GRBLinExpr pasDeRetourIntermediaire = 0;
        // for (int k=1;k<n-1;k++){
        //     for (int i=0;i<n;i++){
        //         pasDeRetourIntermediaire += x[i][0][k] + x[0][i][k];
        //     }
        // }
        // name << " no intermediary to/from 0";
        // model.addConstr(pasDeRetourIntermediaire==0,name.str());
        // name.str("");

        // cout<<"--> Constraint : flow conservation"<<endl;

        // GRBLinExpr conservationFlow;
        // for (int k=0;k<n-1;k++){
        //     for (int i=0;i<n;i++){
        //         conservationFlow = 0;
        //         for (int j=0;j<n;j++){
        //             conservationFlow += x[j][i][k] - x[i][j][k+1];
        //         }
        //         name << "conservation flow etape " << k << " on vertex " << i;
        //         model.addConstr(conservationFlow==0,name.str());
        //         name.str("");
        //     }
        // }

        // cout<<"--> Constraint : go only one time to each node, get out only one time from each node"<<endl;

        // GRBLinExpr uneEtUneSeule;
        // GRBLinExpr uneEtUneSeule2;
        // for (int i=0;i<n;i++){

        //     uneEtUneSeule=0;
        //     uneEtUneSeule2=0;

        //     for (int j=0;j<n;j++){
        //         for (int k=0;k<n;k++){
        //             uneEtUneSeule+=x[j][i][k];
        //             uneEtUneSeule2+=x[i][j][k];
        //         }
        //     }

        //     name << " on arrive une et une seule fois a " << i;
        //     model.addConstr(uneEtUneSeule==1,name.str());
        //     name.str("");

        //     name << " on part une et une seule fois a " << i;
        //     model.addConstr(uneEtUneSeule2==1,name.str());
        //     name.str("");
        // }

        // cout<<"--> Constraint bonus : don't go from i to i"<<endl;

        // for (int i=0;i<n;i++){
        //     for (int k=0;k<n;k++){
        //         GRBLinExpr pasboucle=0;
        //         pasboucle = x[i][i][k];
        //         model.addConstr(pasboucle==0,name.str());
        //     }
        // }

        // cout<<"--> setting model"<<endl;
        // model.set(GRB_DoubleParam_TimeLimit, 600.0);
		// model.set(GRB_IntParam_Threads,1);

        // cout<<"--> optimize"<<endl;
        // model.optimize();
		// model.write("model.lp");

        // int status = model.get(GRB_IntAttr_Status);
		// if (status == GRB_OPTIMAL || (status== GRB_TIME_LIMIT && model.get(GRB_IntAttr_SolCount)>0)){
		// 	cout << "Succes! (Status: " << status << ")" << endl;
		// 	cout << "Runtime : " << model.get(GRB_DoubleAttr_Runtime) << " seconds"<<endl;

		// 	cout<<"--> Printing results "<<endl;
		// 	model.write("solution.sol");
		// 	cout << "Objective value = "<< model.get(GRB_DoubleAttr_ObjVal)  << endl;

        //     for(int i=0;i<n;i++){
        //         for(int j=0;j<n;j++){
        //             for (int k=0;k<n;k++){
        //                 if(x[i][j][k].get(GRB_DoubleAttr_X)>0){
        //                     cout << "x["<<i<<"][" << j << "][" << k << "] is used on flow"<< endl;
        //                 }
        //             }
        //         }
		// 	}
        // }
    } catch(GRBException e) {
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	} catch(...) {

    }

    return sol;
}