#include <iostream>
#include <fstream>
#include "mymosquitto.h"

using namespace std;

int main()
{
	mymosquitto *mosq = new mymosquitto();
	fstream fileReader("candump.log");
	string a, json;

	while (true) {
		while (fileReader >> a >> json) {
			mosq->publish(NULL, "$SYS/raw", json.length(), json.c_str());
			cout << json << endl;
		}
		fileReader.seekg(0, ios::beg);
	}
}
