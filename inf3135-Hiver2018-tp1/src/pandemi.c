#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define LARGEUR 40
#define HAUTEUR 20
#define BUF_SIZE 64

// Program status
enum STATUS {
    PANDEMI_OK               = 0,
    PANDEMI_ARGC_ERROR       = 1,
    PANDEMI_ARGV_NONPOSITIVE = 2,
};
bool contient_des_saut_de_ligne(char * tmp)
{
    const char * saut_de_ligne = "\n";
    char *c = tmp;

    while (*c) {
        if ((strchr(saut_de_ligne, *c))) {
            return true;
        }
        c++;
    }
    return false;
}


void contient_des_caracteres_valides(char * tmp)
{

    const char * valid_characters = "H.XQ";
    char *c = tmp;

    //enlever dernier caractere (\n)
    c[strlen(c)-1] = 0;
    while (*c)
    {
        if (!(strchr(valid_characters, *c)))
        {
            fprintf(stderr,"Erreur: Caractère `%c` inattendu, attendu `H`, `Q`, `X` ou `.`.", *c);
            exit(1);
        }
        c++;
    }
}
bool valider_longueur_matrix(char *content)
{
    //20 * 40 + \n
    return strlen(content) < 801?false : true;
}

void Init(char matrix[HAUTEUR][LARGEUR], char matrix_jour_suivant[HAUTEUR][LARGEUR], char * content)
{
    char * c= content;
    int i,j;
    int nbr_caractere = 0;


    while(nbr_caractere != 801){
        for (i=0; i<HAUTEUR; ++i) {
            for (j = 0; j < LARGEUR; ++j) {
                matrix[i][j] = *c;
                matrix_jour_suivant[i][j] = *c;
                ++c;
                ++nbr_caractere;
            }
        }
        ++nbr_caractere;
        ++c;

    }
}

bool est_une_matrice_habite(char *content){

    const char * caractere_population = "XQH";
    char *c = content;

    while (*c) {
        if ((strchr(caractere_population, *c))) return true;
        c++;
    }
    return false;
}
bool zone_mourante(char  gauche, char   bas, char   droite, char   haut, char   haut_gauche, char   bas_gauche, char   bas_droite, char  haut_droite){

    int i;
    int index = 0;
    int voisin = 0;
    char * c =  malloc(sizeof(char)*8);
    c[0] ='\0';

    if (gauche != 0){
        c[index] = gauche;
        ++index;
    }
    if (bas != 0){
        c[index] = bas;
        ++index;
    }
    if (droite != 0){
        c[index] = droite;
        ++index;
    }
    if (haut != 0){
        c[index] = haut;
        ++index;
    }
    if (haut_gauche != 0){
        c[index] = haut_gauche;
        ++index;
    }
    if (haut_droite != 0){
        c[index] = haut_droite;
        ++index;
    }
    if (bas_gauche != 0){
        c[index] = bas_gauche;
        ++index;
    }
    if (bas_droite != 0){
        c[index] = bas_droite;
        ++index;
    }
    for (i= 0; i < index; ++i){
        if(c[i] == 'H' || c[i] == 'Q' || c[i] == 'X'){
            ++voisin;
        }
    }
    if (voisin <2 || voisin >3){
        return true;
    }
    return false;


}
void reset (char  gauche, char   bas, char   droite, char   haut, char   haut_gauche, char   bas_gauche, char   bas_droite, char  haut_droite)
{
    droite = 0;
    gauche = 0;
    bas = 0;
    haut = 0;
    bas_gauche = 0;
    bas_droite = 0;
    haut_gauche = 0;
    haut_droite = 0;
}

