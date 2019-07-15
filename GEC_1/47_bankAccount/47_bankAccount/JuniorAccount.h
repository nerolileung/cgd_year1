#pragma once
#ifndef JUNIORACCOUNT_H
#define JUNIORACCOUNT_H
#include"BaseAccount.h"

class JuniorAccount : public BaseAccount {
public:
	JuniorAccount();
	JuniorAccount(string lname, string fname, string addr, float bal);
	void viewAccountDetails();
};

#endif // !JUNIORACCOUNT_H
