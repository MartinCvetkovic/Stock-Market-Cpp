#include "User.h"

void User::input() {
	cout << "Input username (only alphanumeric characters, no blank spaces): ";
	string username;
	cin >> username;
	if (cin.peek() == ' ' || cin.peek() == '\t') {
		cin.ignore(LONG_MAX, '\n');
		throw ERRNoUserOrPassword();
	}
	if (find_if(username.begin(), username.end(), [](char c) { return !isalnum(c); }) != username.end())
		throw ERRNoUserOrPassword();
	cout << "Input password (only alphanumeric characters, no blank spaces): ";
	string password;
	cin >> password;
	if (cin.peek() == ' ' || cin.peek() == '\t') {
		cin.ignore(LONG_MAX, '\n');
		throw ERRNoUserOrPassword();
	}
	if (find_if(password.begin(), password.end(), [](char c) { return !isalnum(c); }) != password.end())
		throw ERRNoUserOrPassword();
	this->setUser(username, password);
}

void User::addToMainFile() {

	_mkdir("./userData");

	string fileName = "./userData/user_data.txt";
	fstream userDataFile;
	userDataFile.open(fileName, ios::in | ios::app);
	if (userDataFile.is_open()) {
		string username, password;
		while (!userDataFile.eof()) {
			userDataFile >> username >> password;
			if (this->username == username) throw ERRExistantUsername();
		}
		userDataFile.clear();
		userDataFile << this->username << " " << this->password << endl;
		userDataFile.close();
	}
	else
		throw ERROpeningFile();
}

void User::createAccountFile() {

	string dirName = "./userData/" + this->username;
	_mkdir(dirName.c_str());

	string fileName = "./userData/" + this->username + "/" + this->username + ".txt";
	fstream userDataFile;
	userDataFile.open(fileName, ios::out);
	if (userDataFile.is_open()) {
		userDataFile << this->username << endl << this->money << endl;
		userDataFile.close();
	}
	else
		throw ERROpeningFile();
}

void User::login() {

	string fileName = "./userData/user_data.txt";
	ifstream userDataFile;
	userDataFile.open(fileName, ios::in);
	bool flag = false;
	string username, password;
	if (userDataFile.is_open()) {
		while (!userDataFile.eof()) {
			userDataFile >> username >> password;
			if (this->username == username && this->password == password) {
				flag = true;
				break;
			}
		}
		userDataFile.close();
	}
	else
		throw ERRNoUserFile();
	if (!flag) throw ERRNoUserOrPassword();
	fileName = "./userData/" + this->username + "/" + this->username + ".txt";
	userDataFile.open(fileName, ios::in);
	double money = 0;
	if (userDataFile.is_open()) {
		userDataFile >> username >> money;
		this->setMoney(money);
		int id;
		string symb;
		double amount, buyCost;
		userDataFile >> id >> symb >> amount >> buyCost;
		while (!userDataFile.eof()) {
			transactions.push_back(Transaction(id, symb, amount, buyCost));
			userDataFile >> id >> symb >> amount >> buyCost;
		}
		userDataFile.close();
	}
	else
		throw ERROpeningFile();
}

void User::logout(){

	string fileName = "./userData/" + this->username + "/" + this->username + ".txt";
	ofstream userDataFile;
	userDataFile.open(fileName, ios::out);
	if (userDataFile.is_open()) {
		userDataFile << username << endl << money << endl;
		for_each(transactions.begin(), transactions.end(), [&userDataFile](Transaction t) {
			if (t.getAmount() != 0) {
				userDataFile << t.getID() << " " << t.getSymbol() << " " << t.getAmount() << " " << t.getBuyCost() << endl;
			}
		});
		userDataFile.close();
	}
	else
		throw ERROpeningFile();

}

void User::buy(){
	cout << "Input stock symbol: ";
	string symbol;
	cin >> symbol;
	cout << "Input buying amount: ";
	double amount;
	cin >> amount;
	double currCost;
	for (auto& tr : transactions) {
		if (symbol == tr.getSymbol()) {
			currCost = tr.getCurrentCost();
			if (money < amount * currCost) throw ERRNoMoney();
			tr.buy(amount, currCost);
			money -= amount * currCost;
			return;
		}
	}
	currCost = Transaction(1, symbol, 1, 0).getCurrentCost();
	if (money < amount * currCost) throw ERRNoMoney();
	int id = transactions.back().getID() + 1;
	transactions.push_back(Transaction(id, symbol, amount, currCost));
	money -= amount * currCost;
}

void User::sell(){
	cout << "Input stock ID: ";
	int id;
	cin >> id;
	cout << "Input selling amount: ";
	double amount;
	cin >> amount;
	for (auto& tr : transactions) {
		if (id == tr.getID()) {
			tr.sell(amount);
			money += tr.getCurrentCost() * amount;
			return;
		}
	}
	throw ERRInvalidValue();
}

ostream& operator<<(ostream& os, User user) {
	os << "User: " << user.getUsername() << endl;
	os << "Current amount of money: " << fixed << setprecision(2) << user.money << endl << endl;
	if (user.transactions.empty()) {
		os << "There are no stocks in possesion\n";
		return os;
	}
	os << setw(10) << left << "ID" << setw(15) << left << "Stock symbol" << setw(20) << left << "Number of stocks" <<
		setw(20) << left << "Buying cost" << setw(20) << left << "Current cost" << setw(20) << left << "Absolute change" <<
		setw(20) << left << "Relative change" << endl;
	for (auto tr : user.transactions) {
		os << setw(10) << left << tr.getID() << setw(15) << left << tr.getSymbol() <<
			fixed << setprecision(4) << setw(20) << left << tr.getAmount() <<
			fixed << setprecision(4) << setw(20) << left << tr.getBuyCost() << fixed << setprecision(4) << setw(20) << left << tr.getCurrentCost();
		if (tr.absoluteDifference() <= 0) os << "\033[0;31m";
		else os << "\033[0;32m";
		os << fixed << setprecision(4) << setw(20) << left << tr.absoluteDifference() <<
			fixed << setprecision(4) << setw(0) << left << tr.relativeDifference() << "%" << endl;
		os << "\033[0m";
	}
	return os;
}
