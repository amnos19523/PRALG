#include "matrice.h"
#include <stdio.h>

int main(){
    try{

        if(true){
            Matrice M(2,2);
            M(0,0)=1.5;
            M(1,1)=34.6;
            M.affiche();
            Matrice N(2,2);
            N(1,1)=1;
            N(0,0)=5;
            Matrice O(1,2);
            printf("%d\n",*O.count);    
            N.affiche();
            O.affiche();
            Matrice P(3,2);
            O.affiche();
            Matrice Q(M);
            //segmentation fault
            Q.affiche();
            Q(1,0)=12.75;
            M.affiche(); //test shallow copy
            printf("%d\n",*M.count);
            printf("%d\n",*Q.count);
        }   

        Matrice E,F;
        E.resize(5,5);
        F.resize(6,2);
        for (int k=0; k<5; k++){
            E(k,k)=3;
            F(k, k%2) = 2;
        }

        E.affiche();
        F.affiche();
        Matrice K;
        (E*F).affiche();
        K.affiche();
        return 0;
    }
    

    catch(const char* message){
        printf(message);
        printf("\nRewrite main.cpp\n\n");
        return 0;

    }

}