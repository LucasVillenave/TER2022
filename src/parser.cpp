#include "parser.hpp"
#include <vector>
#include <sstream>
#include <fstream>


std::vector<std::string> split(std::string s, char delim) {
    std::vector<std::string> words;
    std::stringstream ss(s);
    std::string word;
    while (std::getline(ss, word, delim)) {
        words.push_back(word);
    }
    return words;
}



void clean(std::string path){
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
    std::string keyword = "NODES";
    while(switchos == 0){
        std::getline(f,line);
        words = split(line,' ');

        if (words[0] == keyword){
            switchos = 1;
        }
    }
    while(switchos == 1){

    }
}
