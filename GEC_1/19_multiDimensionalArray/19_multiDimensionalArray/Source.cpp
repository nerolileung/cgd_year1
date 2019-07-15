#include <iostream>

using namespace std;

int main() {
	int nums[5][2]{
		{ 0,0 },
	{ 1,2 },
	{ 2,4 },
	{ 3,6 },
	{ 4,8 }
	};

	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 2; col++) {
			cout << "mNumbers[" << row << "][" << col << "]: ";
			cout << nums[row][col] << endl;
		}
	}

	cin.get();
	return 0;
}