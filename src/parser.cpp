#include "parser.hpp"
#include "Instance.hpp"
#include "modelSolving.hpp"
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

vector<string> split(string s, char delim) {
    vector<string> words;
    stringstream ss(s);
    string word;
    while (getline(ss, word, delim)) {
        if (word!=""){
            words.push_back(word);
        }
    }
    return words;
}

vector<int> generateVNF(int n, vector<int> demands){

    vector<int> vnf;
    int hvnf = 0;
    for (int i=0;i<demands.size();i++){
        hvnf += demands[i];
    }
    
    int lvnf = (2*hvnf/n) + 1; //good enought
    int mvnf = ((lvnf+hvnf)/2);
    
    vnf.push_back(lvnf);
    vnf.push_back(mvnf);
    vnf.push_back(hvnf);

    return vnf;
}

Instance* load(std::string path){
    string prefixe = "../instances/cleaned/C";
    path = prefixe + path;
    
    string line;
    fstream f;
    vector<string> words;
    
    int nbNodes;
    int nbEdges;
    int nbDemands;
    int lvnf;
    int mvnf;
    int hvnf;
    std::vector<std::vector<int>> adjencyMatrix;
    std::vector<int> demandsEnd;
    std::vector<int> demandsStart;
    std::vector<int> demands;

    cout << "trying to load : " << path << endl;
    f.open(path);
    if (!f){
        cout<<"\ncouldn't load\n"<<endl;
    }else{
        cout<<"\nsuccessful load\n"<<endl;
    }

    getline(f,line);
    getline(f,line);
    words = split(line,' ');
    nbNodes = stoi(words.at(0));
    nbEdges = stoi(words.at(1));
    nbDemands = stoi(words.at(2));
    lvnf = stoi(words.at(3));
    mvnf = stoi(words.at(4));
    hvnf = stoi(words.at(5));
    getline(f,line);

    cout << "could get that n = " << nbNodes << ", m = " << nbEdges << ", and nD = " << nbDemands << endl;

    for (int i=0;i<nbNodes;i++){
        std::vector<int> tmp;
        for (int j=0;j<nbNodes;j++){
            tmp.push_back(0);
        }
        adjencyMatrix.push_back(tmp);
    }


    for (int i=0; i<(nbEdges);i++){
        //cout << stoi(words.at(0)) << " " << stoi(words.at(1)) << " at " << i << " on " << nbEdges << endl;
        getline(f,line);
        words = split(line,' ');
        adjencyMatrix.at(stoi(words.at(0))).at(stoi(words.at(1))) = 1;
        adjencyMatrix.at(stoi(words.at(1))).at(stoi(words.at(0))) = 1;
    }

    getline(f,line);

    for (int i=0; i<nbDemands;i++){
        getline(f,line);
        words = split(line,' ');
        demands.push_back(stoi(words.at(2)));
        demandsStart.push_back(stoi(words.at(0)));
        demandsEnd.push_back(stoi(words.at(1)));
    }

    Instance* i = new Instance(nbNodes,adjencyMatrix,lvnf,mvnf,hvnf,nbDemands,demandsStart,demandsEnd,demands,0,0);
    i = new Instance(nbNodes,adjencyMatrix,lvnf,mvnf,hvnf,nbDemands,demandsStart,demandsEnd,demands,arcCapacity(i),0);
    return i;

}

void Gwrite(int nbNodes, int nbEdges, int nbDemands, int** edges, vector<int> demands, vector<int> demandsEnd, vector<int> demandsStart, string fileName){

    string prefixe = "../instances/";
    string cl = "cleaned/";
    cout << "trying to write at : " << prefixe + cl + fileName << endl;
    ofstream f(prefixe + cl + fileName);
    if (!f){
        string s = "couldn't create file : ";
    }
    string separator = " ";

    vector<int> vnf = generateVNF(nbNodes,demands);

    f << "nbNodes nbEdges nbDemands lvnf mvnf hvnf u" << endl;

    f << nbNodes << separator << nbEdges << separator << nbDemands << separator << vnf[0] << separator << vnf[1] << separator << vnf[2] << endl << endl;

    for (int i=0;i<nbNodes;i++){
        for (int j=0;j<nbNodes;j++){
            int e = edges[i][j];
            if (e!=-1){
                f << i << separator << j << endl;
            }
        }
    }

    f<<endl;
    for (int i=0;i<nbDemands;i++){
        f << demandsStart.at(i) << separator << demandsEnd.at(i) << separator << demands.at(i) << endl;
    }
    f.close();
}

void clean(string path){
    int nbDemands = 0;
    vector<int> demandsStart;
    vector<int> demandsEnd;
    vector<int> demands;

    int** edges;
    int nbEdges = 0;

    int nbNodes = 0;


    vector<string> nodesNames;
    vector<string>::iterator itr;
    int src;
    int dst;  

    string line;
    fstream f;
    vector<string> words;
    
    int switchos = 0;
    string prefixe = "../instances/";
    string raw = "raw/";
    cout << "trying to load : " << prefixe << raw << path << endl;
    f.open(prefixe + raw + path);
    if (!f){
        cout<<"\ncouldn't load\n"<<endl;
    }else{
        cout<<"\nsuccessful load\n"<<endl;
    }

    //looking for nodes
    string keyword = "NODES";
    while(switchos == 0){
        getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 1;
            }
        }
    }
    keyword = ")";
    while(switchos == 1){
        getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 0;
            }else{
                nbNodes++;
                nodesNames.push_back(words[0]);
            }
        }
    }

    //init int** edges
    edges = new int* [nbNodes];
    for (int i=0;i<nbNodes;i++){
        edges[i] = new int[nbNodes];
        for (int j=0;j<nbNodes;j++){
            edges[i][j] = -1;
        }
    }

    //looking for edges
    keyword = "LINKS";
    while(switchos == 0){
        getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 1;
            }
        }
    }
    keyword = ")";
    while(switchos == 1){
        getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 0;
            }else{
                ++nbEdges;

                itr = find(nodesNames.begin(),nodesNames.end(),words[2]);
                src = distance(nodesNames.begin(),itr);
                
                itr = find(nodesNames.begin(),nodesNames.end(),words[3]);
                dst = distance(nodesNames.begin(),itr);

                edges[src][dst] = stoi(words[5]);
            }
        }
    }

    //looking for demands
    keyword = "DEMANDS";
    while(switchos == 0){
        getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 1;
            }
        }
    }
    keyword = ")";
    while(switchos == 1){
        getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 0;
            }else{
                ++nbDemands;

                itr = find(nodesNames.begin(),nodesNames.end(),words[2]);
                demandsStart.push_back(distance(nodesNames.begin(),itr));
                
                itr = find(nodesNames.begin(),nodesNames.end(),words[3]);
                demandsEnd.push_back(distance(nodesNames.begin(),itr));
                
                demands.push_back(stoi(words[6]));
            }
        }
    }

    string c = "C";
    path = c + path;
    Gwrite(nbNodes, nbEdges, nbDemands, edges, demands, demandsEnd, demandsStart, path);
}
