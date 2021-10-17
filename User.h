#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <fstream>
#include "Exceptions.h"
#include <direct.h>
#include <algorithm>
#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

class User {

	string username = "";
	string password = "";
	double money = 0;
	vector<Transaction> transactions;

public:

	void setUser(string username, string password) {
		this->username = username;
		this->password = password;
	}

	string getUsername() {
		return username;
	}

	void setMoney(double money) {
		if (money < 0) throw ERRInvalidValue();
		this->money = money;
	}

	void input();

	void addToMainFile();
	void createAccountFile();
	void login();
	void logout();
	void buy();
	void sell();

	friend ostream& operator<<(ostream& os, User user);

};

#endif
