#include "BaseAccount.h"
#include "JuniorAccount.h"
#include <string>
#include <iostream>
using namespace std;

JuniorAccount::JuniorAccount() {
}

JuniorAccount::JuniorAccount(string lname, string fname, string addr, float bal) {
	accountType = ACCOUNT_TYPE::JUNIOR;
	accountNum = (rand() % 3000) + 1000;
	interestRate = 1.3f;
	surname = lname;
	forename = fname;
	address = addr;
	balance = bal;
}
void JuniorAccount::viewAccountDetails() {
	cout << "Account number: " << accountNum << endl;
	cout << "Surname: " << surname << endl;
	cout << "Forename: " << forename << endl;
	cout << "Address: " << address << endl;
	cout << "Balance: " << balance << endl;
	cout << "Interest rate: " << interestRate << endl;
	cout << "Account type: Junior" << endl;
}