#include "JSONParser.h"

void JSONParser::parseFile(Stock* stock) {
	regex rx(".*\"timestamp\":\\[([^\\]]*)\\].*\"quote\":\\[\\{([^}]*).*");
	string textLine, timestamps, data, open, close, high, low;
	ifstream jsonFile("./crawlerData/curl_data.json", ios::in);
	smatch result;


	getline(jsonFile, textLine);

	if (regex_match(textLine, result, rx)) {
		timestamps = result.str(1) + ",";
		data = result.str(2);
	}
	else
		throw ERRRegex();

	string name, values;

	for (int i = 0; i < 5; i++) {
		regex rx(",*\"([^\"]*)\":\\[([^\\]]*)\\](.*)");

		if (regex_match(data, result, rx)) {
			name = result.str(1);
			values = result.str(2);
			data = result.str(3);
			if (name == "open") {
				open = values + ",";
			}
			else if (name == "close") {
				close = values + ",";
			}
			else if (name == "high") {
				high = values + ",";
			}
			else if (name == "low") {
				low = values + ",";
			}
		}
		else
			throw ERRRegex();
	}
	long timestamp = 0;
	double opend = 0, highd = 0, lowd = 0, closed = 0;
	string str;

	while (timestamps != "") {
		regex rxt("([^,]*),(.*)");
		if (regex_match(timestamps, result, rxt)) {
			str = result.str(1);
			if (str == "null") continue;
			timestamp = stol(str);
			timestamps = result.str(2);
		}

		regex rxo("([^,]*),(.*)");
		if (regex_match(open, result, rxo)) {
			str = result.str(1);
			if (str == "null") continue;
			opend = stod(str);
			open = result.str(2);
		}

		regex rxc("([^,]*),(.*)");
		if (regex_match(close, result, rxc)) {
			str = result.str(1);
			if (str == "null") continue;
			closed = stod(str);
			close = result.str(2);
		}

		regex rxh("([^,]*),(.*)");
		if (regex_match(high, result, rxh)) {
			str = result.str(1);
			if (str == "null") continue;
			highd = stod(str);
			high = result.str(2);
		}

		regex rxl("([^,]*),(.*)");
		if (regex_match(low, result, rxl)) {
			str = result.str(1);
			if (str == "null") continue;
			lowd = stod(str);
			low = result.str(2);
		}

		stock->candles.push_back(Candle(timestamp, opend, closed, highd, lowd));
	}

}

double JSONParser::parseCurrentPrice(){
	regex rx(".*\"regularMarketPrice\":([^,]*).*");
	string textLine, price;
	ifstream jsonFile("./crawlerData/curl_data.json", ios::in);
	smatch result;


	getline(jsonFile, textLine);

	if (regex_match(textLine, result, rx)) {
		price = result.str(1);
	}
	else
		throw ERRRegex();

	return atof(price.c_str());
}
