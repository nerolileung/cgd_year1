#include <iostream>
using namespace std;

int main() {
	int hariboTotal = 40;
	int studentNum = 14;
	int hariboRem = 40 % 14;
	int hariboStudent = ((hariboTotal - hariboRem) / studentNum);

	cout << "Each student receives " << hariboStudent << " packets, leaving " << hariboRem << " remaining.";
	cin.get();
	return 0;
}