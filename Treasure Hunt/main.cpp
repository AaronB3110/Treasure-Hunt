//Aaron Bermudez
#include <iostream>
#include <string>
#include <iomanip>

//Global Variables
const int ROWS = 10;
const int COLS = 10;

//Structure Declaration
struct chest {
    std::string chestName; //Name
    int row; //Row location
    int col; //Column location
    double value; //How much is it worth?
    bool hidden; //Is the chest hidden?
};

//Prototypes
void printIntro();
void printEndGame(char[][COLS],double, chest[], const int, const char);
void fillArray(chest []);
void fillGrid (char[][COLS], char);
void checkUserGuess(char[][COLS], int, int, chest[], const int, int &, const char, const char, double &, char &);
void printGrid (const char[][COLS]);
void getValidInput(int &, int &); // Gets user input for chests location and validates it

int main() {
    //Variables & Arrays
    const int MAX_GUESS = 3;
    const char EMPTY = 'E';
    const char GRID_SYSTEM = '-';
    const char CHEST_SYM = 'T';
    const int CHEST_QTY = 5; //Amount of chests
    char grid[ROWS][COLS];
    chest chestArray [CHEST_QTY]; //Structure array that'll hold all chest components
    char userReply = 'N'; //Play again?
    double loot = 0.0; //Accumulator or for money earned
    int GuessCounter = 0; //Current number of guesses
    int userRow = 0; // User's guess of row position
    int userColumn = 0; // User's guess of column position

    //Fill grid with symbols
    fillGrid(grid, GRID_SYSTEM);

    //Fill array with chests
    fillArray(chestArray);

    printIntro();

    do{
        std::cout << std::fixed << std::setprecision(2);
        printGrid(grid);
        getValidInput(userRow, userColumn);
        checkUserGuess(grid, userRow, userColumn, chestArray, CHEST_QTY, GuessCounter, EMPTY, CHEST_SYM,
                loot, userReply);
    }while(toupper(userReply) != 'N' && GuessCounter < MAX_GUESS);

    printEndGame(grid, loot, chestArray, CHEST_QTY, CHEST_SYM);
    printGrid(grid);
}

//Print introduction to game
void printIntro(){
    std::cout << "This is a treasure hunt game.\n"
                 "You have 3 attempts to find the 5 treasure chests hidden in the grid below.\n\n";
}
//Creating the chests
void fillArray(chest arr[]) {
         arr[0] = { "Pirate's Chest", 2, 4, 145.90, true };
         arr[1] = { "Dragon's Chest", 5, 8, 258.24, true };
         arr[2] = { "Troll's Chest", 3, 1, 203.71, true };
         arr[3] = { "Queen's Chest", 8, 0, 190.15, true };
         arr[4] = { "Thief's Chest", 1, 9, 98.95, true };
}
//Create a grid full of default symbols
void fillGrid (char arr[][COLS], const char SYM){
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            arr[r][c] = SYM;
        }
    }
}

//Add treasure to the grid
void checkUserGuess(char grid[][COLS], int Row, int Col, chest arr[], const int QTY, int & guess, const char EMP,
        const char CHEST, double & acc, char & retry){
    bool found = false;
    for (int i = 0; i < QTY; ++i) {
            if(Row == arr[i].row && Col == arr[i].col && arr[i].hidden){
                std::cout << "You have found the " << arr[i].chestName << "!\n";
                std::cout << "Inside you find $" << arr[i].value << " worth of valuables.\n\n";
                arr[i].hidden = false;
                guess++;
                grid[Row][Col] = CHEST;
                acc += arr[i].value;
                i = QTY;
                found = true;
            } else if(Row == arr[i].row && Col == arr[i].col && arr[i].hidden == false){
                std::cout << "You already found the treasure at this location. Your stupidity has cost you a guess.\n\n";
                guess++;
                i = QTY;
                found = true;
            }
    }
    if(!found){
        std::cout << "Sorry, there is no treasure at those coordinates.\n";
        guess++;
        grid[Row][Col] = EMP;
    }
    std::cout << "Would you like to play again (Y or N)? \n";
    std::cin >> retry;
    std::cout << std::endl;
    if ((toupper(retry) != 'N' && toupper(retry) != 'Y') || std::cin.fail()){
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore (100, '\n');
            }
        guess = QTY;
    }
}
//Output the grid
void printGrid(const char arr[][COLS]) {
    std::cout << "  " << "0 1 2 3 4 5 6 7 8 9\n";
    for (int r = 0; r < ROWS; r++) {
        std::cout << r << ' ';
            for (int c = 0; c < COLS; c++) {
                std::cout <<  arr[r][c] << ' ';
            }
            std::cout << std::endl;
    }
    std::cout << "\nLegend: - (Unknown); E (Empty); T (Treasure)\n\n";
}

//Get input and validate from user
void getValidInput(int & row, int & col){

    //Getting row # guess
    std::cout <<"Enter the row #: ";
    std::cin >> row;
    std::cout << std::endl;
    while (row < 0 || row > 9 || std::cin.fail()) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore (100, '\n');
        }
        std::cout <<"That entry is invalid. Please enter a valid integer based on the grid size:\n";
        std::cin >> row;
        //std::cout << std::endl;
    }
    //Getting column # Guess
    std::cout << "Enter the column #: ";
    std::cin >> col;
    std::cout << std::endl;

    while (col < 0 || col > 9 || std::cin.fail()) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore (100, '\n');
        }
        std::cout <<"That entry is invalid. Please enter a valid integer based on the grid size: \n";
        std::cin >> col;
        std::cout << std::endl;
    }
}

void printEndGame(char arr1[][COLS], double acc, chest arr2[], int QTY, char CHEST){
    std::cout << "The game is now over. You looted $" << acc << " worth of valuables from chests.\n";
    std::cout << "The grid below shows the position of all treasure chests:\n\n";

    for (int i = 0; i < QTY; i++) {
        int r = arr2[i].row;
        int c = arr2[i].col;
        arr1[r][c] = CHEST;
    }
}