#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define colo 8
#define lign 6
#define WIN_LENGTH 5

int tourner(int tableau[lign][colo],int x,int y,int rota,int xx){  


    //création tableau fils "caa" carré de taille xx à partir des coordonnés (x,y)
    int caa[xx][xx];
    int *ptr = &tableau[y][x];

    int total=32*xx*xx;
    int tot=0;


  for(int i=0; i<xx; i++){
    for(int j=0; j<xx; j++){
      caa[i][j] = *(ptr + i*colo + j);
    }
  }
    

    for (int i = 0; i < xx; i++) {
        for (int j = 0; j < xx; j++) {
            tot += caa[i][j];
        }
    }
    if(tot==total){
        return 0;
    }
  //1= rotation à droite, autre= rotation à gauche
  if(rota==1){
    //rotation 90° vers la droite
    for(int i=0; i<xx/2; i++) {
        for(int j=i; j<xx-i-1; j++) {
            int temp = caa[i][j];
            caa[i][j] = caa[xx-j-1][i];
            caa[xx-j-1][i] = caa[xx-i-1][xx-j-1];
            caa[xx-i-1][xx-j-1] = caa[j][xx-i-1];
            caa[j][xx-i-1] = temp;
        }
    }}
  else{
    //rotation 90° vers la gauche
    for(int i=0;i<3;i++){
        for(int i=0; i<xx/2; i++) {
        for(int j=i; j<xx-i-1; j++) {
            int temp = caa[i][j];
            caa[i][j] = caa[xx-j-1][i];
            caa[xx-j-1][i] = caa[xx-i-1][xx-j-1];
            caa[xx-i-1][xx-j-1] = caa[j][xx-i-1];
            caa[j][xx-i-1] = temp;
        }
    }}
  }
  
  //imbriquement tableau fils dans le tableau père 
  for(int i=0; i<xx; i++){
  for(int j=0; j<xx; j++){
    tableau[i+y][j+x] = caa[i][j];
  }
}
  
return 1;
}



void afficher_grille(int grille[lign][colo]) {
    printf("\n");
    for (int i = 0; i < lign; i++) {
        printf("%d  ",i+1);
        for (int j = 0; j < colo; j++) {
            printf("| %c ", grille[i][j]);
        }
        printf("|\n");
    }
    printf("   _________________________________\n");
    printf("     1   2   3   4   5   6   7   8  \n");
}

/*int jouer_coup(int grille[lign][colo], int colonne, char jeton) {
    for (int i = lign - 1; i >= 0; i--) {
        if (grille[i][colonne] == ' ') {
            grille[i][colonne] = jeton;
            return 1;
        }
    }
    printf("La colonne est pleine.\n");
    return 0;
}*/

//placer le coup joué
int jouer_coup(int grille[lign][colo], int colonne, char jeton) {
    //vérifier si la colonne n'est pas obstrué par un bloc
    if(grille[0][colonne] =='#'){
        printf("la colonne est pleine.\n");
        return 0;
    }

    for (int i = 0; i < lign; i++) {
        if (grille[i][colonne] == ' ' && grille[i+1][colonne]!= ' ') {
            grille[i][colonne] = jeton;
            return 1;
        }
    }
    printf("La colonne est pleine.\n");
    return 0;
}

// Vérifier s'il y a un gagnant
int verifier_gagnant(int grille[lign][colo], char jeton) {
    // Vérifier les lignes
    for (int i = 0; i < lign; i++) {
        for (int j = 0; j <= colo - WIN_LENGTH; j++) {
            int k;
            for (k = 0; k < WIN_LENGTH; k++) {
                if (grille[i][j+k] != jeton) {
                    break;
                }
            }
            if (k == WIN_LENGTH) {
                return jeton;
            }
        }}
   
// Vérifier les colonnes
for (int i = 0; i <= lign - WIN_LENGTH; i++) {
    for (int j = 0; j < colo; j++) {
        int k;
        for (k = 0; k < WIN_LENGTH; k++) {
            if (grille[i+k][j] != jeton) {
                break;
            }
        }
        if (k == WIN_LENGTH) {
            return jeton;
        }
    }
}

// Vérifier les diagonales 
for (int i = WIN_LENGTH - 1; i < lign; i++) {
    for (int j = 0; j <= colo - WIN_LENGTH; j++) {
        int k;
        for (k = 0; k < WIN_LENGTH; k++) {
            if (grille[i-k][j+k] != jeton) {
                break;
            }
        }
        if (k == WIN_LENGTH) {
            return jeton;
        }
    }
}

// Vérifier les diagonales 
for (int i = WIN_LENGTH - 1; i < lign; i++) {
    for (int j = WIN_LENGTH - 1; j < colo; j++) {
        int k;
        for (k = 0; k < WIN_LENGTH; k++) {
            if (grille[i-k][j-k] != jeton) {
                break;
            }
        }
        if (k == WIN_LENGTH) {
            return jeton;
        }
    }
}return 0;}


