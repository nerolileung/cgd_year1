#include "BaseAccount.h"
#include "JuniorAccount.h"
#include "SavingsAccount.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ofstream outstream;
	ifstream instream;
	instream.open("accounts.txt");
	while (!instream.is_open()) {
		cout << "Account data file not found. Please wait..." << endl;
		outstream.open("accounts.txt"); // creates file if none exists
		instream.open("accounts.txt");
	}
	outstream.close();
	instream.close();

	int mainMenuChoice = 0;
	int accountMenuChoice = 0;
	while (mainMenuChoice != 4) {
		system("cls");
		cout << "MAIN MENU" << endl;
		cout << "1. Open a new account" << endl;
		cout << "2. View an account" << endl;
		cout << "3. Close an account" << endl;
		cout << "4. Exit program" << endl;
		cout << "Please select an option:" << endl;
		cin >> mainMenuChoice;
		// variables to be used within switch statement
		AccountData accountInput;
		BaseAccount* pAccounts[MAXACCOUNTS]; // use to hold account data when methods need to be called
		int accIndex = 0;
		bool accountFound = false;
		streampos start;
		streampos end;

		switch (mainMenuChoice) {
		case 1:
			system("cls");
			cout << "NEW ACCOUNT MENU" << endl;
			cout << "1. General account" << endl;
			cout << "2. Junior account" << endl;
			cout << "3. Savings account" << endl;
			cout << "4. Return to main menu" << endl;
			cout << "Please select an option:" << endl;
			cin >> accountMenuChoice;
			if (accountMenuChoice > 4 || accountMenuChoice < 1) {
				cout << "That is not a valid option, please try again." << endl;
				accountMenuChoice = 0;
				cin.get();
			}
			else if (accountMenuChoice != 4) { // use accountInput to hold raw input for new account
				cin.ignore();
				cout << "Please enter your first name:" << endl;
				getline(cin, accountInput.forename);
				cout << "Please enter your last name:" << endl;
				getline(cin, accountInput.surname);
				cout << "Please enter your address (in one line):" << endl;
				getline(cin, accountInput.address);
				cout << "Please enter the opening balance of your account:" << endl;
				cin >> accountInput.balance;
				if (accountInput.balance > 0) {
					switch (accountMenuChoice) { // use pAccounts[0] to call methods
					case 1:
						pAccounts[0] = new BaseAccount(accountInput.surname, accountInput.forename, accountInput.address, accountInput.balance);
						pAccounts[0]->saveNewAccount();
						break;
					case 2:
						pAccounts[0] = new JuniorAccount(accountInput.surname, accountInput.forename, accountInput.address, accountInput.balance);
						pAccounts[0]->saveNewAccount();
						break;
					case 3:
						pAccounts[0] = new SavingsAccount(accountInput.surname, accountInput.forename, accountInput.address, accountInput.balance);
						pAccounts[0]->saveNewAccount();
						break;
					}
					delete pAccounts[0];
					cin.ignore();
					cin.get();
				}
				else {
					cout << "That amount of money is insufficient to open an account. Please try again." << endl;
					cin.ignore();
					cin.get();
				}
			} // don't need a conditional for option 4 because it goes to break anyway
			break;
		case 2:
		case 3:
			int accountNumTemp;
			instream.open("accounts.txt");
			//check if file is empty
			start = instream.tellg();
			instream.seekg(0, ios::end); // makes eof true
			end = instream.tellg();
			if (start == end) {
				cout << "No accounts exist yet." << endl;
			}
			else {
				instream.clear();
				instream.seekg(0, ios::beg);
				while (!instream.eof()) {
					instream >> accountInput.accountNum;
					instream >> accountInput.surname;
					instream >> accountInput.forename;
					instream >> accountInput.address;
					instream >> accountInput.balance;
					instream >> accountInput.interestRate;
					int accountTypeTemp = 0;
					instream >> accountTypeTemp;
					switch (accountTypeTemp) {
						break;
					case 1:
						pAccounts[accIndex] = new JuniorAccount(accountInput.surname, accountInput.forename, accountInput.address, accountInput.balance);
						break;
					case 2:
						pAccounts[accIndex] = new SavingsAccount(accountInput.surname, accountInput.forename, accountInput.address, accountInput.balance);
						break;
					default:
						pAccounts[accIndex] = new BaseAccount(accountInput.surname, accountInput.forename, accountInput.address, accountInput.balance);
						break;
					}
					pAccounts[accIndex]->accountNum = accountInput.accountNum;
					accIndex++;
				}
				if (mainMenuChoice == 2) {
					cout << "Please enter the number of the account you wish to view:" << endl;
					cin >> accountNumTemp;
					for (int i = 0; i < accIndex; i++) {
						if (pAccounts[i]->accountNum == accountNumTemp) {
							pAccounts[i]->viewAccountDetails();
							accountFound = true;
						}
					}
					if (!accountFound) {
						cout << "No such account was found.";
					}
				}
				else {
					cout << "Please enter the number of the account you wish to delete:" << endl;
					cin >> accountNumTemp;
					for (int i = 0; i < accIndex; i++) {
						if (pAccounts[i]->accountNum == accountNumTemp) {
							pAccounts[i]->deleteAccount();
							accountFound = true;
						}
					}
					if (!accountFound) {
						cout << "No such account was found.";
					}
				}
			}
			for (int i = 0; i < accIndex; i++)	delete pAccounts[i];
			cin.ignore();
			cin.get();
			instream.close();
			break;
		case 4:
			break;
		default:
			cout << "That is not a valid option, please try again." << endl;
			mainMenuChoice = 0;
			cin.ignore();
			cin.get();
			break;
		}
	}
	cin.get();
	return 0;
}