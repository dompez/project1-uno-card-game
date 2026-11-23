#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    cout << "Uno card game\n";
    // ---------------------------------
    // CREATING MAIN UNO CARD DECK 
    // ---------------------------------
    // 1. INITIALIZE FILE
    ofstream outputFile;
    outputFile.open("UnoMainDeck.txt");

    if (!outputFile) {
        cout << "\nError: Main Uno deck could not be created.\n";
        return 1;
    }

    cout << "Writing to Uno Main Deck\n";
    
    // 2. GENERATE COLORED CARDS
    for (int i = 1; i <= 4; i++) {
        char color;
        if (i == 1) color = 'R';
        else if (i == 2) color = 'B';
        else if (i == 3) color = 'G';
        else color = 'Y';

        // Numbered cards:
        outputFile << color << 0 << endl;           // Code format:
        for (int i = 1; i <= 9; i++) {              // Digits -> 0-9
            for (int j = 1; j <= 2; j++)            // Quantity -> two each
                outputFile << color << i << endl;   // Format -> color + digit
        }
        // +2 cards
        for (int i = 1; i <= 2; i++) 
            outputFile << color << "+2" << endl;
    }

    // 3. GENERATE WILDCARDS
    for (int i = 1; i <= 4; i++) {
        outputFile << "W" << endl;
    }
    for (int i = 1; i <= 4; i++) {
        outputFile << "W+4" << endl;
    }

    // 4. CLOSE FILE

    outputFile.close();

    // 5. VERIFY MAIN DECK

    ifstream inputFile;
    inputFile.open("UnoMainDeck.txt");

    string card;
    int counter;

    while (inputFile >> card) {
        counter++;
    }

     if (counter != 92) {
        cout << "\nError: Main Uno deck incorrect card count when generated.\n";
        return 1;
    }
    // ---------------------------------
    // END CREATING MAIN UNO CARD DECK 
    // ---------------------------------

    //
    //
    //
    

    return 0;
}