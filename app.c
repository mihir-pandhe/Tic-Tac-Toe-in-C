#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 3
#define MAX_MOVES 9
#define MAX_NAME_LENGTH 50

char board[SIZE][SIZE];
char currentPlayer = 'X';
char playerXName[MAX_NAME_LENGTH] = "Player X";
char playerOName[MAX_NAME_LENGTH] = "Player O";
int moveHistory[MAX_MOVES][2];
int currentMoveIndex = -1;
int totalMoves = 0;
int playerXWins = 0;
int playerOWins = 0;

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    printf("\n");
    printf("  1 2 3\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%c", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("  -+-+-\n");
    }
    printf("\n");
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool makeMove(int row, int col) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        moveHistory[++currentMoveIndex][0] = row;
        moveHistory[currentMoveIndex][1] = col;
        totalMoves = currentMoveIndex + 1;
        return true;
    } else {
        printf("Invalid move. Please enter a valid move.\n");
        return false;
    }
}

void undoMove() {
    if (currentMoveIndex >= 0) {
        int row = moveHistory[currentMoveIndex][0];
        int col = moveHistory[currentMoveIndex][1];
        board[row][col] = ' ';
        currentMoveIndex--;
        switchPlayer();
        printf("Last move undone.\n");
    } else {
        printf("No moves to undo.\n");
    }
}

void redoMove() {
    if (currentMoveIndex + 1 < totalMoves) {
        currentMoveIndex++;
        int row = moveHistory[currentMoveIndex][0];
        int col = moveHistory[currentMoveIndex][1];
        board[row][col] = currentPlayer;
        switchPlayer();
        printf("Last undone move redone.\n");
    } else {
        printf("No moves to redo.\n");
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
        printf("%s (%c), enter your move (row and column): ", currentPlayer == 'X' ? playerXName : playerOName, currentPlayer);
        if (scanf("%d %d", row, col) != 2) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter numeric values.\n");
            continue;
        }
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

void displayInstructions() {
    printf("Welcome to Tic Tac Toe!\n");
    printf("Player X and Player O take turns to place their marks on the 3x3 grid.\n");
    printf("The first player to align three marks horizontally, vertically, or diagonally wins the game.\n");
    printf("If all cells are filled and no player has aligned three marks, the game ends in a draw.\n");
    printf("Enter your move by specifying the row and column numbers (1 to 3) separated by a space.\n\n");
    printf("You can also undo or redo moves using the following commands:\n");
    printf("'u' - Undo last move\n");
    printf("'r' - Redo last undone move\n\n");
}

void displayMenu() {
    printf("Tic Tac Toe\n");
    printf("1. Start New Game\n");
    printf("2. View Instructions\n");
    printf("3. Change Player Names\n");
    printf("4. View Win Count\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

void changePlayerNames() {
    printf("Enter name for Player X: ");
    scanf("%s", playerXName);
    printf("Enter name for Player O: ");
    scanf("%s", playerOName);
    printf("Player names updated successfully.\n");
}

void viewWinCount() {
    printf("Win Count:\n");
    printf("%s (X): %d\n", playerXName, playerXWins);
    printf("%s (O): %d\n", playerOName, playerOWins);
}

int main() {
    int row, col, choice;
    char command;
    bool gameOver = false;

    while (true) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initializeBoard();
                gameOver = false;
                displayInstructions();
                while (!gameOver) {
                    displayBoard();
                    printf("Enter your move (or command): ");
                    scanf(" %c", &command);
                    if (command == 'u') {
                        undoMove();
                    } else if (command == 'r') {
                        redoMove();
                    } else {
                        ungetc(command, stdin);
                        getPlayerMove(&row, &col);
                        if (makeMove(row, col)) {
                            if (checkWin()) {
                                displayBoard();
                                printf("Player %s (%c) wins!\n", currentPlayer == 'X' ? playerXName : playerOName, currentPlayer);
                                if (currentPlayer == 'X') {
                                    playerXWins++;
                                } else {
                                    playerOWins++;
                                }
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
                }
                break;
            case 2:
                displayInstructions();
                break;
            case 3:
                changePlayerNames();
                break;
            case 4:
                viewWinCount();
                break;
            case 5:
                printf("Exiting game. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
