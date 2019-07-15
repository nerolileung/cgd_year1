#include "BaseAccount.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

BaseAccount::BaseAccount() {
	//does nothing, exists to avoid complaints that no default constructor exists
}

BaseAccount::BaseAccount(string lname, string fname, string addr, float bal) { // handles variables only
	accountType = GENERAL;
	accountNum = (rand() % 3000) + 1000;
	interestRate = 1.5f; // 1.1 for junior, 1.7 for savings or whatever
	surname = lname;
	forename = fname;
	address = addr;
	balance = bal;
}
BaseAccount::~BaseAccount() {
}
void BaseAccount::viewAccountDetails() {
	cout << "Account number: " << accountNum << endl;
	cout << "Surname: " << surname << endl;
	cout << "Forename: " << forename << endl;
	cout << "Address: " << address << endl;
	cout << "Balance: " << balance << endl;
	cout << "Interest rate: " << interestRate << endl;
	cout << "Account type: General" << endl;
}
void BaseAccount::saveNewAccount() {
	ifstream inStream;
	ofstream outStream;

	AccountData accounts[MAXACCOUNTS];
	int accIndex = 0;
	inStream.open("accounts.txt");
	if (!inStream.is_open()) {
		cout << "Error: account data file not found. Please close and reopen program." << endl;
		return;
	}
	//check if file is empty; check if file pointer is equal to the end of the file to start with
	streampos start = inStream.tellg();
	inStream.seekg(0, ios::end); // makes eof true
	streampos end = inStream.tellg();
	if (start != end) {
		inStream.clear();
		inStream.seekg(0, ios::beg);
		while (!inStream.eof()) {
			int accountTypeTemp;
			// data must be entered and read in this order
			inStream >> accounts[accIndex].accountNum;
			inStream >> accounts[accIndex].surname;
			inStream >> accounts[accIndex].forename;
			inStream >> accounts[accIndex].address;
			inStream >> accounts[accIndex].balance;
			inStream >> accounts[accIndex].interestRate;
			inStream >> accountTypeTemp;
			switch (accountTypeTemp) {
			case 0:
				accounts[accIndex].accountType = ACCOUNT_TYPE::GENERAL;
				break;
			case 1:
				accounts[accIndex].accountType = ACCOUNT_TYPE::JUNIOR;
				break;
			case 2:
				accounts[accIndex].accountType = ACCOUNT_TYPE::SAVINGS;
				break;
			default: // debug
				cout << "UNKNOWN ACCOUNT TYPE ENCOUNTERED: " << accountTypeTemp << endl;
				cout << "DEFAULTING TO GENERAL ACCOUNT" << endl;
				accounts[accIndex].accountType = ACCOUNT_TYPE::GENERAL;
			}
			accIndex++;
		}
	}
	inStream.close();
	//save new account to end of array
	for (int i = 0; i < accIndex; i++) { //make sure account number is unique
		if (accountNum == accounts[i].accountNum)	accountNum = (rand() % 3000) + 1000;
	}
	accounts[accIndex].accountNum = accountNum;
	accounts[accIndex].surname = surname;
	accounts[accIndex].forename = forename;
	accounts[accIndex].address = address;
	accounts[accIndex].balance = balance;
	accounts[accIndex].interestRate = interestRate;
	accounts[accIndex].accountType = accountType;
	// rewrite all data back, including new account
	outStream.open("accounts.txt", ios::trunc);
	for (int i = 0; i <= accIndex; i++) {
		if (i > 0)	outStream << '\n';
		outStream << accounts[i].accountNum << '\n';
		outStream << accounts[i].surname << '\n';
		outStream << accounts[i].forename << '\n';
		outStream << accounts[i].address << '\n';
		outStream << accounts[i].balance << '\n';
		outStream << accounts[i].interestRate << '\n';
		outStream << (int)accounts[i].accountType;
	}
	cout << "Account " << accountNum << " saved!" << endl;
	outStream.close();
}
void BaseAccount::deleteAccount() { // similar to saving new account, but account to be deleted is not written back to file
	ifstream inStream;
	ofstream outStream;

	AccountData accounts[MAXACCOUNTS];
	int accIndex = 0;

	inStream.open("accounts.txt");
	if (!inStream.is_open()) {
		cout << "Error: account data file not found. Please close and reopen program." << endl;
		return;
	}
	streampos start = inStream.tellg();
	inStream.seekg(0, ios::end); // makes eof true
	streampos end = inStream.tellg();
	if (start != end) {
		inStream.clear();
		inStream.seekg(0, ios::beg);
		while (!inStream.eof()) {
			inStream >> accounts[accIndex].accountNum;
			inStream >> accounts[accIndex].surname;
			inStream >> accounts[accIndex].forename;
			inStream >> accounts[accIndex].address;
			inStream >> accounts[accIndex].balance;
			inStream >> accounts[accIndex].interestRate;
			int accountTypeTemp = 0;
			inStream >> accountTypeTemp; // general is saved as 0, everything else is -842150451
			switch (accountTypeTemp) {
			case 0:
				accounts[accIndex].accountType = ACCOUNT_TYPE::GENERAL;
				break;
			case 1:
				accounts[accIndex].accountType = ACCOUNT_TYPE::JUNIOR;
				break;
			case 2:
				accounts[accIndex].accountType = ACCOUNT_TYPE::SAVINGS;
				break;
			default:
				cout << "UNKNOWN ACCOUNT TYPE ENCOUNTERED: " << accountTypeTemp << endl;
				cout << "DEFAULTING TO GENERAL ACCOUNT" << endl;
				accounts[accIndex].accountType = ACCOUNT_TYPE::GENERAL;
			}
			accIndex++;
		}
	}
	inStream.close();
	// rewrite all data back, excluding current account
	outStream.open("accounts.txt", ios::trunc);
	for (int i = 0; i < accIndex; i++) {
		if (accounts[i].accountNum == accountNum) {
			cout << "Account " << accountNum << " deleted!" << endl;
			continue;
		};
		outStream << accounts[i].accountNum << '\n';
		outStream << accounts[i].surname << '\n';
		outStream << accounts[i].forename << '\n';
		outStream << accounts[i].address << '\n';
		outStream << accounts[i].balance << '\n';
		outStream << accounts[i].interestRate << '\n';
		outStream << accounts[i].accountType << '\n';
	}
	outStream.close();
}