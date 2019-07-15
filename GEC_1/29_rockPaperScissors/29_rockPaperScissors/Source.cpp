#include <iostream>
#include <string>

using namespace std;

int main() {
	int playerWins = 0;
	int computerWins = 0;
	string playerChoice;
	int computerSeed;
	string computerChoice;

	do {
		cout << "Enter rock, paper, or scissors: ";
		getline(cin,playerChoice);
		cout << endl;

		cout << "The computer chose: ";
		computerSeed = rand() % 3;
		switch (computerSeed) {
		case 0:
			computerChoice = "rock";
			break;
		case 1:
			computerChoice = "paper";
			break;
		default:
			computerChoice = "scissors";
			break;
		}
		cout << computerChoice << endl;

		//force player input to lowercase for easy comparison
		for (int i = 0; i < playerChoice.length(); i++) {
			playerChoice[i] = tolower(playerChoice[i]);
		}

		if (playerChoice.compare(computerChoice)==0) {
			cout << "Draw." << endl;
		}
		else if ((playerChoice.compare("rock") == 0) && (computerSeed == 2)) {
			cout << "Player win." << endl;
			playerWins++;
		}
		else if ((playerChoice.compare("paper") == 0) && (computerSeed == 0)) {
			cout << "Player win." << endl;
			playerWins++;
		}
		else if ((playerChoice.compare("scissors") == 0) && (computerSeed == 1)) {
			cout << "Player win." << endl;
			playerWins++;
		}
		else {
			cout << "Computer win." << endl;
			computerWins++;
		}

		cout << "*****" << endl;

	} while ((playerWins != 3)&&(computerWins!=3));

	if (playerWins > computerWins) {
		cout << "Player wins with a score of " << playerWins << " to " << computerWins << '.' << endl;
	}
	else {
		cout << "Computer wins with a score of " << computerWins << " to " << playerWins << '.' << endl;
	}

	cout << "Ending game..." << endl;
	cin.get();
	return 0;
}