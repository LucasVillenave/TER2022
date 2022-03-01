#ifndef PARSER
#define PARSER

#include "Instance.hpp"
#include <string>



//only load an instance that have been cleaned and from wich we added q and u
Instance load(std::string path);

//clean a rought SNDlib native network to keep only the needed data, also add q and u
void clean(std::string path);

//cleaned version of instances will be named cleanedINSTANCE_NAME.txt


#endif
