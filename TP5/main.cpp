#include <cstdio>
#include <cmath>
#include "lib.h"


int main(){

    const int degree = 2 ; 
    float* coefs = new float[degree];
    for (int k=0; k<degree; k++){
        coefs[k] = 1;
    }
    Fonction* fonctionun = new Polynome(coefs, degree);
    printf("%f\n", (*fonctionun)(52.7));
    Fonction* deriveeun;
    deriveeun = fonctionun->derivee();
    printf("%f\n", (*deriveeun)(52.7));


    std::string strig = "tan";
    Fonction* tang = new Trigo(strig);
    printf("%f\n", (*tang)(3.141));
    Fonction* derivet;
    derivet = tang->derivee();
    printf("%f\n", (*derivet)(12));


    Fonction* Randfunc;
    Fonction* Randomder;
    Fonction* Randomder2;
    Fonction* Randomder3;
    Randfunc = new RandomFunction([](float x){return x*std::exp(x);});
    
    Randomder = Randfunc->derivee();
    Randomder2 = Randomder->derivee();
    Randomder3 = Randomder2->derivee();
    printf("%f\n", (*Randomder3)(2));
    printf("%f\n", Randomder2->inverse(35));

    Fonction* exo1;
    float* coefi = new float[4];
    coefi[0]=0;
    coefi[1]=0;
    coefi[2]=0;
    coefi[3]=1;
    exo1 = new Polynome(coefi, 4);
    printf("%f\n", exo1->inverse(27));
    printf("%f\n", 4*tang->inverse(1));
    return 1; 

}