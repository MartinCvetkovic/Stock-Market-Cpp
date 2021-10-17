#include "Crawler.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Crawler::collectData() {
    CURL* curl;
    CURLcode res;
    string readBuffer;
    string userURL = "https://query1.finance.yahoo.com/v8/finance/chart/" + stockSymbol +
        "?period1=" + to_string(startPeriod) + "&period2=" + to_string(endPeriod) + "&interval=1h";
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, userURL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    else
        throw ERRCurlError();

    _mkdir("./crawlerData");

    string fileName = "./crawlerData/curl_data.json";
    fstream outFile;
    outFile.open(fileName, ios::out);
    if (outFile.is_open()) {
        outFile << readBuffer;
        outFile.close();
    }
    else
        throw ERROpeningFile();
}

Stock* Crawler::returnStock(){
    return new Stock(stockSymbol, startPeriod, endPeriod);
}

void Crawler::input() {
    long start, end;
    string symbol;
    cout << "Input stock symbol: ";
    cin >> symbol;
    cout << "Input start period as timestamp: ";
    cin >> start;
    cout << "Input end period as timestamp: ";
    cin >> end;
    if (start >= end || start < 0 || end < 0) throw ERRWrongTimestamp();
    startPeriod = start;
    endPeriod = end;
    stockSymbol = symbol;
}

void Crawler::setCrawler(string symb, long start, long end){
    if (start >= end || start < 0 || end < 0) throw ERRWrongTimestamp();
    startPeriod = start;
    endPeriod = end;
    stockSymbol = symb;
}