char zone_inhabite_devient_peuplee(char gauche, char   bas, char   droite, char   haut, char   haut_gauche, char   bas_gauche, char   bas_droite, char  haut_droite){
    int i;
    int index = 0;
    int voisin_infecte = 0;
    int voisin_sain = 0;
    char * c =  malloc(sizeof(char)*8);
    c[0] ='\0';

    if (gauche != 0){
        c[index] = gauche;
        ++index;
    }
    if (bas != 0){
        c[index] = bas;
        ++index;
    }
    if (droite != 0){
        c[index] = droite;
        ++index;
    }
    if (haut != 0){
        c[index] = haut;
        ++index;
    }
    if (haut_gauche != 0){
        c[index] = haut_gauche;
        ++index;
    }
    if (haut_droite != 0){
        c[index] = haut_droite;
        ++index;
    }
    if (bas_gauche != 0){
        c[index] = bas_gauche;
        ++index;
    }
    if (bas_droite != 0){
        c[index] = bas_droite;
        ++index;
    }
    for (i= 0; i < index; ++i){
        if(c[i] == 'Q' || c[i] == 'X'){
            ++voisin_infecte;
        }else if(c[i] == 'H'){
            ++voisin_sain;
        }
    }
    if (voisin_infecte + voisin_sain == 3){
        if (voisin_infecte > voisin_sain){
            //deviendra en quarantaine
            return 'Q';
        }else{
            //deviendra saine
            return 'H';
        }
    }else{
        return '.';
    }

}
char zone_saine_devient_infectee(char gauche, char bas, char droite, char haut, char haut_gauche, char bas_gauche, char bas_droite, char haut_droite)
{
    int i;
    int index = 0;
    int voisin_infecte = 0;
    int voisin_sain = 0;

    char * c =  malloc(sizeof(char)*8);
    c[0] ='\0';

    if (gauche != 0){
        c[index] = gauche;
        ++index;
    }
    if (bas != 0){
        c[index] = bas;
        ++index;
    }
    if (droite != 0){
        c[index] = droite;
        ++index;
    }
    if (haut != 0){
        c[index] = haut;
        ++index;
    }
    if (haut_gauche != 0){
        c[index] = haut_gauche;
        ++index;
    }
    if (haut_droite != 0){
        c[index] = haut_droite;
        ++index;
    }
    if (bas_gauche != 0){
        c[index] = bas_gauche;
        ++index;
    }
    if (bas_droite != 0){
        c[index] = bas_droite;
        ++index;
    }
    for (i= 0; i < index; ++i){
        if(c[i] == 'Q' || c[i] == 'X'){
            ++voisin_infecte;
        }else if(c[i] == 'H'){
            ++voisin_sain;
        }
    }
    if (voisin_infecte > voisin_sain){
        //deviendra en quarantaine
        return 'Q';
    }else{
        //deviendra saine
        return 'H';
    }
}
char analyser_voisin(char courrant ,char gauche, char   bas, char   droite, char   haut, char   haut_gauche, char   bas_gauche, char   bas_droite, char  haut_droite)
{
    char * c =  malloc(sizeof(char)*8);
    c[0] ='\0';

    if (zone_mourante(gauche, bas, droite, haut, haut_gauche, bas_gauche, bas_droite, haut_droite)){
        return '.';
    }else{
        if (courrant == '.'){
            return zone_inhabite_devient_peuplee(gauche, bas, droite, haut, haut_gauche, bas_gauche, bas_droite, haut_droite);
        }else if (courrant == 'H'){
            return zone_saine_devient_infectee(gauche, bas, droite, haut, haut_gauche, bas_gauche, bas_droite, haut_droite);

        }else if (courrant == 'Q' || courrant == 'X'){
            return 'X';
        }
    }
    //il y a eu erreur
    return '@';
}
/*
 * * Les règles sont les suivantes:

* On dit qu’une population est infectée si elle est en quarantaine ou
complètement infectée

* Une zone sans population devient peuplée si elle possède **exactement trois**
        cellules voisines peuplées (populations saines, en quarantaine et infectées
                                    confondues).  Si la majorité des trois cellules voisines est infectée alors
la zone devient infectée partiellement (c’est-à-dire en quarantaine),
sinon elle est considérée comme saine.

* Une zone avec population reste peuplée si elle possède **deux ou trois**
voisins peuplés. De plus, une zone saine devient infectée partiellement
(c’est-à-dire en quarantaine), si la majorité de ses voisins est infectée.

* Une zone avec population en quarantaine devient complètement infectée après
une journée

* Une zone avec **moins de deux** ou **plus de trois** voisins vivants meurt
(de solitude ou par étouffement).
*/
void calculer_jour_suivant(char matrix [HAUTEUR][LARGEUR], char matrix_jour_suivant [HAUTEUR][LARGEUR]){
    int i,j;
    char  droite , gauche, bas, haut, bas_gauche, bas_droite, haut_gauche, haut_droite, courrant =  0;

//    char * test = malloc(sizeof(char));
//    *test = "\0";

    for (i=0; i < HAUTEUR; ++i){
        for(j=0; j< LARGEUR; ++j){
            droite = gauche = bas=  haut = bas_gauche = bas_droite = haut_gauche = haut_droite = courrant =  0;

            //premiere range
            if (i == 0){
                //coin superieur gauche
                if(j == 0){

                    courrant = matrix[i][j];
                    droite = matrix[i][j+1];
                    bas = matrix[i+1][j];
                    bas_droite = matrix[i+1][j+1];

                    //coin superieur droit
                }else if (j == 39){
                    //verifier gauche,              bas,                 diagonale bas gauche

                    courrant = matrix[i][j];
                    gauche = matrix[i][j-1];
                    bas = matrix[i+1][j];
                    bas_gauche = matrix[i+1][j-1];


                }else {
                    //sinon verifier gauche, droite, bas, bas gauche  bas droit

                    courrant = matrix[i][j];
                    gauche = matrix[i][j-1];
                    droite = matrix[i][j+1];
                    bas = matrix[i+1][j];
                    bas_gauche = matrix[i+1][j-1];
                    bas_droite = matrix[i+1][j+1];

                }
                //derniere rangee
            }else if(i==19){
                //coin inferieur gauche
                if(j == 0){
                    //verifier droite, haut, diagonal haut droite

                    courrant = matrix[i][j];
                    droite = matrix[i][j+1];
                    haut = matrix[i-1][j];
                    haut_droite = matrix[i-1][j+1];

                    //coin inferieur droit
                }else if (j == 39){
                    //verifier gauche, haut,  diagonale haut gauche

                    courrant = matrix[i][j];
                    gauche = matrix[i][j-1];
                    haut = matrix[i-1][j];
                    haut_gauche = matrix[i-1][j-1];

                    //sinon verifier
                }else {
                    //   gauche,  droite,haut,haut gauche ,haut droit

                    courrant = matrix[i][j];
                    gauche = matrix[i][j-1];
                    droite = matrix[i][j+1];
                    haut = matrix[i-1][j];
                    haut_gauche = matrix[i-1][j-1];
                    haut_droite = matrix[i-1][j+1];

                }
                //sans les coin , la premiere et derniere rangee
            }else{
                //premiere colonne
                if (j ==0){
                    //    droite, haut,bas, haut droit ,bas droit

                    courrant = matrix[i][j];
                    droite = matrix[i][j+1];
                    haut = matrix[i-1][j];
                    bas = matrix[i+1][j];
                    haut_droite = matrix[i-1][j+1];
                    bas_droite = matrix[i+1][j+1];

                    //derniere colonne
                }else if (j == 39){
                    //    gauche,haut,bas ,haut gauche,bas gauche
                    gauche = matrix[i][j-1];
                    haut = matrix[i-1][j];
                    bas = matrix[i+1][j];
                    haut_gauche = matrix[i-1][j-1];
                    bas_gauche = matrix[i+1][j-1];

                    //verifier tous les voisins
                }else{
                    //gauche,droite haut,bas diagonale haut gauche diagonale bas gauche diagonale haut droit diagonale bas droit

                    courrant = matrix[i][j];
                    gauche = matrix[i][j-1];
                    droite = matrix[i][j+1];
                    haut = matrix[i-1][j];
                    bas = matrix[i+1][j];
                    haut_gauche = matrix[i-1][j-1];
                    haut_droite = matrix[i-1][j+1];
                    bas_gauche = matrix[i+1][j-1];
                    bas_droite = matrix[i+1][j+1];

                }
            }
            matrix_jour_suivant[i][j] = analyser_voisin(courrant, gauche, bas, droite, haut, haut_gauche, bas_gauche, bas_droite, haut_droite);
        }
    }

}

