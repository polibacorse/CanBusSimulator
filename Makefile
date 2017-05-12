CROSS_COMPILE?=
CXX=g++

all: CanBusSimulator

CanBusSimulator: main.o mymosquitto.o
	$(CROSS_COMPILE)$(CXX) -g -o CanBusSimulator main.o mymosquitto.o -lmosquittopp

%.o: %.cpp
	$(CROSS_COMPILE)$(CXX) -g -c $< --std=c++11

clean:
	rm *.o CanBusSimulator
