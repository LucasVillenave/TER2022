#include "modelSolving.hpp"
using namespace std;

//ToDo
int arcCapacity(Instance* i){
    int s = 0;
    for (int d:i->demands){
        s+=d;
    }
    return s;
}