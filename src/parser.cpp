#include "parser.hpp"
#include "Instance.hpp"
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

Instance load(std::string path){
    string prefixe = "../instances/cleaned";
    path = prefixe + path;
    
    string line;
    fstream f;
    vector<string> words;
    
    int nbNodes;
    int nbEdges;
    int nbDemands;
    std::vector<std::vector<int>> adjencyMatrix;
    std::vector<int> demandsEnd;
    std::vector<int> demandsStart;
    std::vector<int> demands;

    f.open(path);
    if (!f){
        cout<<"\ncouldn't load\n"<<endl;
    }else{
        cout<<"\nsuccessful load\n"<<endl;
    }

    getline(f,line);
    words = split(line,' ');
    nbNodes = stoi(words.at(0));
    nbEdges = stoi(words.at(1));
    nbDemands = stoi(words.at(2));
    getline(f,line);

    cout << "could get that n = " << nbNodes << ", m = " << nbEdges << ", and nD = " << nbDemands << endl;

    for (int i=0;i<nbNodes;i++){
        std::vector<int> tmp;
        for (int j=0;j<nbNodes;j++){
            tmp.push_back(-1);
        }
        adjencyMatrix.push_back(tmp);
    }


    for (int i=0; i<(nbEdges*2);i++){
        getline(f,line);
        words = split(line,' ');
        adjencyMatrix.at(stoi(words.at(0))).at(stoi(words.at(1))) = 1;
    }
 
    getline(f,line);

    for (int i=0; i<nbDemands;i++){
        getline(f,line);
        words = split(line,' ');
        demands.push_back(stoi(words.at(2)));
        demandsStart.push_back(stoi(words.at(0)));
        demandsEnd.push_back(stoi(words.at(1)));
    }

    Instance* i = new Instance(nbNodes,adjencyMatrix,0,0,0,nbDemands,demandsStart,demandsEnd,demands,0,0);
    return *i;

}

void Gwrite(int nbNodes, int nbEdges, int nbDemands, int** edges, vector<int> demands, vector<int> demandsEnd, vector<int> demandsStart, string fileName){
    string prefixe = "../instances/";
    ofstream f(prefixe + fileName);
    if (!f){
        string s = "couldn't create file : ";
    }
    string separator = " ";
    f << nbNodes << separator << nbEdges << separator << nbDemands << endl << endl;
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
    f.open(prefixe + path);
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
                ++nbNodes;
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
                edges[dst][src] = stoi(words[5]);
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

    string c = "cleaned";
    path = c + path;
    Gwrite(nbNodes, nbEdges, nbDemands, edges, demands, demandsEnd, demandsStart, path);
}
