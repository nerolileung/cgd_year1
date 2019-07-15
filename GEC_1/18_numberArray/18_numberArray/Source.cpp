#include <iostream>
#include <iomanip>

using namespace std;
using std::setw;

int main() {
	int nums[10];
	for (int i = 0; i < 10; i++)	nums[i] = i; // set values in array
	cout << "Array Element" << setw(10) << " Stored Value" << endl; //SETW MAKES A COLUMN
	for (int i = 0; i < 10; i++)	cout << setw(5) << i << setw(20) << nums[i] << endl;
	cin.get();
	return 0;
}