#include "ChildClass.h"
#include <iostream>

using namespace std;

int main() {
	cout << "CREATING CHILD CLASS ON HEAP" << endl;
	ChildClass* pChild = new ChildClass();
	cout << "DELETING CHILD CLASS FROM HEAP" << endl;
	delete pChild;
	pChild = nullptr;

	cout << "CREATING CHILD CLASS ON STACK" << endl;
	ChildClass child;
	cin.get();
	cout << "EXITING PROGRAM - STACK WILL NOW BE CLEARED" << endl; // really this should be before cin.get()
	return 0;
}