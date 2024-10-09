#include "IntTree.h"
#include <stdio.h>
#include<iostream>

int main(){
    IntTree* root = new IntTree(12);
    root->addAsLastChild(new IntTree(8));
    root->getChild(0)->addAsLastChild(new IntTree(4));
    root->getChild(0)->addAsLastChild(new IntTree(9));
    root->addAsLastChild(new IntTree(23));
    root->getChild(1)->addAsLastChild(new IntTree(17));
    root->getChild(1)->getChild(0)->addAsLastChild(new IntTree(15));

    root->visTreeIm();
    root->display();
    
    delete root;
    return 0;
}
