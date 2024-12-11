// Student: 


//ligne 151 ajouté (Aigne	43	1.883333)

#ifndef srcPath
#define srcPath "."
#endif

#include <iostream>
#include "town.h"
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <vector>
#include <ctime>

using namespace std;

bool verify_in_order(Town v1, Town v2, Town v3, Town v4){
    return (v1.point()==v2.point() && v1.name() == v3.name() && v3.point()==v4.point() && v2.name() == v4.name());
}
    
bool verify(Town v1, Town v2, Town v3, Town v4){
    int count = 0;
    //(v1,v2,v3,v4), (v2,v1,v4,v3), (v3,v4,v1,v2), (v4,v3,v2,v1)
    if (verify_in_order(v1,v2,v3,v4)){
        return true;
    }
    //(v2,v1,v3,v4), (v1,v2,v4,v3), (v3,v4,v2,v1), (v4,v3,v1,v2)
    if (verify_in_order(v2,v1,v3,v4)){
        return true;
    }
    //(v1,v3,v2,v4), (v3,v1,v4,v2), (v2,v4,v1,v3), (v4,v2,v3,v1)
    if (verify_in_order(v1,v3,v2,v4)){
        return true;
    }
    //(v3,v1,v2,v4),n(v1,v3,v4,v2), (v2,v4,v3,v1), (v4,v2,v1,v3)
    if (verify_in_order(v3,v1,v2,v4)){
        return true;
    }
    //(v1,v4,v2,v3)
    if (verify_in_order(v1,v4,v2,v3)){
        return true;
    }
    //(v4,v1,v2,v3)
    if (verify_in_order(v4,v1,v2,v3)){
        return true;
    }
    return false;
}

