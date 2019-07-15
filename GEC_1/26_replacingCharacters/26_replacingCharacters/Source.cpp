#include <iostream>
#include <string>
using namespace std;

int main() {
	string sentence = "";
	cout << "Please enter a single sentence." << endl;
	getline(cin, sentence);
	cout << sentence << endl;
	for (int i = 0; i < sentence.length(); i++) {
		if (sentence.compare(i,1,"e")==0) {
			cout << "X";
		}
		else {
			cout << sentence[i];
		}
	}
	cin.get();
	return 0;
}