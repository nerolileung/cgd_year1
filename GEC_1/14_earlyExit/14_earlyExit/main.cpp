#include <iostream>
#include <chrono> 
#include <thread> 

using namespace std;
using namespace this_thread; // sleep_for, sleep_until 
using namespace chrono_literals; // ns, us, ms, s, h, etc. 

int main() {
	int playerLife = 100;
	int damage;

	for (int i = 1; i < 11; i++) {
		cout << "Question " << i << ": How much should we decrease the health by?" << endl;
		cin >> damage;
		playerLife -= damage;
		damage = 0;

		if (playerLife < 0) {
			cout << "Early exit." << endl;
			sleep_for(5s);
			return 0;
		}
	}

	cout << "All 10 questions asked and player still has life remaining." << endl;

	sleep_for(5s);
	return 0;
}