// Study French isotoponyms
int main(int argc, char* argv[]) {
    string townFile = argc>1? argv[1]: srcPath "/villes.txt";
    vector<Town> towns = Town::read_towns(townFile);

    //Variable nécessaires

    map<string,int> tab_ass;
    string name;
    int number;

    //EXO1
    std::cout<<endl;

    for(vector<Town>::iterator it1= towns.begin() ;it1 != towns.end(); ++it1) {
        name = (*it1).name();
        if (tab_ass.count(name)==0){
           tab_ass.emplace(name,1);
        }
        else{
            tab_ass[name]++;
        }
    }
    map<int,int> question1_tab;
    for (map<string, int>::iterator it2 = tab_ass.begin(); it2 != tab_ass.end(); ++it2) {
        number = it2->second;
        if(question1_tab.count(number)==0){
            question1_tab.emplace(number,1);
        }
        else{
            question1_tab[number]++;
        }
    }
    for (map<int,int>::iterator it3 = question1_tab.begin(); it3 != question1_tab.end(); ++it3){
        std::cout<<it3->second<<" noms de villes ont "<< it3->first<<" emplacements"<<endl;
    }

    // EXO 2
    std::cout<<endl;

    map<Point2D,int>question2_1_tab;
    for(vector<Town>::iterator it1= towns.begin() ;it1 != towns.end(); ++it1) {
        if (question2_1_tab.count(it1->point())==0){
           question2_1_tab.emplace(it1->point(),1);
        }
        else{
            question2_1_tab[it1->point()]++;
        }
    }
    map<int,int> question2_2_tab;
    for (map<Point2D, int>::iterator it2 = question2_1_tab.begin(); it2 != question2_1_tab.end(); ++it2) {
        if(question2_2_tab.count(it2->second)==0){
            question2_2_tab.emplace(it2->second,1);
        }
        else{
            question2_2_tab[it2->second]++;
        }
    }

    for (map<int,int>::iterator it3 = question2_2_tab.begin(); it3 != question2_2_tab.end(); ++it3){
        std::cout<<it3->second<<" emplacements ont exactement "<< it3->first<<" ville(s)"<<endl;
    }

    //EXO 3
    std::cout<<endl;
    
    set<Town> N;
    set<Town> C;

    for(vector<Town>::iterator it1= towns.begin() ;it1 != towns.end(); ++it1) {
        name = (*it1).name();
        if (tab_ass[name]>=2){
           N.emplace(*it1);
        }
    }
    for(vector<Town>::iterator it1= towns.begin() ;it1 != towns.end(); ++it1) {
        if (question2_1_tab[it1->point()]>=2){
           C.emplace(*it1);
        }
    }

    vector<Town> N_int_C(min(N.size(),C.size()));
    vector<Town>::iterator end = set_intersection(N.begin(), N.end(),C.begin(), C.end(), N_int_C.begin());
    N_int_C.resize(end-N_int_C.begin());

    set<Town> N_et_C(N_int_C.begin(), N_int_C.end());

    std::cout<< "il y a " << N_et_C.size() <<" villes dans N inter C" << endl;

    //for(set<Town>::iterator it1 = N_et_C.begin(); it1 != N_et_C.end(); ++it1){
    //    cout<<it1->name()<<endl;
    //}
    //cout<<"ont des homnymes et ont des voisins"<<endl;

    cout<<N_int_C.begin()->name()<<N_int_C.begin()->point()<<endl;

    //EXO 4
    std::cout<<endl;

    // en soi, pour cette exrcice, on peut se restraindre 
    //à l'ensemble N1 inter C1, où N1 et C1 sont les N et C 
    //mais de l'ensemple N inter C.

    set<Town> N1;
    set<Town> C1;

    map<string,int> tab_ass1;

    for(vector<Town>::iterator it1= N_int_C.begin() ;it1 != N_int_C.end(); ++it1) {
        name = (*it1).name();
        if (tab_ass1.count(name)==0){
           tab_ass1.emplace(name,1);
        }
        else{
            tab_ass1[name]++;
        }
    }

    for(vector<Town>::iterator it1= N_int_C.begin() ;it1 != N_int_C.end(); ++it1) {
        name = (*it1).name();
        if (tab_ass1[name]>=2){
           N1.emplace(*it1);
        }
    }

    map<Point2D,int>tab_ass2;
    for(vector<Town>::iterator it1= N_int_C.begin() ;it1 != N_int_C.end(); ++it1) {
        if (tab_ass2.count(it1->point())==0){
           tab_ass2.emplace(it1->point(),1);
        }
        else{
            tab_ass2[it1->point()]++;
        }
    }

    for(vector<Town>::iterator it1= N_int_C.begin() ;it1 != N_int_C.end(); ++it1) {
        if (tab_ass2[it1->point()]>=2){
           C1.emplace(*it1);
        }
    }

    vector<Town> N1_int_C1(min(N1.size(),C1.size()));
    vector<Town>::iterator end1 = set_intersection(N1.begin(), N1.end(),C1.begin(), C1.end(), N1_int_C1.begin());
    N1_int_C1.resize(end1-N1_int_C1.begin());

    set<Town> N1_et_C1(N1_int_C1.begin(), N1_int_C1.end());

    std::cout<< "il y a " << N1_et_C1.size() <<" villes dans N1 inter C1" << endl;

    for(set<Town>::iterator it = N1_et_C1.begin(); it != N1_et_C1.end(); ++it){
        cout<<it->name()<<endl;
    }

    // exemple avec Zutzendorf, Zuytcoote et Zuytpeene
    //l'idéal searait de continuer jusqu'à ce que l'ensemble reste stable.
    //si on fait une troisième fois, Ozon disparait, et nous nous retrouvons avec un ensemble minuscule.
    // Puisque à partir de cet ensemble, on aurait qu'à vérifier très peu d'égalités, je reste sur N inter C pour les calculs de temps.

    map<Point2D,vector<Town>> city_in_same_coord;
    map<string,vector<Town>> same_name_city;

    clock_t s1 = clock();

    for(set<Town>::iterator it = N_et_C.begin(); it != N_et_C.end(); ++it){
        if(city_in_same_coord.count(it->point())==0){
            city_in_same_coord.emplace(it->point(),vector<Town>());
            city_in_same_coord[it->point()].push_back(*it);
        }
        else{
            city_in_same_coord[it->point()].push_back(*it);
        }
        if(same_name_city.count(it->name())==0){
            same_name_city.emplace(it->name(),vector<Town>());
            same_name_city[it->name()].push_back(*it);
        }
        else{
            same_name_city[it->name()].push_back(*it);
        }
    }

    int count_efficient=0;

    // attention on détruit city_in_same_coord, donc faire une copie si on en a besoin après
 
    for (map<Point2D,vector<Town>>::iterator it = city_in_same_coord.begin(); it!= city_in_same_coord.end(); ++it){
        for (vector<Town>::iterator town_it1 = it->second.begin(); town_it1 !=it->second.end(); ++town_it1 ){
            for (vector<Town>::iterator town_it2 = next(town_it1); town_it2 !=it->second.end(); ++town_it2 ){
                // à ce stade coord(v1) = coord(v2)
                // on prend donc toutes les homonymes de town_it1:
                for(vector<Town>::iterator town_it3 = same_name_city[town_it1->name()].begin(); town_it3 != same_name_city[town_it1->name()].end(); ++town_it3){
                    // nom(v1) = nom(v3)
                    if ((*town_it3)!=(*town_it1)){
                        for(vector<Town>::iterator town_it4 = city_in_same_coord[town_it3->point()].begin(); town_it4 !=city_in_same_coord[town_it3->point()].end(); ++town_it4){
                            //town_it4 est dans la meme zone que town_it3
                            //reste donc plus qu'à vérifier nom(v2)=nom(v4)
                            if ((*town_it3)!=(*town_it4)){
                                if (town_it2->name() == town_it4->name()){
                                    count_efficient++;
                                }
                            }
                        }
                    }
                }
            }
        }
        city_in_same_coord[it->first] = vector<Town>();
    }

    clock_t e1 = clock();


    std::cout<<"nombre de de villes on où peut se tromper en entendant parler d'une ville A toute proche d'une ville B"<<count_efficient<<endl;
    std::cout<<"temps de calcul : "<< e1-s1 <<endl;


    //EXO 5
    std::cout<<endl;
    
    int count = 0;
    int wait  = 0;

    clock_t s2 = clock();

    for(set<Town>::iterator it = N_et_C.begin(); it != N_et_C.end(); ++it){
        for(set<Town>::iterator it1 = next(it); it1 != N_et_C.end(); ++it1){
            for(set<Town>::iterator it2 = next(it1); it2 != N_et_C.end(); ++it2){
                for(set<Town>::iterator it3 = next(it2); it3 != N_et_C.end(); ++it3){
                    //coord(v1)=coord(v2), nom(v1)=nom(v3), coord(v3)=coord(v4), nom(v2)=nom(v4)
                    // with all permutations
                    if (verify(*it,*it1,*it2,*it3)){
                        count++;
                    }
                }
            }
        }
    }

    clock_t e2 = clock();
    std::cout<<"temps de calcul pour l'algo lent : "<< e2-s2 <<endl;




    return 0;
}
