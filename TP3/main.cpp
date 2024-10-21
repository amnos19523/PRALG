#include "eleve.h"
#include "functions.h"
#include <stdio.h>
#include <iostream>
#include <vector>

int main(){
    srand(time(NULL));
    Eleve Jean("Jean", 15);
    Jean.afficher();
    Jean.note()=12;
    Jean.afficher();
    std::vector<Eleve> classe(20);
    std::cout<<gen_name()<<std::endl;
    for (int k=0;k<20; k++){
        classe[k].afficher();
    }
}
