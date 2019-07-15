#include <iostream>
#include <string>
using namespace std;

int main() {
	string testString = "";
	cin >> testString;
	cout << testString;
	getline(cin, testString);
	cout << testString;
	cin.get();
	return 0;
}