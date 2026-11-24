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
    cout << "-----------------------------------------"
         << "\nWelcome to the UNO card game program!\n\n"
         << "You and the computer will be dealt " 
         << CARD_PER_PLAYER << " cards each.\n"
         << "Match a card in your hand with the top "
         << "card shown.\n"
         << "Your goal is to not have any "
         << "cards left in your hand.\n";

    cout << "\nAre you ready to play? (press enter to continue): ";
    cin.get();

    srand(static_cast<unsigned int>(time(0)));

// ------------------------------------------------------------------
// CREATING MAIN UNO CARD DECK 
// ------------------------------------------------------------------
// 1. INITIALIZE OUTPUT FILE
    ofstream outputFileMain;
    cout << "\nCreating UNO card deck...\n";
    outputFileMain.open("UnoMainDeck.txt");

    if (!outputFileMain) {
        cout << "Error: Main Uno deck could not be created.\n\n";
        return 1;
    }

// 2. GENERATE COLORED CARDS
    for (int c = 1; c <= 4; c++) {
        char color;
        if (c == 1) color = 'R';
        else if (c == 2) color = 'B';
        else if (c == 3) color = 'G';
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
    cout << "UNO card deck successfully created.\n\n";    

// ------------------------------------------------------------------
// CREATING USER HAND 
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
        // cout << "\n\nDeck Length: " << deckLen << "\n";
        randUserPick = rand() % deckLen + 1;
        // cout << "Random Number Chosen: " << randUserPick << "\n";

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
                // cout << "Card Selected: " << userCard << "\n";
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
        
        // Finish current draw by incrementing user card counter:
        ithUserCard++;

    } while (ithUserCard <= CARD_PER_PLAYER); 

    // Close file:
    outputFileUser.close();
    cout << "\nUser's deck successfully created.\n";

// ------------------------------------------------------------------
// CREATE COMPUTER HAND 
// ------------------------------------------------------------------
// 1. INITIALIZE FILES
    cout << "\nDealing Computer's cards...";
    ofstream outputFileComp;
    ofstream outputFileTempMain;
    ifstream inputFileTempMain;

    // User files:
    outputFileComp.open("UnoCompHand.txt");

// 2. DRAW SEVEN RANDOM CARDS FROM MAIN DECK
    int ithCompCard = 1;            // The ith card we are drawing.
    int randCompPick;               // The ith card from the main deck we'll draw.

    do {
        // Get random card number:
        randCompPick = rand() % deckLen + 1;

        // Open main UNO deck;
        inputFileMain.open("UnoMainDeck.txt");
        int ithCard = 0;    // ith card for iterating through main deck.
        string compCard;    // The card the user will eventually get.

        // Create temporary UNO deck and open:
        outputFileTempMain.open("TempUnoMainDeck.txt");

        // Iterate through main UNO deck until counter matches random selected card:
        while (inputFileMain >> compCard) {
            ithCard++;

            // Chosen card found:
            if (ithCard == randCompPick) {
                outputFileComp << compCard << endl;
                // cout << "Card Selected: " << compCard << "\n";
            }
            // If not chosen card then write to temporary main UNO deck file:
            else {
                outputFileTempMain << compCard << endl;
            }
        }

        // Close files:
        inputFileMain.close();
        outputFileTempMain.close();

        // Write temporary UNO deck to main UNO deck:
        inputFileTempMain.open("TempUnoMainDeck.txt");
        outputFileMain.open("UnoMainDeck.txt");

        while (inputFileTempMain >> compCard) {
            outputFileMain << compCard << endl;
        }

        // Close files:
        outputFileMain.close();
        inputFileTempMain.close();

        // Subtract length from deck after card selection:
        deckLen--;
        
        // Finish current draw by incrementing user card counter:
        ithCompCard++;

    } while (ithCompCard <= CARD_PER_PLAYER); 

    // Close file:
    outputFileComp.close();
    cout << "\nComputer's deck successfully created.\n\n";

// ------------------------------------------------------------------
// DRAW DECK SETUP
// ------------------------------------------------------------------
// 1. CREATE DRAW DECK
    ofstream outputFileDrawDeck;
    string drawCard;
    
// 2. OPEN FILES
    inputFileMain.open("UnoMainDeck.txt");
    outputFileDrawDeck.open("UnoDrawDeck.txt");

// 3. PLACE MAIN DECK INTO DRAW DECK
    while (inputFileMain >> drawCard) {
        outputFileDrawDeck << drawCard << endl;
    }

