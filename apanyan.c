#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLUMNS 7
#define WIN_LENGTH 5

void afficher_grille(char grille[ROWS][COLUMNS]);
int jouer_coup(char grille[ROWS][COLUMNS], int colonne, char jeton);
int verifier_gagnant(char grille[ROWS][COLUMNS], char jeton);

int main() {
    char grille[ROWS][COLUMNS];
    int colonne;
    char jeton = 'X';
    int gagnant = 0;
    
    // Initialisation de la grille avec des espaces
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            grille[i][j] = ' ';
        }
    }
    
    // Boucle principale du jeu
    while (!gagnant) {
        // Afficher la grille actuelle
        afficher_grille(grille);
        
        // Demander au joueur de choisir une colonne
        printf("Joueur %c, choisissez une colonne (1-%d) : ", jeton, COLUMNS);
        scanf("%d", &colonne);
        colonne--;  // ajuster l'indice de la colonne
        
        // Jouer le coup et vérifier s'il y a un gagnant
        if (jouer_coup(grille, colonne, jeton)) {
            gagnant = verifier_gagnant(grille, jeton);
        }
        
        // Changer le jeton pour le prochain joueur
        jeton = jeton == 'X' ? 'O' : 'X';
    }
    
    // Afficher le gagnant
    afficher_grille(grille);
    printf("Le joueur %c a gagné !\n", gagnant);
    
    return 0;
}

// Afficher la grille
void afficher_grille(char grille[ROWS][COLUMNS]) {
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("| %c ", grille[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------------------\n");
}

// Jouer un coup dans la colonne spécifiée
int jouer_coup(char grille[ROWS][COLUMNS], int colonne, char jeton) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (grille[i][colonne] == ' ') {
            grille[i][colonne] = jeton;
            return 1;
        }
    }
    printf("La colonne est pleine.\n");
    return 0;
}

// Vérifier s'il y a un gagnant
int verifier_gagnant(char grille[ROWS][COLUMNS], char jeton) {
    // Vérifier les lignes
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= COLUMNS - WIN_LENGTH; j++) {
            int k;
            for (k = 0; k < WIN_LENGTH; k++) {
                if (grille[i][j+k] != jeton) {
                    break;
                }
            }
            if (k == WIN_LENGTH) {
                return jeton;
            }
        }
   
// Vérifier les colonnes
for (int i = 0; i <= ROWS - WIN_LENGTH; i++) {
    for (int j = 0; j < COLUMNS; j++) {
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
for (int i = WIN_LENGTH - 1; i < ROWS; i++) {
    for (int j = 0; j <= COLUMNS - WIN_LENGTH; j++) {
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
for (int i = WIN_LENGTH - 1; i < ROWS; i++) {
    for (int j = WIN_LENGTH - 1; j < COLUMNS; j++) {
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
}

return 0;}
