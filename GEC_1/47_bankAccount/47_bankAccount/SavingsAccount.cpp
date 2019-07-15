#include "BaseAccount.h"
#include "SavingsAccount.h"
#include <string>
#include <iostream>
using namespace std;

SavingsAccount::SavingsAccount() {
}

SavingsAccount::SavingsAccount(string lname, string fname, string addr, float bal) {
	accountType = ACCOUNT_TYPE::SAVINGS;
	accountNum = (rand() % 3000) + 1000;
	interestRate = 1.7f;
	surname = lname;
	forename = fname;
	address = addr;
	balance = bal;
}
void SavingsAccount::viewAccountDetails() {
	cout << "Account number: " << accountNum << endl;
	cout << "Surname: " << surname << endl;
	cout << "Forename: " << forename << endl;
	cout << "Address: " << address << endl;
	cout << "Balance: " << balance << endl;
	cout << "Interest rate: " << interestRate << endl;
	cout << "Account type: Savings" << endl;
}