// 4. CLOSE FILES
    inputFileMain.close();
    outputFileDrawDeck.close();

// ------------------------------------------------------------------
// DISCARD DECK SETUP
// ------------------------------------------------------------------
// 1. CREATE DISCARD DECK AND DRAW DECK
    ofstream outputFileDiscardDeck; 
    ofstream outputFileTempDrawDeck;
    ifstream inputFileDrawDeck;
    ifstream inputFileTempDrawDeck;

// 2. INITIALIZE GAME CONDITTIONS    
    int randDraw;     // Use to assign random number when drawing.    

// 3. ASSIGN RANDOM CARD TO TOP CARD AND BEGIN DISCARD DECK
    inputFileDrawDeck.open("UnoDrawDeck.txt");
    outputFileTempDrawDeck.open("UnoTempDrawDeck.txt");
    outputFileDiscardDeck.open("UnoDiscardDeck.txt");

    randDraw = rand() % deckLen + 1;
    int counter = 0;

    // Get random card from draw deck, place in discard deck, and create temporary draw deck:
    while (inputFileDrawDeck >> drawCard) {
        counter++;
        // Draw random card:
        if (counter == randDraw) {
            outputFileDiscardDeck << drawCard << endl;
        }
        // Temporary draw deck:
        else {
            outputFileTempDrawDeck << drawCard << endl;
        }
    }

    // Subtract length from deck after card selection:
    deckLen--;

    // Close files:
    inputFileDrawDeck.close();
    outputFileTempDrawDeck.close();

    // Overwrite draw deck:
    inputFileTempDrawDeck.open("UnoTempDrawDeck.txt");
    outputFileDrawDeck.open("UnoDrawDeck.txt");

    while (inputFileTempDrawDeck >> drawCard) {
        outputFileDrawDeck << drawCard << endl;
    }

    // Close files
    inputFileTempDrawDeck.close();
    outputFileDrawDeck.close();
    outputFileDiscardDeck.close();

// ------------------------------------------------------------------
// INITIALIZE MAIN GAMEPLAY
// ------------------------------------------------------------------
// 1. INITIALIZE GAME CONDITIONS
    int nUserCards = CARD_PER_PLAYER;   // Tracks how many cards the user has in their current deck.
    int nCompCards = CARD_PER_PLAYER;   // Tracks how many cards the computer has in their current deck.
    char currentColor = ' ';            // Color that must be matched (wild cards have no color of their own).
    int userOwed = 0;                   // Cards the user must draw after the computer played a +2 or +4.
    int compOwed = 0;                   // Cards the computer must draw after the user played a +2 or +4.
    int discardLen = 1;                 // Tracks how many cards are in the discard deck.

    char topCardPref = ' ';             // prefix of the top card (R, B, G, Y, W)
    char topCardPost = ' ';             // post character of the top card's value
    char topCardLast = ' ';             // last character of the top card, only used by +2 and +4

// 2. SET STARTING COLOR BASED ON STARTING CARD
    ifstream inputFileDiscardDeck;
    inputFileDiscardDeck.open("UnoDiscardDeck.txt");
    inputFileDiscardDeck.get(topCardPref);
    inputFileDiscardDeck.get(topCardPost);

    if (topCardPost == '\n') {     // Plain wild card ("W"), nothing after it
        topCardPost = ' ';
    }
    else if (topCardPost == '+') { // "+2" or "+4", so read one more character
        inputFileDiscardDeck.get(topCardLast);
    }

    inputFileDiscardDeck.close();
    currentColor = topCardPref;

// 3. SET COLOR IF WILDCARD SELECTED
    if (currentColor == 'W') {
        int randColor = rand() % 4 + 1;
        if (randColor == 1) currentColor = 'R';
        else if (randColor == 2) currentColor = 'B';
        else if (randColor == 3) currentColor = 'G';
        else currentColor = 'Y';
    }

