#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>

using namespace std;

class ERRNoUserFile : public exception {
public:
	const char* what() const override {
		return "Error: Register first!";
	}
};

class ERRNoMoney : public exception {
public:
	const char* what() const override {
		return "Error: Not enough resources!";
	}
};

class ERRRegex : public exception {
public:
	const char* what() const override {
		return "Error: No data for given timestamps!";
	}
};

class ERRExistantUsername : public exception {
public:
	const char* what() const override {
		return "Error: Existant username!";
	}
};

class ERROpeningFile : public exception {
public:
	const char* what() const override {
		return "Error: Unable to open file!";
	}
};

class ERRInvalidValue : public exception {
public:
	const char* what() const override {
		return "Error: Invalid value!";
	}
};

class ERRNoUserOrPassword : public exception {
public:
	const char* what() const override {
		return "Error: Incorrect username or password!";
	}
};

class ERRWrongTimestamp : public exception {
public:
	const char* what() const override {
		return "Error: Incorrect timestamp parameters!";
	}
};

class ERRCurlError : public exception {
public:
	const char* what() const override {
		return "Error: CURL error!";
	}
};

#endif 
