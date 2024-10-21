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
    private: 
        int* ptr;
    public:
        CompareNom(): ptr(new int(0)){}
        CompareNom(int& compteur){ptr = &compteur;}
        bool operator()(Eleve i, Eleve j)const {
            (*ptr)++;
            return i.nom() < j.nom();
            };
};

class CompareNote{
    private:
        int* ptr;
    public:
    CompareNote(): ptr(new int(0)){}
    CompareNote(int& compteur){ptr = &compteur;}
        bool operator()(Eleve i, Eleve j)const {
            (*ptr)++;
            return i.note() > j.note();
            };
};