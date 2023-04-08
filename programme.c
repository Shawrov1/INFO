#include <stdio.h>

#define ROWS 6
#define COLS 7

void display_board(char board[][COLS]);
int check_win(char board[][COLS], char player);
void play(char board[][COLS], char player);

int main() {
    char board[ROWS][COLS];
    char player = 'X';
    int winner = 0;
  
  
    // Initialize the board
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }

    while (!winner) {
        display_board(board);
        play(board, player);
        winner = check_win(board, player);
        if (!winner) {
            // Switch to the other player
            player = (player == 'X') ? 'O' : 'X';
        }
    }

    printf("Player %c wins!\n", player);
    display_board(board);



    return 0;
}

void display_board(char board[][COLS]) {
  
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n");
    }
    printf("-----------------------------\n");
    printf("  1   2   3   4   5   6   7\n");
}

int check_win(char board[][COLS], char player) {
    // Check for horizontal wins
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i][j+1] == player &&
                board[i][j+2] == player && board[i][j+3] == player) {
                return 1;
            }
        }
    }

    // Check for vertical wins
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == player && board[i+1][j] == player &&
                board[i+2][j] == player && board[i+3][j] == player) {
                return 1;
            }
        }
    }

    // Check for diagonal wins (top-left to bottom-right)
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i+1][j+1] == player &&
                board[i+2][j+2] == player && board[i+3][j+3] == player) {
                return 1;
            }
        }
    }

    // Check for diagonal wins (bottom-left to top-right)
    for (int i = 3; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i-1][j+1] == player &&
                board[i-2][j+2] == player && board[i-3][j+3] == player) {
                return 1;
            }
        }
    }

    // Check for a tie
    int tie = 1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == ' ') {
                tie = 0;
                break;
            }
        }
    }
    if (tie) {
        printf("The game is tied!\n");
        display_board(board);
        return 1;
    }

    return 0;
}


void play(char board[][COLS], char player) {
    int column;
    do {
        printf("Player %c, enter a column (1-7): ", player);
        scanf("%d", &column);
        column--;  // Convert to zero-based index
    } while (column < 0 || column >= COLS || board[0][column] != ' ');

    // Find the first empty cell in the chosen column
    int row = ROWS - 1;
    while (board[row][column] != ' ') {
        row--;
    }

    // Place the player's piece in the chosen cell
    board[row][column] = player;
}
