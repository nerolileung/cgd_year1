#include <iostream>
#include <chrono> 
#include <thread> 
using namespace std;
using namespace this_thread; // sleep_for, sleep_until 
using namespace chrono_literals; // ns, us, ms, s, h, etc. 
using chrono::system_clock;

int main() {
	int choice;

	cout << "Please choose an option: 1. Sunny 2. Cloudy 3. Raining 4. Exit" << endl;

	cin >> choice;

	switch (choice){
	case 1:
		cout << "Be mindful of heatstroke!" << endl;
		break;
	case 2:
		cout << "Be careful, the worst sunburns happen on cloudy days!" << endl;
		break;
	case 3:
		cout << "Remember to bring an umbrella with you!" << endl;
		break;
	case 4:
		cout << "Have a nice day!" << endl;
		break;
	default:
		cout << "That was not a listed option!" << endl;
		break;
	}

	sleep_for(5s);
	sleep_until(system_clock::now() + 1s);

	cin.get();
	return 0;
}