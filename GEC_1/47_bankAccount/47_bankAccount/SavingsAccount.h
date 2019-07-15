#pragma once
#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H
#include "BaseAccount.h"

class SavingsAccount : public BaseAccount {
public:
	SavingsAccount();
	SavingsAccount(string lname, string fname, string addr, float bal);
	void viewAccountDetails();
};

#endif // !SAVINGSACCOUNT_H
