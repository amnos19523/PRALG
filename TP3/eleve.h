#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

class Eleve{
    private:
        std::string name;
        int grade;
    public : 
        Eleve();
        Eleve(std::string nom);
        Eleve(std::string nom, int note);
        int note() const;
        int& note();
        std::string nom() const;
        void afficher() const;
};

class CompareNom{
        std::vector<Eleve> classe;
    public: 
        CompareNom(std::vector<Eleve> liste){
            classe.reserve(liste.size());
            for (int k=0; k < liste.size();k++){
                classe.push_back(liste.at(k))
            }
        }
}