void copier_matrix(char matrix[HAUTEUR][LARGEUR], char matrix_jour_suivant[HAUTEUR][LARGEUR])
{
    int i,j;
    for (i=0 ; i < HAUTEUR; ++i){
        for (j=0; j < LARGEUR ; ++j){
            matrix[i][j] = matrix_jour_suivant[i][j];
        }
    }
}

void lire_map(char ** content)
{
    char buffer[BUF_SIZE];
    size_t contentSize = 0; // includes NULL
    char * tmp = malloc(sizeof(char) * BUF_SIZE);

        if (*content == NULL) {
            perror("Failed to allocate content");
            exit(1);
        }
        *content[0] = '\0'; // make null-terminated
        while (fgets(buffer, BUF_SIZE, stdin)) {
            char * old = *content;
            contentSize += strlen(buffer);
            *content = realloc(*content, contentSize);
            if (*content == NULL) {
                perror("Failed to reallocate content");
                free(old);
                exit(2);
            }

            //supprime les saut de ligne
            strtok(*content, "\n");

            enlever_espace(*content);



            //concatene le contenu
            strcat(*content, buffer);

            //pour la validation interne
            strcpy(tmp, buffer);
            enlever_espace(tmp);

            //EOF
            if (tmp[0] == '\n') {
                free(tmp);
                break;
            }

            // perror() si non valide
            contient_des_caracteres_valides(tmp);


            if (ferror(stdin)) {
                free(*content);
                perror("Error reading from stdin.");
                exit(3);
            }
        }//fin while
}

