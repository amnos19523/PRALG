#include "lib.h"
#include <cmath>
#include <cstdlib>



float Fonction::inverse(float y) const{
    int count(0);
    double x = 1;
    double diff=1;
    while((std::abs(diff) > 0.00001)&&(count<100)){
        diff = (y-(*this)(x))/(*(this->derivee()))(x);
        x += diff;
        count++;
    }
    return x;
    }; // to change

float Polynome::operator() (float x) const{
    float result = coef[0];
    for (int i=1; i<deg; i++){
        result += coef[i]*pow(x, i);
    }
    return result;
};


Polynome::Polynome(float* coeff, int degr){
    if (degr<0){throw std::invalid_argument("no negative degree");}
    deg =degr;
    coef = new float[deg];
    for (int k=0; k<deg; k++){coef[k] = coeff[k];}
}

Fonction* Polynome::derivee() const{
    if (deg==2){
        return new Affine(coef[1], 2 * coef[2]);
    }
    if (deg == 1){
        return new Constante(coef[1]);
    }
    if (deg == 0){
        return new Constante(0);
    }
    float* nv_coefs = new float[deg-1];
    for (int i=1; i<deg; i++){
        nv_coefs[i-1] = coef[i]*i;
    }
    return new Polynome(nv_coefs, deg-1);
};

Trigo::Trigo(std::string func){
    if ((func == "cos")){
        fonction = std::cos;
        numero = 1;
    }
    else{
        if ((func == "sin")){
            fonction = std::sin;
            numero = 0;
        }
        else{
            if (func == "tan"){
                fonction = std::tan;
                numero = 5;
            }
            else {throw std::invalid_argument("not trigonometric function");}
        }
    }
};

Trigo::Trigo(int k){
    if ((k>=0)||(k<=3)){
        numero = k;
        if(k==0){fonction = std::sin;}
        if(k==1){fonction = std::cos;}
        if(k==2){fonction = [](double x) { return -std::sin(x); };}
        if(k==3){fonction = [](double x) {return -std::cos(x);};}
    }
    else{
        throw std::invalid_argument("entre 0 et 4");
    }
}



float Trigo::operator() (float x) const{
    return fonction(x);
}

Fonction* Trigo::derivee() const {
    if (numero == 5){
        return new RandomFunction([](float x){return static_cast<float>(1 + std::pow(std::tan(x),2));});
    }
    return new Trigo((numero+1)%4);
};


float Derivee::operator() (float x) const {
    double epsilon = 0.01;
    double f1 = (*Primitive)(x+epsilon);
    double f2 = (*Primitive)(x-epsilon);
    return (f1-f2)/(2*epsilon);
};







