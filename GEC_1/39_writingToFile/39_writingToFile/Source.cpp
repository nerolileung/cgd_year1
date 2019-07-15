#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
int main() {
	ofstream outfile("example.txt");
	if (!outfile.is_open())
	{
		cerr << "File could not be opened!";
		exit(1);
	}
	outfile << "This is a line.\n";
	outfile << "This is another line.\n";
	outfile.close();
	return 0;
}