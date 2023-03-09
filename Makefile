# Nastase Maria 321CA

CC = g++
CFLAGS  = -g -Wall

TASK1 = task1/walsh
TASK2 = task2/statistics
TASK3 = task3/prinel
TASK4 = task4/crypto

default: build

build: p1 p2 p3 p4

p1: task1/walsh.cpp
	g++ -o walsh task1/walsh.cpp -Wall

p2: task2/statistics.cpp
	g++ -o statistics task2/statistics.cpp -Wall

p3: task3/prinel.cpp
	g++ -o prinel task3/prinel.cpp -Wall

p4: task4/crypto.cpp
	g++ -o crypto task4/crypto.cpp -Wall

run-p1:
	./walsh

run-p2:
	./statistics

run-p3:
	./prinel

run-p4:
	./crypto

clean:
	$(RM) ./walsh ./statistics ./prinel ./crypto