#include <Imagine/Graphics.h>
#include <iostream>
#include "quadtree/quadtree.h"
#include <stdio.h>
#include <algorithm>
#include <cstdlib>

using namespace std;

// The path and name of the town file
const char* default_image_file=srcPath("grayscale-image.png");
const char* default_image_file1=srcPath("lena_gray.png");
const char* default_image_file2=srcPath("running-horse-rect.png");

// defining white and black

int white = 255;
int black = 0;

// defining global QuadLeaf

QuadLeaf<bool> Blackleaf(true);
QuadLeaf<bool> Whiteleaf(false);

int superior2 (int n){
  if (n<=0){
    return 0;
  }
  int answer = 1;
  while (answer<n){
    answer = answer*2;
  }
  return answer;
}


QuadTree<bool>* Encode(::byte* Image, int wi, int hi, int x, int y, int width, int height, bool checkdim=false) {
if (checkdim){
  int hidim = max(hi,wi);
  hi = superior2(hidim);
  wi = hi;
  printf("size of image is %d\n", wi);
  }
  if (wi==1 && hi==1){
    if ((x>=width)||(y>=height)){ // check if image in bound
      return new QuadLeaf<bool>(false);
      }
    int i  = Image[x + (y*width)];
      if (i==black){
        return new QuadLeaf<bool>(true);
      }
      else{
        return new QuadLeaf<bool>(false);
      };
    }
  //create 4 blocks
  QuadTree<bool>*SH = Encode(Image, wi/2, hi/2, x, y, width, height);
  QuadTree<bool>*TH = Encode(Image, wi/2, hi/2, x+(wi/2), y, width, height);
  QuadTree<bool>*TN = Encode(Image, wi/2, hi/2, x+(wi/2), y+(hi/2), width, height);
  QuadTree<bool>*SN = Encode(Image, wi/2, hi/2, x, y+(hi/2), width, height);
   // if leaf ?
  if(SH->isLeaf() && TH->isLeaf() && TN->isLeaf() && SN->isLeaf()){
    // all black case
    if((SH->value()==true)&&(TH->value()==true)&&(TN->value()==true)&&(SN->value()==true)){
        return &Blackleaf;
      }
    // all white case
    else if((SH->value()==false)&&(TH->value()==false)&&(TN->value()==false)&&(SN->value()==false)){
        return &Whiteleaf;
        }
      }
        // neither all black or all white
  return new QuadNode<bool>(SH, TH, TN, SN);        
}

int Decode(::byte* image, QuadTree<bool>* Tree, int width, int height, int wi, int hi, int x=0, int y=0, bool drawsq = true, bool verify2pow = false){
  if (verify2pow){
    int hidim = max(hi,wi);
    hi = superior2(hidim);
    wi = hi;
    printf("size of image is %d\n", wi);
  }
  if (Tree->isLeaf()){
      int data = (Tree->value())? 0:255; // inverser 255 et 0 (pour voir que on a bien décodé l'image)
      int invdata = (Tree->value())? 255:0;
    for (int i=0; i<(min(wi,width-x)); i++){
      for (int j=0; j<(min(hi, height-y)); j++){
        image[(x+i)+((y+j)*width)] = data;
      }
    }
    // définition des bords
    // définition que des bords nord et ouest. enlever le commentaire pour épaissir les bords
    if ((drawsq)&&(x<width)&&(y<height)){
      for(int i=0; i<min(wi,width-x);i++){
        image[(x+i)+((y)*width)] = invdata;
        //image[(x+i)+((y+min(hi, height-y)-1)*width)] = invdata; 
      }
      for(int j=0; j<min(hi, height-y);j++){
        image[(x)+((y+j)*width)] = invdata;
        //image[(x+min(wi,width-x)-1)+((y+j)*width)] = invdata;
      }
    }
  }
  else{
    Decode(image,Tree->child(0), width, height, wi/2, hi/2, x, y, drawsq);
    Decode(image,Tree->child(1), width, height, wi/2, hi/2, x+(wi/2), y, drawsq);
    Decode(image,Tree->child(2), width, height, wi/2, hi/2, x+(wi/2), y+(hi/2), drawsq);
    Decode(image,Tree->child(3), width, height, wi/2, hi/2, x, y+(hi/2), drawsq);
  }
  return 0;
}

