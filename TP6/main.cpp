#include <cstdio>
#include <algorithm>
#include <iostream>
#include <ctime>

int dist_recur_mem (const char* mot1, const char* mot2, int i, int j, int** memo = nullptr) {
    
    if (memo != nullptr && memo[i][j] != -1){
        //printf("h\n");
        return memo[i][j];
    }
    else{
        if (i==0){
            if (memo!=nullptr){
            memo[i][j] = j;
            }
            return j;
        }
        if (j==0){
            if (memo!=nullptr){
            memo[i][j] = i;
            }
            return i;
        }
        int cost; 

        cost = (mot1[i] == mot2[j]) ? 0 : 1;

        int result = std::min(1+std::min(dist_recur_mem(mot1, mot2, i-1,j, memo),
        dist_recur_mem(mot1, mot2, i, j-1, memo)),dist_recur_mem(mot1, mot2, i-1, j-1, memo)+cost);

        //printf("%i", result); 
        if (memo!=nullptr){
            memo[i][j] = result;
        }
        //std::cout<<(memo[i][j]);

        return result;
    }
}

int dist_iter_mem (const char* mot1, const char* mot2, int i, int j){

    //initialisation memo
    int** memo = new int*[i+1];
    for (int k=0; k<=i; k++){
        memo[k] = new int[j+1];
    }
    for (int k=0; k<=i; k++){
        for (int l=0; l<=j; l++){
            memo[k][l] = -1;
        }
    }

    //itération
    for (int k=0; k<=i; k++){
        for (int l=0; l<=j; l++){
            if (k==0 || l==0){
                memo[k][l] = std::max(k,l);
            }
            else{
                int cost = (mot1[k] == mot2[l]) ? 0 : 1;
                memo[k][l] = std::min(1+std::min(memo[k-1][l],memo[k][l-1]),memo[k-1][l-1]+cost);
            }
        }
    }


    //affichage tableau

    for (int k=0; k<=i; k++){
        std::cout<<'[';
        for (int l=0; l<=j; l++){
            std::cout <<memo[k][l];
        }
        std::cout <<']' <<std::endl;
    }

    int result = memo[i][j];

    // effacer cache

    for (int k = 0; k <= i; k++) {
    delete[] memo[k];
    }
    delete[] memo;  

    return result;
    
}


int display_path(const char* mot1, const char* mot2, int i, int j, int** memo){return 0;}

int main(){

    const char*a = "gendarmes";
    const char*b = "gens abris";
    printf(a);
    printf("\n");
    printf(b);
    printf("\n");


    const int len_word_a = 10;
    const int len_word_b = 11;


    int** memo = new int*[len_word_a+1];
    
    for (int k=0; k<=len_word_a; k++){
        memo[k] = new int[len_word_b+1];
    }

    for (int k=0; k<=len_word_a; k++){
        for (int l=0; l<=len_word_b; l++){
            memo[k][l] = -1;
        }
    }
    for (int k=0; k<=len_word_a; k++){
        std::cout<<'[';
        for (int l=0; l<=len_word_b; l++){
            std::cout <<memo[k][l];
        }
        std::cout <<']' <<std::endl;
    }
    
    // avec et sans memoïsation 
    clock_t t1 = clock();
    printf("\ndistance is %i\n", dist_recur_mem(a,b,len_word_a,len_word_b));
    clock_t t2 = clock();
    printf("\ndistance is %i\n", dist_recur_mem(a,b,len_word_a,len_word_b,memo));
    clock_t t3 = clock();

    for (int k=0; k<=len_word_a; k++){
        std::cout<<'[';
        for (int l=0; l<=len_word_b; l++){
            std::cout <<memo[k][l];
        }
        std::cout <<']' <<std::endl;
    }

    std::cout<<(t2-t1)/(float)CLOCKS_PER_SEC<<std::endl<<(t3-t2)/(float)CLOCKS_PER_SEC<<std::endl;
    // complexité sans mémoïsation est exponentielle et du même ordre en mémoire.
    // la complexité avec mémoïsation est linéaire O(m*n) avec le même ordre en mémoire.
    // on voit une grosse différence sur le temps.

    clock_t t4 = clock();
    printf("\ndistance is %i\n", dist_iter_mem(a,b,len_word_a,len_word_b));
    clock_t t5 = clock();

    std::cout<<(t5-t4)/(float)CLOCKS_PER_SEC<<std::endl;

    // La complexité est de O(m*n) aussi .la mémoire aussi est de l'ordre de m*n. 
    // Le temps d'exécution est à priori plus élevé, mais cela est du à l'affichage du cache + la suppression du tableau.


    return 0;
}