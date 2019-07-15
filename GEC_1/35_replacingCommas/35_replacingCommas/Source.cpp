#include <iostream>
#include <string.h>
using namespace std;

void comma2blank(char* textToChange);

int main() {
	char textToChange[40];
	char* pTextToChange = &textToChange[0];
	cout << "Please enter some text with commas. (Max 40 characters.)" << endl;
	cin.getline(textToChange, 40);
	comma2blank(pTextToChange);
	cout << "Without commas, the text entered was: " << textToChange << endl;
	cin.get();
	return 0;
}

void comma2blank(char* textToChange) {
	for (int i = 0; i < 40; i++)	if (*(textToChange+i) == ',')	*(textToChange + i) = ' '; //COMPRESS
}