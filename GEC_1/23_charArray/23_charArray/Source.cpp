#include <iostream>
using namespace std;

int main() {
	char testString1[21] = {'T','h','i','s',' ','i','s',' ','t','e','s','t',' ','s','t','i','n','g',' ','1','\0'}; // [sic]
	char testString2[] = "This is test string 2";
	cout << "testString1: " << testString1 << endl;
	cout << "testString2: " << testString2 << endl;
	cin.get();
	return 0;
}