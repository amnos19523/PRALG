#include "IntTree.h"
#include <vector>
#include <stdio.h>
#include <iostream>

IntTree::IntTree(){
}

IntTree::IntTree(int d){
    data = d;
}

IntTree::~IntTree(){
    for (int k=0;k<children.size();k++){
        children[k]=nullptr;
    }
    children.clear();
}

int IntTree::getData()const{
    return data;
}

void IntTree::setData(int d){
    data = d;
}

int IntTree::nbChildren()const{
    return children.size();
}

IntTree* IntTree::getChild(int pos){
    return children[pos];
}

void IntTree::setChild(int pos, IntTree* NewChild){
    children.push_back(children[pos]);
    children[pos]=NewChild;
}

void IntTree::addAsLastChild(IntTree* NewChild){
    children.push_back(NewChild);
}

void IntTree::removeLastChild(){
    //delete children.back();
    children.back()=nullptr;
    children.pop_back();
}

int IntTree::depth(){
    if (children.size()==0){
        return 1;
    }
    else{
        int depth = 1;
        for (int k=0; k<children.size(); k++){
            int d = (*children[k]).depth();
            if (d>depth){
                depth = d;
            }
        }
        depth +=1;
        return depth;
    }
}


void IntTree::display(std::string prefix, std::string indent) const{

    std::cout << prefix <<indent<<getData()<<std::endl;
    for (int k=0; k < nbChildren();k++){
        (*children[k]).display(prefix+indent,indent);
    }
}



int** IntTree::get_tree_list(){

    int initial_depth = depth();

    int** list = new int*[(initial_depth*2)+1];
    list[(2*initial_depth)] = new int[initial_depth];
    list[initial_depth*2][0]=1;
    list[0]= new int [1];
    list[initial_depth+0] = new int[1];
    list[0][0]= getData();
    list[initial_depth][0]=1;
    //initialize stage_size
    if (initial_depth == 1 ){
        return list;
    }
    int stage_size = children.size();
    list[initial_depth+0][0]=stage_size;
    list[1] = new int[stage_size];
    IntTree** this_stage = new IntTree*[stage_size];
    for(int i=0; i<stage_size;i++){
        this_stage[i] = children[i];
    }
    for (int k=0; k<stage_size; k++){
        list[1][k]= (*this_stage[k]).getData();
    }
    list[initial_depth*2][1]=stage_size;
    if (initial_depth==2){
        //make info list ?
        return list;
    }
    // search every stage 
    int next_stage_size = 0;
    IntTree** next_stage = nullptr;
    int counter;
    for (int k=2; k<initial_depth; k++){
        // define new stage size
        list[initial_depth+(k-1)] = new int[stage_size];
        next_stage_size = 0;
        for (int l=0; l<stage_size; l++){
            list[initial_depth+(k-1)][l] = (*this_stage[l]).nbChildren();
            next_stage_size += (*this_stage[l]).nbChildren();
        }
        // do not Delete pointer of next_stage
        //define next_stage
        counter = 0;
        next_stage = new IntTree*[next_stage_size];
        list[k] = new int[next_stage_size];
        for (int l=0; l<stage_size; l++){
            for (int m=0;m<(*this_stage[l]).nbChildren();m++){
                next_stage[counter] = (*this_stage[l]).getChild(m);
                counter+=1;
            }
        }
        //update stage_size :
        stage_size = next_stage_size;
        for (int l=0; l<stage_size; l++){
            list[k][l]= (*next_stage[l]).getData();
        }
        // delete this_stage
        this_stage = next_stage;
        list[initial_depth*2][k]=next_stage_size;
    }
    return list;
}



int IntTree::get_tree_widest_size(){
    int max = 0;
    int comp;
    int** tree = get_tree_list();
    for (int k=0; k<depth(); k++){
        comp = (get_tree_list())[depth()*2][k];
        if (comp>max){
            max = comp;
        }
    }
    return max;
}


void IntTree::visTreeIm(){
    int* tree_size = nullptr;
    int space;
    int** tree = get_tree_list();
    //printf("%d\n",get_tree_widest_size());
    tree_size = tree[depth()*2];
    for (int k =0; k<(depth());k++){
        printf("\n");
        for (int l =0; l<tree_size[k]; l++){
            printf("|%d|", tree[k][l]);
        }
    }
    printf("\n");
}