void imprimer_matrix(char * content)
{

    int i,j;
    for (i=0; i< HAUTEUR; ++i){
        for (j=0; j<LARGEUR; ++j){
            printf("%c", *content);
            ++content;
        }
        printf("\n");
    }
}

void enlever_espace(char * content)
{
    char* i = content;
    char* j = content;
    while(*j != 0)
    {
        *i = *j++;
        if(*i != ' ')
            i++;
    }
    *i = 0;
    
}
/*
 * * Le caractère `H` indique que la zone géographique contient une population
  saine (non infectée par le virus X).

* Le caractère `Q` indique que la zone géographique est en quarantaine,
  c'est-à-dire qu’une partie de la population est infectée par le virus.

* Le caractère `X` indique que la zone géographique est complètement infectée
  par le virus X.

* Le caractère `.` indique que la zone géographique est sans population (pas de
  population initiale ou population décédée).


 * Les règles sont les suivantes:

* On dit qu’une population est infectée si elle est en quarantaine ou
  complètement infectée

* Une zone sans population devient peuplée si elle possède **exactement trois**
  cellules voisines peuplées (populations saines, en quarantaine et infectées
  confondues).  Si la majorité des trois cellules voisines est infectée alors
  la zone devient infectée partiellement (c’est-à-dire en quarantaine),
  sinon elle est considérée comme saine.

* Une zone avec population reste peuplée si elle possède **deux ou trois**
  voisins peuplés. De plus, une zone saine devient infectée partiellement
  (c’est-à-dire en quarantaine), si la majorité de ses voisins est infectée.

* Une zone avec population en quarantaine devient complètement infectée après
  une journée

* Une zone avec **moins de deux** ou **plus de trois** voisins vivants meurt
  (de solitude ou par étouffement).
 */
int main(int argc, char* argv[])
{
    if (argc > 2) {
        perror("Erreur: Attendu un seul argument: le nombre de jours à simuler.\n");
        exit(PANDEMI_ARGC_ERROR);
    }else {
        int nbr_jour_arg = 0;
        if (argc == 2){
            nbr_jour_arg = argv[1][0] -'0';
            if(nbr_jour_arg > 100){
                perror("100 jours maximum pour argc");
                exit(1);
            }
        }
        int nbr_jour = 0;
        char * content = malloc(sizeof(char) * BUF_SIZE);

        lire_map(&content);
        if (!valider_longueur_matrix(content)){
            fprintf(stderr,"Erreur: Caractère `EOF` inattendu, attendu `H`, `Q`, `X` ou `.`.");
            exit(1);
        };


        //zone inhabite ou totalement decede
        if (nbr_jour_arg == 0 || !est_une_matrice_habite(content)) {
            //imprime la matrice
            while (nbr_jour <= nbr_jour_arg){
                printf("Jour %d", nbr_jour);
                printf("\n");
                imprimer_matrix(content);
                ++nbr_jour;
            }

        } else {

            char matrix[HAUTEUR][LARGEUR];
            char matrix_jour_suivant[HAUTEUR][LARGEUR];
            Init(matrix,matrix_jour_suivant, content);

            //imprimer jour 0
            printf("Jour 0\n");
            imprimer_matrix(content);

            ++nbr_jour;

            while (nbr_jour <= nbr_jour_arg) {
                calculer_jour_suivant(matrix, matrix_jour_suivant);

                //imprimer jour suivant
                printf("Jour %d", nbr_jour);
                printf("\n");

                int i, j;
                for (i=0; i< HAUTEUR; ++i){
                    for (j=0; j<LARGEUR; ++j){
                        char caractere = matrix_jour_suivant[i][j];
                        printf("%c", caractere);
                    }
                    printf("\n");
                }
                copier_matrix(matrix, matrix_jour_suivant);
                ++nbr_jour;
            }
        }


    }
    return PANDEMI_OK;
}