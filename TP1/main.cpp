#include "matrice.h"
#include <stdio.h>

int main(){

    if(false){
        Matrice M(2,2);
        M(0,0)=1.5;
        M(1,1)=34.6;
        M.affiche();
        Matrice N(2,2);
        N(1,1)=1;
        N(0,0)=5;
        Matrice O(1,2);
        O = M*N;
        printf("%d\n",*O.count);
        N.affiche();
        O.affiche();
        Matrice P(3,2);
        O=P*N;
        O.affiche();
        Matrice Q(M);
        Q(1,0)=12.75;
        M.affiche();
        printf("%d\n",*M.count);
        printf("%d\n",*Q.count);
    }   
    // marche pas

    Matrice E,F;
    E.resize(5,6);
    F.resize(6,2);
    for (int k=0; k<5; k++){
        E(k,k)=3;
        F(k, k%2) = 2;
    }

    double* tableau;
    E.affiche();
    F.affiche();
    Matrice K;
    K = E*F;
    K.affiche();
    return 0;
    
}