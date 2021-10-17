#include <iostream>
#include "User.h"
#include "Crawler.h"
#include "Stock.h"
#include "JSONParser.h"
#include "MAIndicator.h"
#include "EMAIndicator.h"
#include "IndicatorPrinter.h"

using namespace std;

void printMenu() {
    cout << "User menu\n\n1. Gather and show stock data\n\
2. Calculate statistic stock indicators\n3. Show user portfolio \
(buy and sell stocks)\n\n0. Quit\n";
}

int main() {
    User user;
    bool loginFlag = false;
    string choice;
    while (true) {
        if (loginFlag) break;
        cout << "Menu\n\n1. Login\n2. Registration\n\n0. Quit\n";
        cin >> choice;
        if (choice == "1") {
            while (true) {
                try {
                    user.input();
                    user.login();
                    loginFlag = true;
                    break;
                }
                catch (exception& e) {
                    cout << e.what() << endl << "Do you want to go to previous menu?(Y/N)" << endl;
                    string goBack;
                    cin >> goBack;
                    if (goBack == "Y" || goBack == "y") break;
                }
            }
        }
        else if (choice == "2") {
            while (true) {
                try {
                    user.input();
                    user.addToMainFile();
                    while (true) {
                        cout << "Input starting money amount in USD: ";
                        double money;
                        cin >> money;
                        try {
                            user.setMoney(money);
                            user.createAccountFile();
                            break;
                        }
                        catch (exception& e) {
                            cout << e.what() << endl;
                            continue;
                        }
                    }
                    break;
                }
                catch (exception& e) {
                    cout << e.what() << endl;
                }
            }
        }
        else if (choice == "0") {
            cout << "Are you sure you want to quit?(Y/N)\n";
            string confirmation;
            cin >> confirmation;
            if (confirmation == "Y" || confirmation == "y")
                return 0;
        }
        else {
            cout << "Nonexistent command!" << endl;
            continue;
        }
    }
    cout << "Welcome " << user.getUsername() << endl;
    Stock* stock = nullptr;
    Crawler crawler;
    Parser* parser = new JSONParser();
    IndicatorPrinter& printer = IndicatorPrinter::getInstance();
    while (true) {
        printMenu();
        cin >> choice;
        if (choice == "1") {
            //tsla?period1=1617272670&period2=1617531870
            //aapl?period1=1618905600&period2=1618992000
            try {
                crawler.input();
                crawler.collectData();
                if (stock) delete stock;
                stock = crawler.returnStock();
                parser->parseFile(stock);
                cout << *stock << endl;
            }
            catch (exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (choice == "2") {
            if (!stock) {
                cout << "First gather stock data" << endl;
                continue;
            }
            try {
                Indicator::input();
                printer.input();
                printer.output(*stock);
            }
            catch (exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (choice == "3") {
            while (true) {
                cout << user;
                cout << "\n\n1. Buy stocks\n2. Sell stocks\n\n0. Previous menu\n";
                cin >> choice;
                if (choice == "1") {
                    try {
                        user.buy();
                    }
                    catch (exception& e) {
                        cout << e.what() << endl;
                    }
                }
                else if (choice == "2") {
                    try {
                        user.sell();
                    }
                    catch (exception& e) {
                        cout << e.what() << endl;
                    }
                }
                else if (choice == "0") {
                    break;
                }
            }
        }
        else if (choice == "0") {
            cout << "Are you sure you want to quit?(Y/N)\n";
            string confirmation;
            cin >> confirmation;
            if (confirmation == "Y" || confirmation == "y")
                break;
        }
        else {
            cout << "Nonexistent command!" << endl;
            continue;
        }
    }
    user.logout();
    if (stock) delete stock;
    delete parser;
    IndicatorPrinter::deleteInstance();
    cout << "Goodbye!";
    return 0;
}