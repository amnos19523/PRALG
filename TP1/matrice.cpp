#include "matrice.h"
#include <stdio.h>
#include <cassert>
#include "functions.h"

#if defined(__linux__)
    #include <unistd.h>
    #include <sys/ioctl.h>
#elif defined(_WIN32)
    #include <windows.h>
#endif

Matrice::Matrice(){
    count = new int;
    *count = 1;
    L=1;
    C=1;
    tab = new double[1];
    tab[0] = 0;
    printf("default Matrix constructed\n");
}



Matrice::Matrice(int a, int b){
    count = new int;
    *count = 1;
    L = a;
    C = b;
    tab = new double[L*C];
    for(int i=0;i<L*C;i++){
        tab[i]=0;
    }
    printf("0 Matrix constructed \n");
};

Matrice::Matrice(const Matrice& copy){
    count=new int;
    count = copy.count;
    (*count)++;
    L=copy.L;
    C=copy.C;
    printf("Matrix copied\n");
};

Matrice::~Matrice(){
    (*count)--;
    if (*count == 0){
        delete[] tab;
        printf("Matrix deleted\n");
    }
    else{
        printf("there is still %d copies of this Matrix\n", *count);
    }
}


void Matrice::resize(int a, int b){
    double* NewMatrix = new double[a*b];
    L=a;
    C=b;
    for(int l=0 ; l<L ; l++){
        for(int c=0; c<C; c++){
            NewMatrix[c+(C*l)] = 0;
        }
    }
    if (*count == 0){
        double* to_delete = tab;
        tab = NewMatrix;
        delete[] to_delete;
        printf("Old Matrix Deleted\n");
    }
    else{
        (*count)--;
        int * newcount = new int;
        *newcount  = 1;
        count = newcount;
        tab = NewMatrix;
    }
}



char Matrice::affiche(){
    int window_height, window_length;
    #if defined(__linux__)
        struct winsize w;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        window_length = w.ws_col;
        window_height = w.ws_row;
    }
    #elif defined(_WIN32)
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      int columns, rows;
      columns=0;
      rows=0;
        // Get the console screen buffer info
      if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
          columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
          rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
      };
      window_length = columns;
      window_height = rows;
    #else
        printf("You're not on Linux or Windows, there is no guarantee for the display of the matrix");
        window_length=0;
        window_height=0;
    #endif

    int element_size=1;

    for(int k=0 ; k<C*L; k++){
        if (element_size<count_double_size(tab[k])){
            element_size = count_double_size(tab[k]);
        }
    };
    if ((element_size+3)*C>(window_length-5) || window_height < (L+4)){
        printf("the matrix may not display properly because of Window Size or Terminal\n");
        printf("If you are on Windows, try build.bat execute it on cmd \n");
        printf("If you are on Linux, just launch build.sh and execute the project in Build folder\n");
    }
    
    element_size+=2;

    for(int l=0 ; l<L ; l++){
        printf("|");
        for(int c=0; c<C; c++){
            print_double(tab[c+(C*l)],element_size);
            printf(" ");
        };
        printf("|\n");
    };
    printf("\n");
    return 0;
};



double Matrice::operator()(int i, int j) const {
    assert(0<=i && i<L && 0<=j && j<C);
    return tab[j+(C*i)];
};

double& Matrice::operator()(int i, int j) {
    assert(0<=i && i<L && 0<=j && j<C);
    return tab[j+(C*i)];
};


Matrice Matrice::operator*(const Matrice& factor){
    Matrice product(L, factor.C);
    if (C==factor.L){
        for(int l= 0; l<L; l++){
            for(int c=0; c<factor.C; c++){
                for (int n=0; n<C; n++){
                    product(l,c)+=(tab[n+(l*C)]*factor(n,c));
                }
            }
        }
    }
    else{
        printf("verify your matrix sizes");
        throw "multiplication impossible";
    }
    (*product.count)++;
    return product;
}















