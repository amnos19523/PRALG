#include "eleve.h"
#include "functions.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int compteur=0;
    srand(time(NULL));
    Eleve Jean("Jean", 15);
    Jean.afficher();
    Jean.note()=12;
    Jean.afficher();
    std::vector<Eleve> classe(20);
    std::cout<<"random name"<< std::endl<<gen_name()<<std::endl<<std::endl;
    printf("\n");
    std::cout<<"Désordonné"<<std::endl;
    for (int k=0;k<20; k++){
        classe[k].afficher();
    }
    printf("\n");
    std::sort(classe.begin(), classe.end() ,CompareNom(compteur));
    std::cout<<"Ordre Alphabétique"<<std::endl;
    for (int k=0;k<20; k++){
        classe[k].afficher();
    }
    std::cout<<"nombre de tri: "<< compteur << std::endl;
    compteur = 0;
    printf("\n");
    std::sort(classe.begin(), classe.end() ,CompareNote(compteur));
    std::cout<<"Note décroissante"<<std::endl;
    for (int k=0;k<20; k++){
        classe[k].afficher();
    }
    std::cout<< "nombre de tri : "<<compteur << std::endl;
}
