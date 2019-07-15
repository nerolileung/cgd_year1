#include <iostream>
using namespace std;
//variables go here, or should they be in main?
const char cardFace[2][5] = {
	{ 'A', 'C', 'E', 'B', 'D' },
{ 'B','A','D','E','C'}
};
const char cardBack[2][5] = {
	{'1','2','3','4','5'},
{'6','7','8','9','0'}
};
char cardUpSide[2][5];
int playerInput;
int playerPoints = 0;
//function initialisers go here
void drawBoard();
char chooseCard();
void flipCard(int row, int col);
void checkPair(char faceA, char faceB);
int main() {
	for (int i = 0; i < 5; i++) {
		cardUpSide[0][i] = cardBack[0][i];
		cardUpSide[1][i] = cardBack[1][i];
	}
	
	do {
		drawBoard();
		checkPair(chooseCard(), chooseCard());
		cin.ignore();
		cin.get();
	} while (playerPoints < 5);
	
	std::cin.get();
	return 0;
}
void drawBoard() {
	system("cls"); // clears output
	for (int i = 0; i < 2; i++) { // looping card by card
		for (int j = 0; j < 5; j++) {
			cout << '[' << cardUpSide[i][j]<< ']';
		}
		cout << endl;
	}
}
char chooseCard() {
	cout << "Enter a number between 0 and 9 (inclusive) to choose a card." << endl;
	cin >> playerInput;
	//flip card depending on input
	if ((playerInput < 0) || (playerInput > 9)) {
		cout << "That was not a number between 0 and 9, try again." << endl;
		chooseCard();
		return 'x';
	}
	else {
		if (playerInput == 0) {
			flipCard(1, 4);
			return cardBack[1][4];
		}
		else if (playerInput < 6) {
			flipCard(0, playerInput - 1);
			return cardBack[0][playerInput - 1];
			
		}
		else {
			flipCard(1, playerInput - 6);
			return cardBack[1][playerInput - 6];
		}
	}
}
void flipCard(int row, int col) {
	if (cardUpSide[row][col] == cardFace[row][col]) {
		cout << "That card is already facing up, try again." << endl;
		chooseCard();
	}
	else {
		cardUpSide[row][col] = cardFace[row][col];
		drawBoard();
	};
}
void checkPair(char faceA, char faceB) {
	int aRow = -1;
	int aCol = -1;
	int bRow = -1;
	int bCol = -1;

	for (int i = 0; i < 2; i++) { // looping card by card again
		for (int j = 0; j < 5; j++) {
			if (cardBack[i][j] == char(faceA)) {
				aRow = i;
				aCol = j;
			}
			else if (cardBack[i][j] == char(faceB)) {
				bRow = i;
				bCol = j;

			}
			
		}
	}
	if (cardUpSide[aRow][aCol] == cardUpSide[bRow][bCol]) { // don't compare face values in case flip goes wrong
		playerPoints++;
		if (playerPoints == 5) {
			cout << "You did it! You won! Well done!" << endl;
		}
		else {
			cout << "Those two cards match! You get 1 point. (You have " <<playerPoints << " points total.) Press enter to continue." << endl;
		}
	}
	else { // return chosen cards facedown
		cardUpSide[aRow][aCol] = cardBack[aRow][aCol];
		cardUpSide[bRow][bCol] = cardBack[bRow][bCol];
		cout << "You guessed wrong. Press enter and try again." << endl;
	}
}