int get_moy(::byte* list, int nb_liste){
  int moy =0;
  for (int k = 0; k < nb_liste; k++){
    moy += list[k];
  }
  moy = moy/nb_liste;
  return moy;
}

bool compare(::byte* list, int nb_liste, int seuil){
  int moy=get_moy(list, nb_liste);
  int diff = 0;
  int adder;
  for (int k = 0; k < nb_liste; k++){   // LSE
    adder= abs(list[k]-moy);
    diff += (adder*adder);
  }
  diff = diff / nb_liste;
  if(diff <= seuil){
    return true;
  }
  return false;
}


QuadTree<::byte>* Encode_grey(::byte* Image, int wi, int hi, int x, int y, int width, int height, int seuil, bool checkdim=false) {
if (checkdim){
  int hidim = max(hi,wi);
  hi = superior2(hidim);
  wi = hi;
  printf("size of image is %d\n", wi);
  }
  if (wi==1 && hi==1){
    if ((x>=width)||(y>=height)){ // check if image in bound
      return new QuadLeaf<::byte>(0);
      }
    ::byte i  = Image[x + (y*width)];
    return new QuadLeaf<::byte>(i);
    }
  //create 4 blocks
  QuadTree<::byte>*SH = Encode_grey(Image, wi/2, hi/2, x, y, width, height, 3*seuil/4);
  QuadTree<::byte>*TH = Encode_grey(Image, wi/2, hi/2, x+(wi/2), y, width, height, 3*seuil/4);
  QuadTree<::byte>*TN = Encode_grey(Image, wi/2, hi/2, x+(wi/2), y+(hi/2), width, height, 3*seuil/4);
  QuadTree<::byte>*SN = Encode_grey(Image, wi/2, hi/2, x, y+(hi/2), width, height, 3*seuil/4);
   // if leaf ?
  if(SH->isLeaf() && TH->isLeaf() && TN->isLeaf() && SN->isLeaf()){
    // all black case
    ::byte* list = new ::byte(4);
    list[0] = SH->value();
    list[1] = TH->value();
    list[2] = TN->value();
    list[3] = SN->value();
    if(compare(list, 4, seuil)){
        return new QuadLeaf<::byte>(get_moy(list, 4));
      }
      }
        // neither all black or all white
  return new QuadNode<::byte>(SH, TH, TN, SN);        
}


int Decode_grey(::byte* image, QuadTree<::byte>* Tree, int width, int height, int wi, int hi, int x=0, int y=0, bool drawsq = true, bool verify2pow = false){
  if (verify2pow){
    int hidim = max(hi,wi);
    hi = superior2(hidim);
    wi = hi;
    printf("size of image is %d\n", wi);
  }
  if (Tree->isLeaf()){
      int data = Tree->value();
    for (int i=0; i<(min(wi,width-x)); i++){
      for (int j=0; j<(min(hi, height-y)); j++){
        image[(x+i)+((y+j)*width)] = data;
      }
    }
    // définition des bords
    // définition que des bords nord et ouest. enlever le commentaire pour épaissir les bords
    if ((drawsq)&&(x<width)&&(y<height)){
      for(int i=0; i<min(wi,width-x);i++){
        image[(x+i)+((y)*width)] = 0;
        //image[(x+i)+((y+min(hi, height-y)-1)*width)] = invdata; 
      }
      for(int j=0; j<min(hi, height-y);j++){
        image[(x)+((y+j)*width)] = 0;
        //image[(x+min(wi,width-x)-1)+((y+j)*width)] = invdata;
      }
    }
  }
  else{
    Decode_grey(image,Tree->child(0), width, height, wi/2, hi/2, x, y, drawsq);
    Decode_grey(image,Tree->child(1), width, height, wi/2, hi/2, x+(wi/2), y, drawsq);
    Decode_grey(image,Tree->child(2), width, height, wi/2, hi/2, x+(wi/2), y+(hi/2), drawsq);
    Decode_grey(image,Tree->child(3), width, height, wi/2, hi/2, x, y+(hi/2), drawsq);
  }
  return 0;
}



