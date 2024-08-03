#include <stdio.h>
#include <stdbool.h>


#define SIZE 3


char board[SIZE][SIZE];
char currentPlayer = 'X';


void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}


void displayBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}


void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}


bool makeMove(int row, int col) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        return true;
    } else {
        printf("Invalid move. Please enter a valid move.\n");
        return false;
    }
}


bool checkWin() {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) return true;
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) return true;
    }
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) return true;
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) return true;


    return false;
}


bool checkDraw() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}


void getPlayerMove(int *row, int *col) {
    while (true) {
        printf("Player %c, enter your move (row and column): ", currentPlayer);
        scanf("%d %d", row, col);
        if (*row >= 1 && *row <= SIZE && *col >= 1 && *col <= SIZE) {
            (*row)--;
            (*col)--;
            if (board[*row][*col] == ' ') {
                break;
            } else {
                printf("This cell is already occupied. Please enter a different move.\n");
            }
        } else {
            printf("Invalid input. Please enter row and column numbers between 1 and 3.\n");
        }
    }
}


int main() {
    int row, col;
    bool gameOver = false;
    initializeBoard();


    while (!gameOver) {
        displayBoard();
        getPlayerMove(&row, &col);
        if (makeMove(row, col)) {
            if (checkWin()) {
                displayBoard();
                printf("Player %c wins!\n", currentPlayer);
                gameOver = true;
            } else if (checkDraw()) {
                displayBoard();
                printf("The game is a draw!\n");
                gameOver = true;
            } else {
                switchPlayer();
            }
        }
    }


    return 0;
}
