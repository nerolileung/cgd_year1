#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	string line;
	ifstream infile("example.txt");
	if (infile.is_open()) {
		while (getline(infile, line)) {
			cout << line << endl;
		}
		infile.close();
	}
	else {
		cout << "Unable to open file";
	}
	cin.get();
	return 0;
}