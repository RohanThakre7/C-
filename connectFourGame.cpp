#include <iostream>
#include <vector>
using namespace std;

const int ROWS = 6;
const int COLS = 7;

// Function to display the board
void displayBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    for (int j = 0; j < COLS; j++) {
        cout << "----";
    }
    cout << "-" << endl;
    for (int j = 0; j < COLS; j++) {
        cout << "  " << j + 1 << " ";
    }
    cout << endl;
}

// Function to drop a disc into a column
bool dropDisc(vector<vector<char>>& board, int col, char disc) {
    if (col < 0 || col >= COLS || board[0][col] != ' ') {
        return false; // Invalid move
    }
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == ' ') {
            board[i][col] = disc;
            return true;
        }
    }
    return false;
}

// Function to check for a win
bool checkWin(const vector<vector<char>>& board, char disc) {
    // Check horizontal, vertical, and diagonal lines
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Check horizontal
            if (j <= COLS - 4 && board[i][j] == disc && board[i][j + 1] == disc &&
                board[i][j + 2] == disc && board[i][j + 3] == disc) {
                return true;
            }
            // Check vertical
            if (i <= ROWS - 4 && board[i][j] == disc && board[i + 1][j] == disc &&
                board[i + 2][j] == disc && board[i + 3][j] == disc) {
                return true;
            }
            // Check diagonal (bottom-left to top-right)
            if (i >= 3 && j <= COLS - 4 && board[i][j] == disc &&
                board[i - 1][j + 1] == disc && board[i - 2][j + 2] == disc &&
                board[i - 3][j + 3] == disc) {
                return true;
            }
            // Check diagonal (top-left to bottom-right)
            if (i <= ROWS - 4 && j <= COLS - 4 && board[i][j] == disc &&
                board[i + 1][j + 1] == disc && board[i + 2][j + 2] == disc &&
                board[i + 3][j + 3] == disc) {
                return true;
            }
        }
    }
    return false;
}

// Function to check for a draw
bool isDraw(const vector<vector<char>>& board) {
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == ' ') {
            return false; // There's still space to play
        }
    }
    return true;
}

int main() {
    vector<vector<char>> board(ROWS, vector<char>(COLS, ' '));
    char players[2] = {'X', 'O'};
    int currentPlayer = 0;

    cout << "Welcome to Connect Four!" << endl;
    displayBoard(board);

    while (true) {
        int col;
        cout << "Player " << (currentPlayer + 1) << " (" << players[currentPlayer] << "), enter column (1-" << COLS << "): ";
        cin >> col;
        col--; // Adjust for 0-based index

        if (!dropDisc(board, col, players[currentPlayer])) {
            cout << "Invalid move. Try again!" << endl;
            continue;
        }

        displayBoard(board);

        if (checkWin(board, players[currentPlayer])) {
            cout << "Player " << (currentPlayer + 1) << " (" << players[currentPlayer] << ") wins!" << endl;
            break;
        }

        if (isDraw(board)) {
            cout << "It's a draw!" << endl;
            break;
        }

        currentPlayer = 1 - currentPlayer; // Switch player
    }

    return 0;
}
