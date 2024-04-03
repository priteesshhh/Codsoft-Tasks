    /*
        NOTE: Since points are declared and initialized in main before the main loop,
            once the player goes below zero by default the program will no longer
            allow them to continue playing or even ask to play again.
    */

    #include<iostream>
    #include<cmath>
    #include<string>
    #include<cstring>
    #include<ctime>
    #include<cstdlib>
    #include<iomanip>

    using namespace std;

    // Enum for actions
    enum Action {
        DisplayLeft = 1,
        DisplayRight = 2,
        GuessNumber = 3,
        Reset = 4,
        ExitGame = 5
    };

    // Function to print game header
    void printGameHeader() {
        cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
        cout << "|                                         CodSoft Internship (March 05 - April 05)                                    |" << endl;
        cout << "|                                              Developed with C++ Programming                                         |" << endl;
        cout << "|                                         Building a Number Guessing Game with C++                                    |" << endl;
        cout << "|                                              Priteesh Madhav Reddy Karra                                            |" << endl;
        cout << "+---------------------------------------------------------------------------------------------------------------------+" << endl;
    }
    // Returns true if the given string is a valid name (contains only letters and spaces)
    bool isValidName(string name) {
        // Iterate over each character in the string
        for (int i=0; i<name.length(); i++) {
            // Check if the character is a letter or space using ASCII codes
            if (!(isalpha(name[i]) || isspace(name[i]))) {
                // If the character is not a letter or space, return false
                return false;
            }
        }
        // If all characters are letters or spaces, return true
        return true;
    }
    // Converts the first letter of each word in the given string to uppercase
    string convertFirstLetterToUpperCase(string name) {
        // Initialize a flag to track if the previous character was a whitespace
        bool isPreviousWhiteSpace = true;

        // Iterate over each character in the string
        for (int i=0; i<name.length(); i++) {
            // If this is the first character in the string, or the previous character was a whitespace
            if ((i==0 || isPreviousWhiteSpace) && isalpha(name[i])) {
                // Convert the current character to uppercase
                name[i] = toupper(name[i]);
                // Set the flag to false, since this character is not a whitespace
                isPreviousWhiteSpace = false;
            }
            // If the current character is a whitespace
            else if (isspace(name[i])) {
                // Set the flag to true, since the next character will be the start of a new word
                isPreviousWhiteSpace = true;
            }
            // If none of the above conditions are met, convert the character to lowercase
            else {
                name[i] = tolower(name[i]);
            }
        }
        // Return the modified string
        return name;
    }


    string getName() {
        string name;
        bool isCorrectName = false;
        while (!isCorrectName) {
            // Prompt user to enter their name
            cout << "Please enter your name: ";
            getline(cin, name);
            // Check if the name is valid
            if (!isValidName(name)) {
                cout << "Name should contain only a-z (or) A-Z (or) whitespaces. Please try again...\n";
            }
            else {
                // Format the name with the first letter of each word capitalized and the rest lowercased
                isCorrectName = true;
                name = convertFirstLetterToUpperCase(name);
            }
        }
        return name;
    }

    void genShowMatrix(int visibleMatrix[5][5]) {
        // Loop through each row of the matrix
        for (int i = 0; i < 5; i++) {
            // Loop through each column of the matrix
            for (int j = 0; j < 5; j++) {
                // Set the value of the current cell to -1
                visibleMatrix[i][j] = -1;
            }
        }
    }

    // Generate random numbers between lowerBound and upperBound (inclusive) and fill the matrix with them
    void genHideMatrix(int hideMatrix[5][5], int lowerBound, int upperBound) {
        for (int i = 0; i < 5; i++) { // Loop through rows
            for (int j = 0; j < 5; j++) { // Loop through columns
                // Generate a random number between lowerBound and upperBound
                int randomNumber = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
                // Assign the random number to the current element of the matrix
                hideMatrix[i][j] = randomNumber;
            }
        }
    }

    void showMatrix(int matrix[5][5]) {
        for (int i = 0; i < 5; i++) { // Loop through rows
            for (int j = 0; j < 5; j++) { // Loop through columns
            // reserve space for and display element of 2D matrix
                cout << setw(8) << left << matrix[i][j];
            }
            // next row of matrix
            cout << endl;
        }
    }

    void setdisplayLeft(int& showLower, int randomLower, bool &areBoundsVisible) {
        // check if a bound was already given
        if (areBoundsVisible) {
            // display message that only one bound can be shown
            cout <<  "Already showing one bound. Cannoth show both or you selected the same bound twice." << endl;
        } else {
            // set the display of lower bound to the random lower bound generated by the system
            showLower = randomLower;
            // display a message to indicate the scoring system
            cout<<"Correct guess will only earn 1 point and incorrect guess will lose 10 points\n";
            // set the flag indicating that the bounds are visible
            areBoundsVisible = true;
        }
    }
    void setdisplayRight(int& showUpper, int randomUpper, bool& areBoundsVisible) {
        // check if a bound was already given
        if (areBoundsVisible) {
            // display message that only one bound can be shown
            cout <<  "Already showing one bound. Cannoth show both or you selected the same bound twice." << endl;
        } else {
            // set the display of upper bound to the random upper bound generated by the system
            showUpper = randomUpper;
            // display a message to indicate the scoring system
            cout << "Correct guess will earn 1 point and incorrect guess will lose 10 points.\n";
            // set the flag indicating that the bounds are visible
            areBoundsVisible = true;
        }
    }

    // This function eliminates the entire row and column of the selected cell
    // in both the visible and hidden matrices.
    void eliminate(int visibleMatrix[5][5], int hideMatrix[5][5], int row, int col) {
        // Set all the cells in the selected row to 0 in both matrices.
        for (int i = 0; i < 5; i++) {
            visibleMatrix[row][i] = 0;
            hideMatrix[row][i] = 0;
        }
        
        // Set all the cells in the selected column to 0 in both matrices.
        for (int i = 0; i < 5; i++) {
            visibleMatrix[i][col] = 0;
            hideMatrix[i][col] = 0;
        }
    }
    // This function checks if all elements of the visible matrix are zero
    bool allZeros(const int twoDMatrix[5][5]) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (twoDMatrix[i][j] != 0) {  // If a non-zero element is found
                    return false;  // Return false (not all elements are zero)
                }
            }
        }
        return true;  // If no non-zero elements are found, return true
    }

    // Check if the given guess matches any value in the hidden matrix, and eliminate the corresponding row and column
    bool checkIfGuessInHidenMatrix(int visibleMatrix[5][5], int hideMatrix[5][5], int guess) {
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                if (hideMatrix[i][j] == guess) {  // If the guess matches a value in the hidden matrix
                    eliminate(visibleMatrix, hideMatrix, i, j);  // Eliminate the corresponding row and column
                    return true;  // Return true to indicate that the guess was correct
                }
            }
        }
        return false;  // Return false to indicate that the guess was incorrect
    }
    // Function to handle the player's guess
    void guess(int visibleMatrix[5][5], int hideMatrix[5][5], int &playerPoints, bool areBoundsVisible) {
        // prompt for and get user guess (int)
        int guess;
        cout<<"Enter your guess: " << flush;
        cin>>guess;

        // Determine the number of points the player gains or loses based on whether the bounds are visible
        int gainPoints = areBoundsVisible?1:5;
        int losePoints = areBoundsVisible?10:5;

        // Check if the guess is in the hidden matrix and eliminate the corresponding row and column if it is
        if (checkIfGuessInHidenMatrix(visibleMatrix, hideMatrix, guess)) {
            // Reward player points based on gainPoints, message accordingly
            cout<<"You guessed correctly. You get " << gainPoints << " points\n";
            playerPoints += gainPoints;
        }
        else {
            // Seize player points based on losePoints, message accordingly
            cout<<"You guessed incorrectly. You get -" << losePoints << " points\n";
            playerPoints -= losePoints;
        }
    }

    // Initializes the game by generating random lower and upper bounds, setting the player's points to 100,
    // and initializing the hide and visible matrices
    void initialize(int hideMatrix[5][5], int visibleMatrix[5][5], int &randomLower, int &randomUpper, int &showLower, int &showUpper, bool &areBoundsVisible) {
        // Generate random lower and upper bounds
        randomLower = (rand() % (199 - 100 + 1)) + 100;
        randomUpper = (rand() % (299 - 200 + 1)) + 200;

        // Initialize showLower and showUpper to -1, playerPoints to 100, and areBoundsVisible to false
        showLower = -1;
        showUpper = -1;
        areBoundsVisible = false;

        // Generate the hide matrix using the random lower and upper bounds
        genHideMatrix(hideMatrix, randomLower, randomUpper);

        // Generate the visible matrix
        genShowMatrix(visibleMatrix);
    }

    void displayChoice() {
        // Print the menu options for the user to choose from
        cout << "1. Display Left Number"<<endl;
        cout << "2. Display Right Number"<<endl;
        cout << "3. Guess a number in between"<<endl;
        cout << "4. Reset"<<endl;
        cout << "5. Exit"<<endl;
        
        // Prompt the user to select an action from the menu
        cout << "Enter a number (1-5):  " << flush;
    }

    // Function to ask user if they want to exit the game
    bool exitGame(string playerName, int points) {
        // Ask user for confirmation to exit the game
        char stopPlaying;
        cout << "Do you want to exit the game? (Y/n) ";
        cin >> stopPlaying;
        stopPlaying = tolower(stopPlaying);
        
        // ensure that the user input is valid
        while (stopPlaying != 'y' && stopPlaying != 'n') {
            cout << "Invalid input, please enter y/n to indicate if you would like to exit the game or not: " << flush;
            cin >> stopPlaying;
            stopPlaying = tolower(stopPlaying);
        }

        // If user confirms by entering 'y', return true
        if (stopPlaying == 'y') {
            return true;
        }
        // Otherwise, return false
        return false;
    }

    bool startGameAgain() {
        char startAgain;
        cout << "Do you want to play the game again? (Y/n) "<< flush;
        cin >> startAgain; // get input from user to decide if they want to play again
        startAgain = tolower(startAgain);

        // ensure that the user input is valid
        while (startAgain != 'y' && startAgain != 'n') {
            cout << "Invalid input, please enter y/n to indicate if you would like to play again or not: " << flush;
            cin >> startAgain;
            startAgain = tolower(startAgain);
        }

        if (startAgain == 'y') { // if the user entered 'y', return true
            return true;
        }
        return false; // if the user entered anything else, return false
    }
    int main() {
        // Call printGameHeader to display information about the author
        printGameHeader();

        // Initialize variables
        int playerPoints = 100;
        int randomLower, randomUpper, showLower = -1, showUpper = -1;
        int hideMatrix[5][5], visibleMatrix[5][5];
        bool areBoundsVisible = false;

        // Call initialize function to set up the game
        initialize(hideMatrix, visibleMatrix, randomLower, randomUpper, showLower, showUpper, areBoundsVisible);

        // Get player name and greet the player
        string playerName = getName();
        cout << "Welcome to the game " << playerName << endl;

        bool exitTheGame = false;
        do {
            // Display current range of hidden number
            cout << showLower << " " << showUpper << endl;

            // Get player's choice
            int choice;
            while (true) {
                displayChoice();
                cin >> choice;
                if (choice >= 1 && choice <= 5) {
                    break;
                }
                cout << "Please choose again"<<endl;
            }

            // Perform action based on player's choice
            switch (choice) {
                case DisplayLeft:
                    // Display the lower bound of hidden number
                    setdisplayLeft(showLower, randomLower, areBoundsVisible);
                    break;
                case DisplayRight:
                    // Display the upper bound of hidden number
                    setdisplayRight(showUpper, randomUpper, areBoundsVisible);
                    break;
                case GuessNumber:
                    // Show the player the current show matrix
                    showMatrix(visibleMatrix);
                    // Ask player to guess the hidden number and update game state
                    guess(visibleMatrix, hideMatrix, playerPoints, areBoundsVisible);
                    // Display the updated visible matrix and player's remaining points
                    genShowMatrix(visibleMatrix);
                    cout << "Your remaining points are: " << playerPoints << endl;
                    // Show the player the current show matrix
                    showMatrix(visibleMatrix);
                    // Check if the user won the game
                    if (allZeros(hideMatrix)) {
                        cout << "Congratulations, you have won the game!" << endl;
                        cout << "Your remaining points are: " << playerPoints << endl;
                        if (startGameAgain()) {
                            initialize(hideMatrix, visibleMatrix, randomLower, randomUpper, showLower, showUpper, areBoundsVisible);
                        }
                    }
                    // Game Lost Check is performed in the while loop condition
                case Reset:
                    // Reset the game to initial state
                    initialize(hideMatrix, visibleMatrix, randomLower, randomUpper, showLower, showUpper, areBoundsVisible);

                    playerPoints--;
                    cout << "Your remaining points are: " << playerPoints << endl;

                    // Game Lost Check is performed in the while loop condition
                    break;
                case ExitGame:
                    // Ask player if they want to exit the game
                    exitTheGame = exitGame(playerName, playerPoints); // asks for confirmation, so game may continue
                    break;
            };
        } while (!exitTheGame && playerPoints > 0);

        // If game was ended b/c the player lost, inform them
        if (playerPoints <= 0) {
            cout << "Sorry, you have lost the game. :(" << endl;
        }

        // Personalized goodbye message
        cout << "Thanks for playing, " << playerName << "! Have a nice day." << endl;
        cout << "Your remaining points were: " << playerPoints << endl;

        // End the game
        return 0;
    }

