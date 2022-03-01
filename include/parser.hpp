#ifndef PARSER
#define PARSER

#include "graph.hpp"
#include <string>


namespace TER{
    //only load an instance that have been cleaned and from wich we added q and u
    graph load(std::string path);

    //clean a rought SNDlib native network to keep only the needed data, also add q and u 
    void clean(std::string path);

    //cleaned version of instances will be named cleanedINSTANCE_NAME.txt
}

#endif