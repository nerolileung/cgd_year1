#include <iostream>
#include <string>
using namespace std;
int main() {
	string testString = "Do you know who loves C++ XX does!";
	string shortName = "";
	string longName = "";
	cout << "Please enter your name." << endl;
	getline(cin, shortName);
	testString.insert(27, shortName,0,shortName.length()); // inserts shortName at position 27
	cout << testString << endl;
	testString.erase(26, 1); //remove first X
	testString.erase(26+shortName.length(), 1); //remove second X
	cout << testString << endl;
	cout << "Please enter a different name, longer than the previous one." << endl;
	getline(cin, longName);
	testString.replace(26, shortName.length(), longName);
	cout << testString << endl;
	cin.get();
	return 0;
}