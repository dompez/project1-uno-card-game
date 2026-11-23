/*
    Test feature for generating and initial deck of Uno cards using loops and
    file system.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // INITIALIZE FILE
    ofstream outputFile;
    outputFile.open("UnoMainDeck.txt");

    if (!outputFile) {
        cout << "\nError: Main Uno deck could not be created.\n";
        return 1;
    }

    cout << "Writing to Uno Main Deck\n";
    
    // GENERATE COLORED CARDS
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

    // GENERATE WILDCARDS
    for (int i = 1; i <= 4; i++) {
        outputFile << "W" << endl;
    }
    for (int i = 1; i <= 4; i++) {
        outputFile << "W+4" << endl;
    }

    // CLOSE FILE

    outputFile.close();

    // VERIFY MAIN DECK

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

    cout << "Cards in deck: " << counter << "\n";

    return 0;
}