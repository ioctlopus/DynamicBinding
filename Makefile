all: main.cpp activities.o datastructures.o
	g++ -g -Wall -Wextra -o main activities.o datastructures.o main.cpp
activities.o: activities.cpp activities.h
	g++ -g -c -Wall -Wextra -o activities.o activities.cpp
datastructures.o: datastructures.cpp datastructures.h
	g++ -g -c -Wall -Wextra -o datastructures.o datastructures.cpp
clean:
	rm ./main
	rm ./datastructures.o activities.o
tar:
	mkdir ./prog2
	cp ./*.cpp ./prog2/
	cp ./*.h ./prog2/
	cp ./Makefile ./prog2/
	tar -cvf prog2.tar ./prog2/
	rm ./prog2/*
	rmdir ./prog2/
