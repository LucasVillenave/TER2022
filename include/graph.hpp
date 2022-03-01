#ifndef GRAPH
#define GRAPH
#include <iostream>

namespace TER{
    class graph{
        private :
            int n;
            int** u;
        public :
            graph(int n,int** u){
                this->n=n;
                this->u=u;
            }

            int getN(){
                return n;
            }

            int** getU(){
                return u;
            }

            int getU(int s,int d){
                return u[s][d];
            }
    };
}

#endif