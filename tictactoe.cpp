#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For seeding random numbers
using namespace std;

char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
char player_marker, computer_marker;
int current_player;

void drawBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool placeMarker(int slot, char marker) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = marker;
        return true;
    }
    return false;
}

int checkWinner() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return current_player;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return current_player;
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return current_player;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return current_player;

    return 0; // No winner yet
}

int getComputerMove() {
    // Computer chooses a random available slot
    int slot;
    do {
        slot = rand() % 9 + 1; // Random number between 1 and 9
    } while (!placeMarker(slot, computer_marker)); // Keep trying until an empty slot is found
    return slot;
}

void game() {
    cout << "Choose your marker (X or O): ";
    cin >> player_marker;

    // Assign computer marker
    computer_marker = (player_marker == 'X') ? 'O' : 'X';
    current_player = 1; // Player starts first

    drawBoard();

    int winner = 0;
    for (int i = 0; i < 9; i++) {
        if (current_player == 1) {
            cout << "Your turn. Enter your slot: ";
            int slot;
            cin >> slot;

            if (slot < 1 || slot > 9) {
                cout << "Invalid slot! Choose a slot between 1 and 9.\n";
                i--;
                continue;
            }

            if (!placeMarker(slot, player_marker)) {
                cout << "Slot already occupied! Try again.\n";
                i--;
                continue;
            }
        } else {
            cout << "Computer's turn...\n";
            int computer_slot = getComputerMove();
            cout << "Computer chose slot " << computer_slot << ".\n";
        }

        drawBoard();
        winner = checkWinner();

        if (winner != 0) {
            if (winner == 1) {
                cout << "You win! 🎉\n";
            } else {
                cout << "Computer wins! 💻\n";
            }
            break;
        }

        // Swap player
        current_player = (current_player == 1) ? 2 : 1;
    }

    if (winner == 0) {
        cout << "It's a tie!\n";
    }
}

int main() {
    srand(time(0)); // Seed the random number generator
    cout << "Welcome to Tic Tac Toe (Player vs Computer)!\n";
    game();
    return 0;
}