int main(int argc, char **argv) {
    // make bool leaf protected 
    QuadTree<bool>::protect_leaves_from_destruction = true;

    //code
    string image_file = (argc>1)? argv[1]: default_image_file;
    ::byte* image;
    int width, height;
    cout << "Loading image: " << image_file << endl; 
    if(! Imagine::loadGreyImage(image_file, image, width, height)) {
        cerr << "Error loading image file " << image_file << endl;
        return 1;
    }

    // Print statistics
    cout << "Image size: " << width << "x" << height << endl;
    cout << "Number of pixels: " << width*height << endl;




    // Display image
    Imagine::Window window1 = Imagine::openWindow(width, height);
    Imagine::putGreyImage(0, 0, image, width, height);

    Imagine::endGraphics(); 

    QuadTree<::byte>* im1 = Encode_grey(image, width, height, 0, 0, width, height, 100, true);

    //display<bool>(im);

    ::byte* Image2;
    Image2 = new ::byte[width*height];

    Decode_grey(Image2, im1, width, height, width, height, 0, 0, false, true); // put false to not make appear the little squares.

    // Display image
    Imagine::putGreyImage(0, 0, Image2, width, height);

    Imagine::endGraphics();

//_________________________________________________________

    image_file = (argc>2)? argv[2]: default_image_file1;
    cout << "Loading image: " << image_file << endl; 
    if(! Imagine::loadGreyImage(image_file, image, width, height)) {
        cerr << "Error loading image file " << image_file << endl;
        return 1;
    }

    // Print statistics
    cout << "Image size: " << width << "x" << height << endl;
    cout << "Number of pixels: " << width*height << endl;

    Imagine::Window window2 = Imagine::openWindow(width, height);
    Imagine::setActiveWindow(window2);

    // Display im 2
    Imagine::putGreyImage(0, 0, image, width, height);

    Imagine::endGraphics(); 

    QuadTree<::byte>* im2 = Encode_grey(image, width, height, 0, 0, width, height, 100, true);

    //display<bool>(im);

    Image2 = new ::byte[width*height];

    Decode_grey(Image2, im2, width, height, width, height, 0, 0, true, true); // put false to not make appear the little squares.

    // Display image
    Imagine::putGreyImage(0, 0, Image2, width, height);

    Imagine::endGraphics();

  //_________________________________________________________________________

    image_file = (argc>1)? argv[1]: default_image_file2;
    cout << "Loading image: " << image_file << endl; 
    if(! Imagine::loadGreyImage(image_file, image, width, height)) {
        cerr << "Error loading image file " << image_file << endl;
        return 1;
    }

    // Print statistics
    cout << "Image size: " << width << "x" << height << endl;
    cout << "Number of pixels: " << width*height << endl;

    Imagine::Window window3 = Imagine::openWindow(width, height);
    Imagine::setActiveWindow(window3);

    // Display im 2
    Imagine::putGreyImage(0, 0, image, width, height);

    Imagine::endGraphics(); 

    QuadTree<bool>* im3 = Encode(image, width, height, 0, 0, width, height, true);

    //display<bool>(im);

    Image2 = new ::byte[width*height];

    Decode(Image2, im3, width, height, width, height, 0, 0, true, true); // put false to not make appear the little squares.

    // Display image
    Imagine::putGreyImage(0, 0, Image2, width, height);

    Imagine::endGraphics();



    return 0;
}
