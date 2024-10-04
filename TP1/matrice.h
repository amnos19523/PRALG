class Matrice {
    public:
        int* count;
        int L,C ; //nb lignes, colonnes
        double* tab; // pointeur vers matrice
        //constructor
        Matrice();
        Matrice(int a, int b);
        //copy constructor
        Matrice(const Matrice& copy);
        //destructor
        ~Matrice();

        //other funcs
        void resize(int a, int b);
        char affiche();
        Matrice operator*(const Matrice& facteur);
        double operator() (int i, int j) const;
        double& operator() (int i, int j);
};