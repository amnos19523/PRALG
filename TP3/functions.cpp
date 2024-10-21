#include "functions.h"

std::string gen_name(){
    std::string CAP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string MIN = "abcdefghijklmnopqrstuvwxyz";

    std::string name;
    name+=CAP.at(rand()%26);
    int num = 2 + (rand()%10);
    for (int k=1; k<num; k++){
        name+=MIN.at(rand()%26);
    }
    return name;
}