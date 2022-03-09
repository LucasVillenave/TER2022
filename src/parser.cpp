#include "parser.hpp"
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>


std::vector<std::string> split(std::string s, char delim) {
    std::vector<std::string> words;
    std::stringstream ss(s);
    std::string word;
    while (std::getline(ss, word, delim)) {
        if (word!=""){
            words.push_back(word);
        }
    }
    return words;
}

void write(int nbNodes, int nbEdges, int nbDemands, int** edges, std::vector<int> demands, std::vector<int> demandsEnd, std::vector<int> demandsStart, std::string fileName){

}

void clean(std::string path){
    int nbDemands = 0;
    std::vector<int> demandsStart;
    std::vector<int> demandsEnd;
    std::vector<int> demands;

    int** edges;
    int nbEdges = 0;

    int nbNodes = 0;


    std::vector<std::string> nodesNames;
    std::vector<std::string>::iterator itr;
    int src;
    int dst;  

    std::string line;
    std::fstream f;
    std::vector<std::string> words;
    
    


    int switchos = 0;
    f.open(path);
    if (!f){
        std::cout<<"\ncouldn't load\n"<<std::endl;
    }else{
        std::cout<<"\nsuccessful load\n"<<std::endl;
    }

    //looking for nodes
    std::string keyword = "NODES";
    while(switchos == 0){
        std::getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 1;
            }
        }
    }
    keyword = ")";
    while(switchos == 1){
        std::getline(f,line);
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
        std::getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 1;
            }
        }
    }
    keyword = ")";
    while(switchos == 1){
        std::getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 0;
            }else{
                ++nbEdges;

                itr = std::find(nodesNames.begin(),nodesNames.end(),words[2]);
                src = std::distance(nodesNames.begin(),itr);
                
                itr = std::find(nodesNames.begin(),nodesNames.end(),words[3]);
                dst = std::distance(nodesNames.begin(),itr);

                edges[src][dst] = std::stoi(words[5]);
                edges[dst][src] = std::stoi(words[5]);
            }
        }
    }

    //looking for demands
    keyword = "DEMANDS";
    while(switchos == 0){
        std::getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 1;
            }
        }
    }
    keyword = ")";
    while(switchos == 1){
        std::getline(f,line);
        words = split(line,' ');

        if (!words.empty()){
            if (words[0] == keyword){
                switchos = 0;
            }else{
                ++nbDemands;

                itr = std::find(nodesNames.begin(),nodesNames.end(),words[2]);
                demandsStart.push_back(std::distance(nodesNames.begin(),itr));
                
                itr = std::find(nodesNames.begin(),nodesNames.end(),words[3]);
                demandsEnd.push_back(std::distance(nodesNames.begin(),itr));
                
                demands.push_back(std::stoi(words[6]));
            }
        }
    }

    write(nbNodes, nbEdges, nbDemands, edges, demands, demandsEnd, demandsStart, path);
}
