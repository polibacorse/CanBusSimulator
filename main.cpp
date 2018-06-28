#include <iostream>
#include <fstream>
#include <thread>
#include <csignal>
#include "mymosquitto.h"

using namespace std;

bool running = true;

void interruptHandler(int) {
    cout << "Interrupting message streaming." << endl;
    running = false;
}

int main()
{
    mymosquitto mosq;
    ifstream fileReader("../candump.log");
	string a, json;

    if (!fileReader.is_open()) {
        cout << "ERROR: File \"candump.log\" not found" << endl;
        return -1;
    }

    signal(SIGINT, interruptHandler);
    signal(SIGTERM, interruptHandler);

    while (running) {
        while (fileReader >> a >> json && running) {
            mosq.publish(NULL, "/raw", json.length(), json.c_str());
			cout << json << endl;

            this_thread::sleep_for(chrono::milliseconds(100));
		}

        fileReader.clear();
		fileReader.seekg(0, ios::beg);
	}

    fileReader.close();

    return 0;
}
