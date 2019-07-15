#include <iostream>
#include <string.h>
using namespace std;

int main() {
	char rawUserInput[24];
	int spaceCounter = 0;
	cout << "Please enter the initials of your first and middle names, followed by your surname, separated using spaces." << endl;
	cin.getline(rawUserInput,24);
	cout << "First initial: " << rawUserInput[0] << endl;
	for (int i = 0; i < 24; i++) {
		if (rawUserInput[i]==' ') {
			spaceCounter++;
			switch (spaceCounter) {
			case 0:
				break;
			case 1:
				cout << "Middle initial: " << rawUserInput[i + 1] << endl;
				break;
			case 2:
				spaceCounter = i+1;
				cout << "Full surname: ";
				break;
			default:
				break;
			}
		}
		if (spaceCounter>2 && spaceCounter==i) {
			cout << rawUserInput[i];
			if (rawUserInput[i] != '\0')	spaceCounter++;
			else cout << endl;
		}
	}

	cin.get();
	return 0;
}