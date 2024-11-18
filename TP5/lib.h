#pragma once
#include <stdexcept>
#include <cmath>
#include <cstring>


class Fonction{
    public:
    
        Fonction() {};
        Fonction(Fonction* func){};
        virtual ~Fonction() {};
        virtual float operator() (float x) const = 0;
        virtual Fonction* derivee() const = 0;
        virtual float inverse(float y) const  ;  // défini dans cpp PENDING
        virtual Fonction* clone() const = 0;
};

class Derivee: public Fonction{
    private:

        Fonction * Primitive;
    
    public : 

        Derivee() {};
        Derivee(Fonction* prim) {Primitive = prim->clone();}
        ~Derivee() {delete Primitive;};
        float operator() (float x) const;   // défini dans cpp OK
        Fonction* derivee() const {
            return new Derivee(Primitive->derivee());};
        Fonction* clone() const {return new Derivee(Primitive->clone());}

};

class Constante: public Fonction{
    private:

        float constante;

    public:

        Constante(float a) {constante = a;};
        ~Constante(){};
        float operator() (float x) const {return constante;};
        Fonction* derivee() const {return new Constante(0.0);};
        float inverse(float y) const {if (y==constante){return 0;}throw std::domain_error("pas d'antécédent");}
        Fonction* clone() const {return new Constante(constante);};

};

class Polynome: public Fonction{
    protected : 

        float* coef;
        int deg;

    public:

        Polynome() {};
        Polynome(float* coeff, int degr);           // défini dans cpp OK (is already copy)
        virtual ~Polynome() {delete[] coef;};
        virtual float operator() (float x) const;   // défini dans cpp OK
        virtual Fonction* derivee() const;          // défini dans cpp OK
        // pas besoin de définir l'inverse
        Fonction* clone() const {return new Polynome(coef, deg);};

};

class Affine: public Polynome{
    private : 

        float a,b;

    public:
        Affine() {};
        Affine(float constante, float facteur) {a = facteur; b = constante; deg = 1;};
        virtual ~Affine() {};
        virtual float operator() (float x) const {return (a*x) + b;};
        virtual Fonction* derivee() const {return new Constante(a); };
        virtual float inverse(float y) const {if (a==0){if (y==b){return 0;}throw std::domain_error("pas d'antécédent");}else{return (y-b)/a;}};
        Fonction* clone() const {return new Affine(b, a);};
};


class Trigo: public Fonction{
    protected : 

        double (*fonction)(double);
        int numero;
    
    public: 

        Trigo() {fonction = std::cos;};
        Trigo(std::string func);    // défini dans cpp OK
        Trigo (int k);              // défini dans cpp OK
        virtual ~Trigo() {};
        virtual float operator() (float x) const; // défini dans cpp OK
        virtual Fonction* derivee() const ; // défini dans cpp OK
        Fonction* clone() const {return new Trigo(numero);};

};

class RandomFunction: public Fonction{
    private:

        float (*fonction)(float);

    public: 

        RandomFunction() {};
        RandomFunction(float (*func)(float)) {fonction = func;};
        ~RandomFunction() {};
        float operator() (float x) const {return fonction(x);};
        Fonction* derivee() const {return new Derivee(this->clone());};
        Fonction* clone() const {return new RandomFunction(fonction);};
};

