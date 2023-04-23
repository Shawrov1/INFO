#include <stdio.h>

#define LINES 9
#define COLUMNS 8

void affichage_plateau(char plateau[][COLUMNS]);
int check_win(char plateau[][COLUMNS], char player);
void play(char plateau[][COLUMNS], char player);

int main() {
    char plateau[LINES][COLUMNS];
    char player = 'X';
    int winner = 0;
  
  
    // Initialisation du plateau
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            plateau[i][j] = ' ';
        }
    }

    while (!winner) {
        affichage_plateau(plateau);
        play(plateau, player);
        winner = check_win(plateau, player);
        if (!winner) {
            // Switch to the other player
            player = (player == 'X') ? 'O' : 'X';
        }
    }

    printf("Player %c wins!\n", player);
    affichage_plateau(plateau);

    return 0;
}

void affichage_plateau(char plateau[][COLUMNS]) {
  
    printf("\n");
   for (int i = 0; i < LINES; i++) {
         printf("|");
          for (int j = 0; j < COLUMNS; j++) {
             printf(" %c |", plateau[i][j]);
        }
         printf("\n");
    }
    printf("---------------------------------\n");
    printf("  1   2   3   4   5   6   7   8\n\n");
}

int check_win(char plateau[][COLUMNS], char player) {
    // Check for horizontal wins
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMNS - 3; j++) {
            if (plateau[i][j] == player && plateau[i][j+1] == player &&
                plateau[i][j+2] == player && plateau[i][j+3] == player) {
                return 1;
            }
        }
    }

    // Check for vertical wins
    for (int i = 0; i < LINES - 3; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (plateau[i][j] == player && plateau[i+1][j] == player &&
                plateau[i+2][j] == player && plateau[i+3][j] == player) {
                return 1;
            }
        }
    }

    // Check for diagonal wins (top-left to bottom-right)
    for (int i = 0; i < LINES - 3; i++) {
        for (int j = 0; j < COLUMNS - 3; j++) {
            if (plateau[i][j] == player && plateau[i+1][j+1] == player &&
                plateau[i+2][j+2] == player && plateau[i+3][j+3] == player) {
                return 1;
            }
        }
    }

    // Check for diagonal wins (bottom-left to top-right)
    for (int i = 3; i < LINES; i++) {
        for (int j = 0; j < COLUMNS - 3; j++) {
            if (plateau[i][j] == player && plateau[i-1][j+1] == player &&
                plateau[i-2][j+2] == player && plateau[i-3][j+3] == player) {
                return 1;
            }
        }
    }

    // Check for a tie
    int tie = 1;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (plateau[i][j] == ' ') {
                tie = 0;
                break;
            }
        }
    }
    if (tie) {
        printf("The game is tied!\n");
        affichage_plateau(plateau);
        return 1;
    }

    return 0;
}




void play(char plateau[][COLUMNS], char player) {

  
    // do {
    //     printf("Joueur %c, entrez une colonne (1-8): \n", player);
    //     scanf("%d", &colonne);
    //     colonne--;
    //   // Convert to zero-based index
    // } while (colonne < 0 || colonne >= COLUMNS || plateau[0][colonne] != ' ');

      int colonne;
      int entier;
      int liste[] = { 1, 2, 3, 4, 5, 6 ,7 ,8 };
      
      do {
        entier = 1;
        colonne = 0;
        printf("Joueur %c, entrez une colonne (1-8): \n", player);
        scanf("%d", &colonne);
        while(getchar() != '\n');
        
        for (int i = 0; i < 8; i++) {
          if(colonne == liste[i]){
            entier = 0;
            break ;
          }
        } 
        colonne --;
      }while(entier);


  
    // Gravité
    int ligne = LIGNES - 1;
    while (plateau[ligne][colonne] != ' ') {
        ligne--;
    }

    // Place the player's piece in the chosen cell
    plateau[ligne][colonne] = player;
}
 
