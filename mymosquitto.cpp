#include "mymosquitto.h"

mymosquitto::mymosquitto() : mosqpp::mosquittopp("CanBusSim")
{
	const char *host = "localhost";
	this->connect_async(host);
	this->loop_start();
}
