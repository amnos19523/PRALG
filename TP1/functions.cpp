#include "functions.h"
#include <string>
#include <cctype>
using namespace std;

int count_double_size(double a){
    // helped by AI
    string str = to_string(a);
    int decimal_pos = str.find('.');
    if (decimal_pos == string::npos) { // no decimal point
        return str.size(); // return the entire length of the string
    }
    return decimal_pos; // return the position of the decimal point
}

void print_double(double d, int a){
    string str = to_string(d);
    for(int k=0;k<a;k++){
        printf("%c", str[k]);
    }
}

