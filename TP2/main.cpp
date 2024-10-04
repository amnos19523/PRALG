#include "IntTree.h"
#include <stdio.h>
#include<iostream>

int main(){
    IntTree A(1),B(2),C(3),D(4),E(5),F(6),G(7);
    A.addAsLastChild(&B);
    A.addAsLastChild(&C);
    A.addAsLastChild(&E);
    B.addAsLastChild(&D);
    E.addAsLastChild(&F);
    E.addAsLastChild(&G);
    A.visTreeIm();
    return 0;
}
