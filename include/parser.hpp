#ifndef PARSER
#define PARSER

#include "Instance.hpp"
#include <string>
#include <vector>



//only load an instance that have been cleaned and from wich we added q
Instance* load(std::string path);

//clean a rought SNDlib native network to keep only the needed data, also add q
void clean(std::string path);

//cleaned version of instances will be named cleanedINSTANCE_NAME.txt
void Gwrite(int nbNodes, int nbEdges, int nbDemands, int** edges, std::vector<int> demands, std::vector<int> demandsEnd, std::vector<int> demandsStart, std::string fileName);

#endif
