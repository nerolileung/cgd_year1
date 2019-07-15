#include <iostream>
#include <fstream>
using namespace std;
int main() {
	char character;
	int number = 51;
	int count = 0;
	ofstream out_stream;
	ifstream in_stream1;
	ifstream in_stream2;

	out_stream.open("Integers");
	for (count = 1; count <= 5; count++)	out_stream << number++ << " ";
	out_stream.close();
	
	//count integers in file
	in_stream1.open("Integers");
	count = 0;
	in_stream1 >> number;
	while (!in_stream1.eof()) {
		count++;
		in_stream1 >> number;
	}
	in_stream1.close();
	cout << "There are " << count << " integers in the file,\n";

	// count non-blank characters in file
	in_stream2.open("Integers");
	count = 0;
	in_stream2 >> character;
	while (!in_stream2.eof()) {
		count++;
		in_stream2 >> character;
	}
	in_stream2.close();
	cout << "represented using " << count << " characters." << endl;

	cin.get();
	return 0;
}