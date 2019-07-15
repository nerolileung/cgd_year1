#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	int menuChoice = 0;
	ofstream outStream;
	ifstream inStream;

	while (menuChoice != 3) {
		string enteredName;
		int enteredScore;
		string scoresFull[10];
		string scoreNames[10];
		int scoreNums[10];
		for (int i = 0; i < 10; i++) {
			scoresFull[i] = "test 0";
			scoreNames[i] = "test";
			scoreNums[i] = 0;
		}
		int chars = 0;
		string scoreEntry;
		int entryCount = 0;
		int numEntry;
		string nameEntry;
		int tempLowest;

		cout << "1. Enter a score" << endl;
		cout << "2. Display scores" << endl;
		cout << "3. Exit" << endl << endl;
		cin >> menuChoice;

		switch (menuChoice) {
		case 1:
			//todo check type of entered variables if necessary??
			cout << "Please enter a name." << endl;
			cin >> enteredName;
			cout << "Please enter a score." << endl;
			cin >> enteredScore;

			//read all existing scores into scores array. note that >> ignores whitespace and that names are stored first, so every other input should be an int
			inStream.open("Scores.txt");
			if (!inStream.is_open()) {
				cout << "Score file not found." << endl;
				break;
			}
			inStream >> nameEntry;
			inStream >> numEntry;
			while (!inStream.eof()) {
				scoreNums[entryCount] = numEntry;
				scoreNames[entryCount] = nameEntry;
				entryCount++; //serves as index number for both name and score values
				inStream >> nameEntry;
				inStream >> numEntry;
			}
			inStream.close();
			// find lowest score by comparing all of them + score to be entered, replace values at that index with entered values
			tempLowest = enteredScore;
			for (int i = 0; i < 10; i++) {
				if (scoreNums[i] < tempLowest) {
					tempLowest = scoreNums[i];
					entryCount = i;
				}
			}
			if (tempLowest != enteredScore) {
				scoreNums[entryCount] = enteredScore;
				scoreNames[entryCount] = enteredName;
			}
			// write updated scores from array back to file
			outStream.open("Scores.txt",ios::trunc);
			for (int i = 0; i < 10; i++) {
				outStream << scoreNames[i] << " " << scoreNums[i] << "\n";
			}
			outStream.close();
			break;
		case 2:
			inStream.open("Scores.txt");
			if (!inStream.is_open()) {
				cout << "Score file not found." << endl;
				break;
			}
			//if there's nothing in the file, there are no scores
			getline(inStream, scoreEntry);
			while (!inStream.eof()) {
				chars++;
				scoresFull[entryCount] = scoreEntry;
				entryCount++;
				getline(inStream, scoreEntry);
			}
			if (chars == 0) {
				cout << "No existing scores were found." << endl;
			}
			else {
				for (int i = 0; i < 10; i++) {
					cout << scoresFull[i] << endl;
				}
			}
			inStream.close();
			cin.ignore();
			cin.get();
			break;
		case 3:
			break;
		default:
			cout << "Input not recognised. Please enter a valid option." << endl;
			cin.ignore();
			cin.get();
			break;
		}
		system("cls");
	}
	cin.get();
	return 0;
}