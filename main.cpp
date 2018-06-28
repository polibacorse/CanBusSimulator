#include <iostream>
#include <fstream>
#include <thread>
#include <csignal>
#include <mosquittopp.h>

using namespace std;

bool running = true;

void interruptHandler(int) {
    cout << "Interrupting message streaming." << endl;
    running = false;
}

int main()
{
    ifstream fileReader("../candump.log");
	string a, json;
    mosqpp::mosquittopp mosq("CanBusSim");

    int rc = mosq.connect("localhost");
    if (rc) {
        cout << "ERROR: Cannot connect to MQTT broker (code " << rc << ")." << endl;
        return -rc;
    }

    if (!fileReader.is_open()) {
        cout << "ERROR: File \"candump.log\" not found." << endl;
        return -1;
    }

    signal(SIGINT, interruptHandler);
    signal(SIGTERM, interruptHandler);

    while (running) {
        while (fileReader >> a >> json && running) {
            mosq.publish(NULL, "/data/raw", json.length(), json.c_str());
			cout << json << endl;

            this_thread::sleep_for(chrono::milliseconds(100));
		}

        fileReader.clear();
		fileReader.seekg(0, ios::beg);
	}

    fileReader.close();
    mosq.disconnect();

    return 0;
}
