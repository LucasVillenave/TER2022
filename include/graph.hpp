#ifndef GRAPH
#define GRAPH
#include <iostream>

namespace TER{
    class graph{
        private :
            //nb nodes
            int n;

            //different services levels as described in the paper
            int hq;
            int mq;
            int lq;

            //capacity matrix, equal -1 if nodes aren't adjacent
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