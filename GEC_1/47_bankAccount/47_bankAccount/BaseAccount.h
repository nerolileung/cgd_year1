#pragma once
#ifndef BASEACCOUNT_H
#define BASEACCOUNT_H
#define MAXACCOUNTS 100 //arbitrary
#include <string>
using namespace std;

enum ACCOUNT_TYPE {
	GENERAL,
	JUNIOR,
	SAVINGS
};

struct AccountData { // used for reading in data from file
	int accountNum;
	string surname;
	string forename;
	string address;
	float balance;
	float interestRate;
	ACCOUNT_TYPE accountType;
};

class BaseAccount {
public:
	BaseAccount();
	BaseAccount(string lname, string fname, string addr, float bal);
	~BaseAccount();
	ACCOUNT_TYPE accountType;
	int accountNum;
	virtual void viewAccountDetails();
	void saveNewAccount();
	void deleteAccount();
protected:
	string surname;
	string forename;
	string address;
	float balance;
	float interestRate;
};

#endif // !BASEACCOUNT_H
