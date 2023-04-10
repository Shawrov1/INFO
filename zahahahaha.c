#include <stdio.h>

#define colo 8
#define lign 6
#define WIN_LENGTH 5

void tourner(int tableau[lign][colo],int x,int y,int rota,int xx){


  //création tableau fils "caa" carré de taille xx à partir des coordonnés (x,y)
  int caa[xx][xx];
  int *ptr = &tableau[y][x];
  
  for(int i=0; i<xx; i++){
    for(int j=0; j<xx; j++){
      caa[i][j] = *(ptr + i*colo + j);
    }
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
  

}



void afficher_grille(int grille[lign][colo]) {
    printf("\n");
    for (int i = 0; i < lign; i++) {
        for (int j = 0; j < colo; j++) {
            printf("| %c ", grille[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------------------\n");
}

int jouer_coup(int grille[lign][colo], int colonne, char jeton) {
    for (int i = lign - 1; i >= 0; i--) {
        if (grille[i][colonne] == ' ') {
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
                if(tableau[f][i]==32 && tableau[f-1][i]!=32){
                tableau[f][i] = tableau[f-1][i];
                tableau[f-1][i]=32;}
        }
    }
  }
}



int main(){
    char jeton = 'X';
    int caca=10;
    int jeu;
    int gagnant =0;

  int tableau[lign][colo];
    for (int i = 0; i < lign; i++) {
        for (int j = 0; j < colo; j++) {
            tableau[i][j] = ' ';
        }
    }

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
        afficher_grille(tableau);printf("1");
        
        // Demander au joueur de choisir une colonne
        printf("Joueur %c, choisissez une colonne (1-%d) : ", jeton, colo);
        scanf("%d", &jeu);
        jeu--;  // ajuster l'indice de la colonne
        afficher_grille(tableau);printf("2");

        // Jouer le coup et vérifier s'il y a un gagnant
        if (jouer_coup(tableau, jeu, jeton)) {
            afficher_grille(tableau);printf("3");
            tourner(tableau,1,0,3,6);
            afficher_grille(tableau);printf("4");
            gravite(tableau);
            afficher_grille(tableau);printf("5");
            gagnant = verifier_gagnant(tableau, jeton);
        }
        printf("\n");
        printf("\n");
        printf("\n");
        // Changer le jeton pour le prochain joueur
        jeton = jeton == 'X' ? 'O' : 'X';
    }
    
}


  
  


