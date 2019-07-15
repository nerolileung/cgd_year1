#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main() {
	streampos begin, end;

	ifstream inFile("example.txt", ios::binary);
	if (!inFile) {
		cerr << "File could not be opened!";
		exit(1);
	}

	begin = inFile.tellg(); //get current pointer position in file
	inFile.seekg(0, ios::end); //reposition file poinhter to end of file
	end = inFile.tellg();
	inFile.close();
	cout << "size is: " << (end - begin) << " bytes.\n";

	cin.get();
	return 0;
}