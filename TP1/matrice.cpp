#include "matrice.h"
#include <stdio.h>

#include "functions.h"

#if defined(__linux__)
    #include <unistd.h>
    #include <sys/ioctl.h>
#elif defined(_WIN32)
    #include <windows.h>
#endif


char Matrice::init(int a, int b){
    L = a;
    C = b;
    tab = new double[L*C];
    for(int i=0;i<L*C;i++){
        tab[i]=0;
    }
    return 0;
};

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
        printf("the matrix may not display properly \n");
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
    return 0;
};
