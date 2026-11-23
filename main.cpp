#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int const CARD_PER_PLAYER = 7;  // Number of cards each player is dealt
int const MAX_CARDS = 92;       // Based on a standard deck without skip or reverse cards. Revise if added later.

int main() {

    // ------------------------------------------------------------------
    // GAME INTRODUCTIOIN AND INITIALIZE RANDOM SEED
    // ------------------------------------------------------------------
    cout << "Uno card game\n";
    srand(static_cast<unsigned int>(time(0)));

    // ------------------------------------------------------------------
    // START CREATING MAIN UNO CARD DECK 
    // ------------------------------------------------------------------
    // 1. INITIALIZE OUTPUT FILE
    ofstream outputFileMain;
    cout << "\nCreating Uno card deck...\n";
    outputFileMain.open("UnoMainDeck.txt");

    if (!outputFileMain) {
        cout << "Error: Main Uno deck could not be created.\n\n";
        return 1;
    }

    // 2. GENERATE COLORED CARDS
    for (int i = 1; i <= 4; i++) {
        char color;
        if (i == 1) color = 'R';
        else if (i == 2) color = 'B';
        else if (i == 3) color = 'G';
        else color = 'Y';

        // Numbered cards:
        outputFileMain << color << 0 << endl;           // Code format:
        for (int i = 1; i <= 9; i++) {                  // Digits -> 0-9
            for (int j = 1; j <= 2; j++)                // Quantity -> two each
                outputFileMain << color << i << endl;   // Format -> color + digit
        }
        // +2 cards
        for (int i = 1; i <= 2; i++) 
            outputFileMain << color << "+2" << endl;
    }

    // 3. GENERATE WILDCARDS
    for (int i = 1; i <= 4; i++) {
        outputFileMain << "W" << endl;
    }
    for (int i = 1; i <= 4; i++) {
        outputFileMain << "W+4" << endl;
    }

    // 4. CLOSE FILE
    outputFileMain.close();

    // 5. VERIFY MAIN DECK
    ifstream inputFileMain; // Used to access main UNO deck
    inputFileMain.open("UnoMainDeck.txt");

    if (!inputFileMain) {
        cout << "Error: Main UNO deck could not be accessed for verification.\n\n";
        return 1;
    }

    string cardExist;       // Placeholder for checking card
    int existsCounter = 0;  // Counts the cards that exist

    // Counts cards in main UNO deck:
    while (inputFileMain >> cardExist) {
        existsCounter++;
    }
    
    if (existsCounter != MAX_CARDS) {
        cout << "Error: Main UNO deck incorrect card count detected.\n\n";
        return 1;
    }

    // Close input file:
    inputFileMain.close();
    cout << "Uno card deck successfully created.\n\n";    

    // ------------------------------------------------------------------
    // CREATE USER AND COMPUTER HANDS 
    // ------------------------------------------------------------------
    // 1. INITIALIZE FILES
    cout << "\nDealing User's cards...";

    // User files:
    ofstream outputFileUser;
    outputFileUser.open("UnoUsersHand.txt");

    // 2. DRAW SEVEN RANDOM CARDS FROM MAIN DECK
    int ithUserCard = 1;            // The ith card we are drawing.
    int deckLen = existsCounter;    // Length of the main deck. Uses counter from prior deck verification.
    int randUserPick;               // The ith card from the main deck we'll draw.

    do {
        // Get random card number:
        cout << "\n\nDeck Length: " << deckLen << "\n";
        randUserPick = rand() % deckLen + 1;
        cout << "Random Number Chosen: " << randUserPick << "\n";

        // Open main UNO deck;
        inputFileMain.open("UnoMainDeck.txt");
        int ithCard = 0;    // ith card for iterating through main deck.
        string userCard;    // The card the user will eventually get.

        // Create temporary UNO deck and open:
        ofstream outputFileTempMain;
        outputFileTempMain.open("TempUnoMainDeck.txt");

        // Iterate through main UNO deck until counter matches random selected card:
        while (inputFileMain >> userCard) {
            ithCard++;

            // Chosen card found:
            if (ithCard == randUserPick) {
                outputFileUser << userCard << endl;
                cout << "Card Selected: " << userCard << "\n";
            }
            // If not chosen card then write to temporary main UNO deck file:
            else {
                outputFileTempMain << userCard << endl;
            }
        }

        // Close files:
        inputFileMain.close();
        outputFileTempMain.close();

        // Write temporary UNO deck to main UNO deck:
        ifstream inputFileTempMain;
        inputFileTempMain.open("TempUnoMainDeck.txt");
        outputFileMain.open("UnoMainDeck.txt");

        while (inputFileTempMain >> userCard) {
            outputFileMain << userCard << endl;
        }

        // Close files:
        outputFileMain.close();
        inputFileTempMain.close();

        // Subtract length from deck after card selection:
        deckLen--;
        cout << "Deck Length After Pick: " << deckLen << "\n";
        
        // Finish current draw by incrementing user card counter:
        cout << ithUserCard << " card drawn\n";
        ithUserCard++;

    } while (ithUserCard <= CARD_PER_PLAYER); 

    outputFileUser.close();

    return 0;
}