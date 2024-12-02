#include <cstdio>
#include <string.h>
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

        cost = (mot1[i-1] == mot2[j-1]) ? 0 : 1;

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

    //itération
    for (int k=0; k<=i; k++){
        for (int l=0; l<=j; l++){
            if (k==0 || l==0){
                memo[k][l] = std::max(k,l);
            }
            else{
                int cost = (mot1[k-1] == mot2[l-1]) ? 0 : 1 ;
                memo[k][l] = std::min(1+std::min(memo[k-1][l],memo[k][l-1]),memo[k-1][l-1]+cost);
            }
        }
    }


    //affichage tableau

    //for (int k=0; k<=i; k++){
    //    std::cout<<'[';
    //    for (int l=0; l<=j; l++){
    //        std::cout <<memo[k][l];
    //    }
    //    std::cout <<']' <<std::endl;
    //}

    int result = memo[i][j];

    // effacer cache

    for (int k = 0; k <= i; k++) {
    delete[] memo[k];
    }
    delete[] memo;  

    return result;
    
}

void add_letter(char* mot, int length, char letter, int pos){
    for (int k=0; k<pos; k++){
        printf("%c",mot[k]);
    }
    printf("+%c+", letter);
    for (int k = pos; k<length; k++){
        printf("%c", mot[k]);
    }
    for (int k = length-1; k>pos; k--){
        mot[k]= mot[k-1];
    }
    mot[pos] = letter;

    std::cout<< " : " << mot;
    printf("\n");
}

void del_letter(char* mot, int length, int pos){
    for (int k=0; k<pos; k++){
        printf("%c",mot[k]);
    }
    printf("-%c-", mot[pos]);
    for (int k = pos+1; k<length; k++){
        printf("%c", mot[k]);
    }
    for (int k = pos; k<length-1; k++){
        mot[k]= mot[k+1];
    }
    mot[length-1]=0;

    std::cout<< " : " << mot;
    printf("\n");
}


void exch_letter(char* mot, int length, const char letter, int pos){
    for (int k=0; k<pos; k++){
        printf("%c",mot[k]);
    }
    printf("(%c->%c)", mot[pos], letter);
    for (int k = pos+1; k<length; k++){
        printf("%c", mot[k]);
    }
    mot[pos] = letter;
    std::cout<< " : " << mot;
    printf("\n");
}


int display_path(const char* mot1, const char* mot2, int i, int j, int** memo){

    //create copy of mot 2
    int max = std::max(i,j)+1;
    char* mod_word = new char[max];
    for (int k=0; k< j; k++){
        mod_word[k] = mot2[k];
    }
    for (int k=j; k< max; k++){
        mod_word[k] = 0;
    }


    //int distance = dist_iter_mem(mot1, mot2, i, j);
    int nord, ouest, n_w, actuel;
    
    while (i+j != 0){
        actuel  = memo[i][j];
        if (i!=0){
           nord = memo[i-1][j]; 
        }
        else{
            nord = j+2; // chemin impossible
        }
        if (j!=0){
            ouest = memo[i][j-1];
        }
        else{
            ouest = i+2;    // chemin impossible
        }
        if (j!=0 && i!=0){
            n_w = memo[i-1][j-1];
        }
        else{
            n_w=2+std::max(i,j);    // chemin impossible
        }

        if ( nord+1 == actuel){
            i--;
            add_letter(mod_word, max, mot1[i],j);
        }
        else{
            if(ouest+1 == actuel){
                j--;
                del_letter(mod_word, max, j);
            }
            else{
                i--;
                j--;
                if(actuel != n_w){
                    exch_letter(mod_word, max, mot1[i], j);
                }
            }
        }


    }
    delete [] mod_word;
    return 0;
}   

int main(){

    const char*a = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";
    const char*b = "la vie n'est pas un long fleuve";
    printf(a);
    printf("\n");
    printf(b);
    printf("\n");


    const int len_word_a = 74;
    const int len_word_b = 32;


    int** memo = new int*[len_word_a+1];
    
    for (int k=0; k<=len_word_a; k++){
        memo[k] = new int[len_word_b+1];
    }

    for (int k=0; k<=len_word_a; k++){
        for (int l=0; l<=len_word_b; l++){
            memo[k][l] = -1;
        }
    }
    
    // avec et sans memoïsation 
    clock_t t1 = clock();
    //printf("\ndistance is %i\n", dist_recur_mem(a,b,len_word_a,len_word_b));
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
    // la version sans mémoïsation est inutilisable au bout d'un moment.

    clock_t t4 = clock();
    printf("\ndistance is %i\n", dist_iter_mem(a,b,len_word_a,len_word_b));
    clock_t t5 = clock();

    std::cout<<(t5-t4)/(float)CLOCKS_PER_SEC<<std::endl;

    // La complexité est de O(m*n) aussi .la mémoire aussi est de l'ordre de m*n. 
    // Le temps d'exécution est à priori plus élevé, mais cela est du à l'affichage du cache + la suppression du tableau.
    // A grande échelle, le temps est plus court pour la version itérative.

    // affichage des étapes : memo utilisé construit plus haut avec la version récurssive
    display_path(a, b, len_word_a, len_word_b, memo);



    return 0;
}