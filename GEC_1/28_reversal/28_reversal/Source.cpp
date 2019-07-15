#include <iostream>
#include <string>
using namespace std;

int main() {
	int userInput = 0;
	string textInput = "";
	do {
		cout << "Enter a positive integer with at least two digits, or enter -1 to exit." << endl;
		cin >> userInput;
		if (userInput == -1) {
			cout << "Exiting..." << endl;
			break;
		}
		else if (userInput<10) {
			cout << "Value is too small, try again." << endl;
			continue;
			
		}
		else {
			textInput = to_string(userInput);
			cout << "The reverse of the integer is: ";
			for (int i = textInput.length()-1; i >= 0; i--) {
				cout << textInput[i];
			}
			cout << endl;
		}
	} while (userInput > -1);
	cin.ignore();
	cin.get();
	return 0;
}