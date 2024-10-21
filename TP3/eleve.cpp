#include "eleve.h"
#include "functions.h"

Eleve::Eleve(){
    name = gen_name();
    grade = rand()%21;
}
Eleve::Eleve(std::string nom){
    name = nom;
}
Eleve::Eleve(std::string nom, int note){
    name = nom;
    grade = note;
}

int Eleve::note() const{
    return grade;
}
int& Eleve::note(){
    return grade;
}

std::string Eleve::nom() const{
    return name;
}

void Eleve::afficher()const{
    std::cout << name << "   " << grade << std::endl;
}
