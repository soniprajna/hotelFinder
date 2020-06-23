output: functions.o main.o
	g++ main.o functions.o -o hotelFinder

myFunctions.o: functions.cpp header.h
	g++ -c functions.cpp

project2: main.cpp
	g++ -c main.cpp

clean:
	rm *.o hotelFinder