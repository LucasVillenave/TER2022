#include "parser.hpp"
#include <vector>
#include <sstream>
#include <fstream>

namespace TER{
    std::vector<std::string> split(std::string s, char delim) {
        std::vector<std::string> words;
        std::stringstream ss(s);
        std::string word;
        while (std::getline(ss, word, delim)) {
            words.push_back(word);
        }
        return words;
    }
}


void TER::clean(std::string path){
    std::string line;
    std::fstream f;
    std::vector<std::string> words;
    int switch = 0;
    f.open(path);
    if (!f){
        std::cout<<"\ncouldn't load\n"<<std::endl;
    }else{
        std::cout<<"\nsuccessful load\n"<<std::endl;
    }
    while(switch == 0){
        std::getline(f,line);
        words = TER::split(line,' ');
        if (words[0].equals("NODES")){
            switch = 1;
        }
    }
    while(switch == 1){

    }

}