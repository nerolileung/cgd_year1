#include "Cat.h"
#include <iostream>
using namespace std;

int main() {
	Cat button(5); //created on stack
	Cat* pDaisy = new Cat(10); // on heap

	cout << "Button is " << button.GetAge() << " years old." << endl;
	cout << "Daisy is " << pDaisy->GetAge() << " years old." << endl;
	cin.get();
	delete pDaisy;
	pDaisy = nullptr;
	return 0;
}