// ------------------------------------------------------------------
// MAIN GAMEPLAY LOOP 
// ------------------------------------------------------------------
    do {
        // Files used during gameplay:
        ifstream inputFileUser;
        ifstream inputFileComp;
        ifstream inputFileTempHand;
        ofstream outputFileTempHand;
        ifstream inputFileTempDiscard;
        ofstream outputFileTempDiscard;

        string fileCard;                // Placeholder for reading cards from files.
        string drawnCard;               // The card taken from the draw deck.

// ------------------------------------------------------------------
// RESHUFFLE DISCARD DECK INTO DRAW DECK IF THE DRAW DECK IS RUNNING LOW
// ------------------------------------------------------------------
// 1. SAVE TOP CARD FROM DISCARD DECK
        if (deckLen < 8 && discardLen > 1) {
            string topDiscard;          // The top card stays in the discard deck.

            inputFileDiscardDeck.open("UnoDiscardDeck.txt");
            inputFileDrawDeck.open("UnoDrawDeck.txt");
            outputFileTempDrawDeck.open("UnoTempDrawDeck.txt");
            inputFileDiscardDeck >> topDiscard;

// 2. MOVE REST OF DISCARD DECK TO TEMPORARY DRAW DECK            
            while (inputFileDiscardDeck >> drawCard) {
                outputFileTempDrawDeck << drawCard << endl;
                deckLen++;
            }

// 3. MOVE REST OF DRAW DECK TO BOTTOM of TEMPORARY DECK            
            while (inputFileDrawDeck >> drawCard) {
                outputFileTempDrawDeck << drawCard << endl;
            }

            inputFileDiscardDeck.close();
            inputFileDrawDeck.close();
            outputFileTempDrawDeck.close();

// 4. OVERWRITE DRAW DECK WITH TEMPORARY DRAW DECK                        
            inputFileTempDrawDeck.open("UnoTempDrawDeck.txt");
            outputFileDrawDeck.open("UnoDrawDeck.txt");

            while (inputFileTempDrawDeck >> drawCard) {
                outputFileDrawDeck << drawCard << endl;
            }

            inputFileTempDrawDeck.close();
            outputFileDrawDeck.close();

// 5. RESTART DRAW DECK WITH TOP CARD ON TOP                        
            outputFileDiscardDeck.open("UnoDiscardDeck.txt");
            outputFileDiscardDeck << topDiscard << endl;
            outputFileDiscardDeck.close();
            discardLen = 1;

            cout << "The discard deck was reshuffled into the draw deck.\n";
        }

// ------------------------------------------------------------------
// USER'S TURN
// ------------------------------------------------------------------
        cout << "-------------------------------------\n";

// 1. SHOW TOP CARD, COMPUTER'S CARD COUNT, AND USER'S CARDS
        cout << "Top card: " << topCardPref;
        if (topCardPost != ' ') cout << topCardPost;
        if (topCardLast != ' ') cout << topCardLast;
        if (topCardPref == 'W') {
            cout << " (color: " << currentColor << ")";
        }
        cout << "\n\n";

        string userCard;
        inputFileUser.open("UnoUsersHand.txt");

        cout << "Computer's cards: " << nCompCards << "\n";
        cout << "Your cards: ";
        while (inputFileUser >> userCard) {
            cout << userCard << " ";
        }
        inputFileUser.close();
        cout << "\n";

// 2. USER TURN VARIABLES
        bool userPlayed = false;        // True if the user is playing a card this turn.
        int userDraw = 0;               // Number of cards the user draws this turn.

        string userPlayCard;            // The card the user is playing, written as text 
        char userPlayPre = ' ';         // Card the user is playing.
        char userPlayPost = ' ';
        char userPlayLast = ' ';

// 3. USER MUST DRAW IF THE COMPUTER PLAYED A +2 OR +4 IN THE PREVIOUS TURN
        if (userOwed > 0) {
            userDraw = userOwed;
            userOwed = 0;

            cout << "\nYou must draw " << userDraw << " cards (press enter to continue): ";
            cin.get();
        }
        else {            

// 4. IF NO +2 OR +4 USER SELECTS CARD OR CHOOSES TO DRAW
            bool validChoice = false;

            // User input loop and validation:
            do {
                // Reading user input:
                userPlayLast = ' ';
                cout << "\nEnter a card to play, or D to draw a card: ";
                cin.get(userPlayPre);
                cin.get(userPlayPost);
                if (userPlayPost == '\n') {
                    userPlayPost = ' ';
                }
                else if (userPlayPost == '+') {
                    cin.get(userPlayLast);
                    if (userPlayLast == '\n') userPlayLast = ' ';
                    else cin.ignore(1000, '\n');
                }
                else {
                    cin.ignore(1000, '\n');
                }

                // User chooses to draw a card:
                if (userPlayPre == 'D' && userPlayPost == ' ') {
                    userDraw = 1;
                    validChoice = true;
                }
                else {
                    // Write the choice as text so it can be compared:
                    userPlayCard = userPlayPre;
                    if (userPlayPost != ' ') userPlayCard += userPlayPost;
                    if (userPlayLast != ' ') userPlayCard += userPlayLast;

                    // Checking if card is in user's hand:
                    bool inHand = false;
                    inputFileUser.open("UnoUsersHand.txt");
                    while (inputFileUser >> fileCard) {
                        if (fileCard == userPlayCard) {
                            inHand = true;
                        }
                    }
                    inputFileUser.close();

                    // Checking if card matches the color, matches the value, or is a wild:
                    bool canPlay = (userPlayPre == currentColor || userPlayPre == 'W' || 
                                   (userPlayPost == topCardPost && userPlayLast == topCardLast));

                    if (!inHand) {
                        cout << "That card is not in your hand (use capital letters). Try again.\n";
                    }
                    else if (!canPlay) {
                        cout << "That card does not match the top card. Try again.\n";
                    }
                    else {
                        userPlayed = true;
                        validChoice = true;
                    }
                }
            } while (!validChoice);
        }

// 5. USER DRAWS CARDS FROM DRAW DECK (SKIPS IF userDraw = 0)
        for (int d = 1; d <= userDraw; d++) {   
            if (deckLen > 0) {
                randDraw = rand() % deckLen + 1;
                counter = 0;
                
                // Place in draw deck:
                inputFileDrawDeck.open("UnoDrawDeck.txt");
                outputFileTempDrawDeck.open("UnoTempDrawDeck.txt");

                while (inputFileDrawDeck >> drawCard) {
                    counter++;
                    // Remember the drawn card:
                    if (counter == randDraw) {
                        drawnCard = drawCard;
                        cout << "You drew: " << drawCard << "\n";
                    }
                    else {
                        outputFileTempDrawDeck << drawCard << endl;
                    }
                }
                inputFileDrawDeck.close();
                outputFileTempDrawDeck.close();

                // Create temp hand file and append drawn card
                inputFileUser.open("UnoUsersHand.txt");
                outputFileTempHand.open("UnoTempHand.txt");

                while (inputFileUser >> fileCard) {
                    outputFileTempHand << fileCard << endl;
                }
                outputFileTempHand << drawnCard << endl;

                inputFileUser.close();
                outputFileTempHand.close();

                // Overwrite current user hand with the temp hand file:
                inputFileTempHand.open("UnoTempHand.txt");
                outputFileUser.open("UnoUsersHand.txt");

                while (inputFileTempHand >> fileCard) {
                    outputFileUser << fileCard << endl;
                }

                inputFileTempHand.close();
                outputFileUser.close();

                // Overwrite draw deck to remove drawn card:
                inputFileTempDrawDeck.open("UnoTempDrawDeck.txt");
                outputFileDrawDeck.open("UnoDrawDeck.txt");

                while (inputFileTempDrawDeck >> drawCard) {
                    outputFileDrawDeck << drawCard << endl;
                }

                inputFileTempDrawDeck.close();
                outputFileDrawDeck.close();

                // drawn deck length reduced by each draw:
                deckLen--;

                // User has another card:
                nUserCards++;
            }
            else {
                cout << "There are no cards left to draw.\n";
            }
        }

// 6. USER PLAYS THE CHOSEN CARD
        if (userPlayed) {
            // Remove card from the user's hand (only one copy):
            bool removed = false;
            inputFileUser.open("UnoUsersHand.txt");
            outputFileTempHand.open("UnoTempHand.txt");

            // Find card and write rest to temporary file:
            while (inputFileUser >> fileCard) {
                if (fileCard == userPlayCard && !removed) {
                    removed = true;
                }
                else {
                    outputFileTempHand << fileCard << endl;
                }
            }

            inputFileUser.close();
            outputFileTempHand.close();

            // Write temporary hand back to the user's hand:
            inputFileTempHand.open("UnoTempHand.txt");
            outputFileUser.open("UnoUsersHand.txt");

            while (inputFileTempHand >> fileCard) {
                outputFileUser << fileCard << endl;
            }

            inputFileTempHand.close();
            outputFileUser.close();

            // Played card becomes the new top card:
            topCardPref = userPlayPre;
            topCardPost = userPlayPost;
            topCardLast = userPlayLast;

            // Newest card goes first in the discard deck (copy old cards to temporary file after it):
            inputFileDiscardDeck.open("UnoDiscardDeck.txt");
            outputFileTempDiscard.open("UnoTempDiscardDeck.txt");
            outputFileTempDiscard << userPlayCard << endl;

            while (inputFileDiscardDeck >> fileCard) {
                outputFileTempDiscard << fileCard << endl;
            }

            inputFileDiscardDeck.close();
            outputFileTempDiscard.close();

            inputFileTempDiscard.open("UnoTempDiscardDeck.txt");
            outputFileDiscardDeck.open("UnoDiscardDeck.txt");

            while (inputFileTempDiscard >> fileCard) {
                outputFileDiscardDeck << fileCard << endl;
            }

            inputFileTempDiscard.close();
            outputFileDiscardDeck.close();
            discardLen++;

            // Update the user's card count:
            nUserCards--;
            cout << "\nYou played: " << userPlayCard << "\n";

            // 7. UPDATE CURRENT COLOR
            if (userPlayPre == 'W') {
                // User picks the new color:
                do {
                    cout << "Choose a color (R, B, G, Y): ";
                    cin.get(currentColor);
                    if (currentColor != '\n') cin.ignore(1000, '\n');
                } while (currentColor != 'R' && currentColor != 'B' && 
                         currentColor != 'G' && currentColor != 'Y');

                cout << "The color is now " << currentColor << ".\n";
            }
            else {
                currentColor = userPlayPre;
            }

            // 8. APPLY +2 AND +4 EFFECTS AGAINST COMPUTER
            if (userPlayPost == '+' && userPlayLast == '2') {
                compOwed = 2;
            }
            else if (userPlayPost == '+' && userPlayLast == '4') {
                compOwed = 4;
            }
        }

// ------------------------------------------------------------------
// COMPUTER'S TURN (skipped if the user just played their last card)
// ------------------------------------------------------------------
        if (nUserCards > 0) {
            cout << "-------------------------------------\n";
            cout << "Computer's turn (" << nCompCards << " cards in hand).\n";

// 1. COMPUTER TURN VARIABLES
            bool compPlayed = false;        // True if the computer is playing a card this turn.
            int compDraw = 0;               // Number of cards the computer draws this turn.

            char compPlayPre = ' ';         // Card the computer is playing (the first playable card it finds).
            char compPlayPost = ' ';
            char compPlayLast = ' ';
            string compPlayCard;            // The card the computer is playing, written as text.

            char compHandPre;               // The card being checked in the computer's hand.
            char compHandPost;
            char compHandLast;

// 2. COMPUTER MUST DRAW IF THE USER PLAYED A +2 OR +4
            if (compOwed > 0) {
                compDraw = compOwed;
                compOwed = 0;

                cout << "\nComputer must draw " << compDraw << " cards.\n";
            }
            else {

// 3. COMPUTER LOOKS FOR A PLAYABLE CARD IN ITS HAND
                inputFileComp.open("UnoCompHand.txt");

                while (inputFileComp.get(compHandPre)) {
                    inputFileComp.get(compHandPost);
                    compHandLast = ' ';

                    if (compHandPost == '\n') {
                        compHandPost = ' ';
                    }
                    else {
                        if (compHandPost == '+') {
                            inputFileComp.get(compHandLast);
                        }
                        inputFileComp.get();
                    }

                    // If able to, the computer will play the first card it can:
                    if (!compPlayed && (compHandPre == currentColor || compHandPre == 'W' || 
                                       (compHandPost == topCardPost && compHandLast == topCardLast))) {
                        compPlayed = true;
                        compPlayPre = compHandPre;
                        compPlayPost = compHandPost;
                        compPlayLast = compHandLast;
                    }
                }
                inputFileComp.close();

                // No playable card, so draw one:
                if (!compPlayed) {
                    compDraw = 1;
                    cout << "\nComputer has no playable card and draws a card.\n";
                }
            }

// 4. COMPUTER DRAWS CARDS FROM DRAW DECK
            for (int d = 1; d <= compDraw; d++) {
                if (deckLen > 0) {
                    randDraw = rand() % deckLen + 1;
                    counter = 0;

                    inputFileDrawDeck.open("UnoDrawDeck.txt");
                    outputFileTempDrawDeck.open("UnoTempDrawDeck.txt");

                    while (inputFileDrawDeck >> drawCard) {
                        counter++;
                        // Remember the drawn card:
                        if (counter == randDraw) {
                            drawnCard = drawCard;
                        }
                        else {
                            outputFileTempDrawDeck << drawCard << endl;
                        }
                    }

                    inputFileDrawDeck.close();
                    outputFileTempDrawDeck.close();

                    // Add drawn card to the end of the computer's hand (copy hand to temporary file first):
                    inputFileComp.open("UnoCompHand.txt");
                    outputFileTempHand.open("UnoTempHand.txt");

                    while (inputFileComp >> fileCard) {
                        outputFileTempHand << fileCard << endl;
                    }
                    outputFileTempHand << drawnCard << endl;

                    inputFileComp.close();
                    outputFileTempHand.close();

                    inputFileTempHand.open("UnoTempHand.txt");
                    outputFileComp.open("UnoCompHand.txt");

                    while (inputFileTempHand >> fileCard) {
                        outputFileComp << fileCard << endl;
                    }

                    inputFileTempHand.close();
                    outputFileComp.close();

                    // Overwrite draw deck:
                    inputFileTempDrawDeck.open("UnoTempDrawDeck.txt");
                    outputFileDrawDeck.open("UnoDrawDeck.txt");

                    while (inputFileTempDrawDeck >> drawCard) {
                        outputFileDrawDeck << drawCard << endl;
                    }

                    inputFileTempDrawDeck.close();
                    outputFileDrawDeck.close();

                    deckLen--;
                    nCompCards++;
                }
                else {
                    cout << "There are no cards left to draw.\n";
                }
            }

// 5. COMPUTER PLAYS ITS CARD
            if (compPlayed) {
                compPlayCard = compPlayPre;
                if (compPlayPost != ' ') compPlayCard += compPlayPost;
                if (compPlayLast != ' ') compPlayCard += compPlayLast;

                // Remove card from the computer's hand (only one copy):
                bool removed = false;
                inputFileComp.open("UnoCompHand.txt");
                outputFileTempHand.open("UnoTempHand.txt");

                while (inputFileComp >> fileCard) {
                    if (fileCard == compPlayCard && !removed) {
                        removed = true;
                    }
                    else {
                        outputFileTempHand << fileCard << endl;
                    }
                }

                inputFileComp.close();
                outputFileTempHand.close();

                // Write temporary hand back to the computer's hand:
                inputFileTempHand.open("UnoTempHand.txt");
                outputFileComp.open("UnoCompHand.txt");

                while (inputFileTempHand >> fileCard) {
                    outputFileComp << fileCard << endl;
                }

                inputFileTempHand.close();
                outputFileComp.close();

                // Played card becomes the new top card:
                topCardPref = compPlayPre;
                topCardPost = compPlayPost;
                topCardLast = compPlayLast;

                // Newest card goes first in the discard deck (copy old cards to temporary file after it):
                inputFileDiscardDeck.open("UnoDiscardDeck.txt");
                outputFileTempDiscard.open("UnoTempDiscardDeck.txt");
                outputFileTempDiscard << compPlayCard << endl;

                while (inputFileDiscardDeck >> fileCard) {
                    outputFileTempDiscard << fileCard << endl;
                }

                inputFileDiscardDeck.close();
                outputFileTempDiscard.close();

                inputFileTempDiscard.open("UnoTempDiscardDeck.txt");
                outputFileDiscardDeck.open("UnoDiscardDeck.txt");

                while (inputFileTempDiscard >> fileCard) {
                    outputFileDiscardDeck << fileCard << endl;
                }

                inputFileTempDiscard.close();
                outputFileDiscardDeck.close();
                discardLen++;

                // Update the computer's card count:
                nCompCards--;
                cout << "\nComputer played: " << compPlayCard << "\n";

// 6. UPDATE CURRENT COLOR
                if (compPlayPre == 'W') {
                    // Computer picks a random color:
                    int randColor = rand() % 4 + 1;
                    if (randColor == 1) currentColor = 'R';
                    else if (randColor == 2) currentColor = 'B';
                    else if (randColor == 3) currentColor = 'G';
                    else currentColor = 'Y';

                    cout << "The color is now " << currentColor << ".\n";
                }
                else {
                    currentColor = compPlayPre;
                }

// 7. APPLY +2 AND +4 EFFECTS AGAINST USER
                if (compPlayPost == '+' && compPlayLast == '2') {
                    userOwed = 2;
                }
                else if (compPlayPost == '+' && compPlayLast == '4') {
                    userOwed = 4;
                }
            }
        }
    } while (nUserCards > 0 && nCompCards > 0);

// ------------------------------------------------------------------
// ANNOUNCE WINNER
// ------------------------------------------------------------------
    cout << "-------------------------------------\n";
    if (nUserCards == 0) {
        cout << "Congratulations! You played all of your cards and won the game!\n\n";
    }
    else {
        cout << "The computer played all of its cards and won the game.\n\n";
    }

    return 0;
}