void gravite(int tableau[lign][colo]){
    for(int k=0;k<(lign-1);k++){
        for(int i=0;i<colo;i++){
            for(int f=lign-1;f!=0;f--){
                if(tableau[f][i]==32 && tableau[f-1][i]!=32 && tableau[f-1][i]!='#'){
                tableau[f][i] = tableau[f-1][i];
                tableau[f-1][i]=32;}
        }
    }
  }
}

void creation_tableau(int tableau[lign][colo]){
    
    for (int i = 0; i < lign; i++) {
        for (int j = 0; j < colo; j++) {
            tableau[i][j] = ' ';
        }
    }
    tableau[0][0]='#';
    tableau[0][colo-1]='#';
    tableau[lign-1][0]='#';
    tableau[lign-1][colo-1]='#';
}



int main(){
    char jeton = 'X';
    int nb_joueur;
    printf("Vous pouvez jouer à 2 ou 3 joueurs, à combien de joueur voulez vous jouer ?\n");
    scanf("%d",&nb_joueur);
    int jeu;
    int gagnant =0;
    int tableau[lign][colo];
    creation_tableau(tableau);


    /*while (caca)
    {
        afficher_grille(tableau);
        printf("\n");
        scanf("%d",&jeu);
        printf("\n");
        jouer_coup(tableau,jeu,jeton);
        afficher_grille(tableau);
        tourner(tableau,1,1,0,3);
        afficher_grille(tableau);
        printf("6666666666666666666666666666666666666");
        printf("\n");
        printf("\n");
        printf("\n");
    }*/

    while (!gagnant) {

        
        // Afficher la grille actuelle
        afficher_grille(tableau);
        int coo_x=0;
        int coo_y=0;
        
        
        
        srand(time(NULL));
        int dim= rand() % 2;
        if(dim==0){dim=3;}
        else{dim=5;}

        


        // Demander au joueur de choisir une colonne
        int jeu_valide;
        do {
            jeu_valide=1;
            printf("Joueur %c, veuillez choisir une colonne (1-%d) : ", jeton, colo);
            scanf("%d", &jeu);
            jeu--;//ajuster l'indice de la colonne
            if(jeu< 0 || jeu >= colo || tableau[0][jeu] != ' '){
                jeu_valide=0;
                printf("Vous avez fait une erreur, veuillez recommencer svp.\n\n");
            }
        } while (!jeu_valide);


        afficher_grille(tableau);printf("affichage classique");

        // Jouer le coup et vérifier s'il y a un gagnant
        if (jouer_coup(tableau, jeu, jeton)) {
            afficher_grille(tableau);printf("affichage après jeu\n");


            printf("vous avez obtenu la dimension %d !\n",dim);
            printf("entrez les coordonnées d'où vous voulez faire tourner\n");
            printf("x: ");
            scanf("%d",&coo_x);
            printf("\ny: ");
            scanf("%d",&coo_y);
            

            if(dim==3){
                if(!tourner(tableau,coo_x-2,coo_y-2,1,dim)){
                    do{
                        printf("réessayez svp");
                        printf("\nx: ");
                        scanf("%d",&coo_x);
                        printf("\ny: ");
                        scanf("%d",&coo_y);
                    }while(!tourner(tableau,coo_x-1,coo_y-1,1,3));
                }; 
            }
            else{
                if(!tourner(tableau,coo_x-3,coo_y-3,1,dim)){
                    do{
                        printf("réessayez svp");
                        printf("\nx: ");
                        scanf("%d",&coo_x);
                        printf("\ny: ");
                        scanf("%d",&coo_y);
                    }while(!tourner(tableau,coo_x-1,coo_y-1,1,3));
                }; 
            }


            afficher_grille(tableau);printf("affichage après rotation");
            gravite(tableau);
            afficher_grille(tableau);printf("affichage après gravité");
            gagnant = verifier_gagnant(tableau, jeton);
        }

        printf("\n");
        printf("\n");
        printf("\n");
        // Changer le jeton pour le prochain joueur
        if(nb_joueur==2){
            if(jeton=='X'){jeton='O';}
            else{jeton='X';}};
        if(nb_joueur==3){
            if(jeton=='X'){jeton='+';}
            else if(jeton=='+'){jeton='O';}
            else {jeton='X';}
        }
    }
    
}
