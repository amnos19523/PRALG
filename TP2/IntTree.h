#pragma once
#include <vector>
#include <string>

// Node of a tree containing an integer at each node
class IntTree {
    // Node information
    int data;
    // Sequence of children (empty if none)
    std::vector<IntTree*> children;
public:
    IntTree();
    // Create a node with given information
    IntTree(int d);
    // Destruct a node and all its descendents
    ~IntTree();
    // Return information of this node
    int getData() const;
    // Set information of this node
    void setData(int d);
    // Return the number of children of this node
    int nbChildren() const;
    // Return the child at pos, if any (left-most child at position 0)
    IntTree* getChild(int pos);
    // Replace the exisiting child at pos (left-most child at position 0) 
    void setChild(int pos, IntTree* newChild);
    // Add newChild as supplementary right-most child of this node
    void addAsLastChild(IntTree* newChild);
    // Remove right-most child of this node
    void removeLastChild();
    // return depth
    int depth();
    //parcours en profondeur
    void display(std::string prefix="*" , std::string indent="  ")const;
    // get size at bottom
    int get_tree_widest_size();
    //list of data in Tree
    int** get_tree_list();
    //makestring
    void visTreeIm();
};
