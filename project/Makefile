all: create main
create: creat

main: main.o packet.o routing_table.o random.o initialize.o routing.o 
	g++ main.o  packet.o routing_table.o random.o initialize.o routing.o -o main

main.o: main.cpp
	g++ -c main.cpp

packet.o: packet.cpp
	g++ -c packet.cpp

routing_table.o: routing_table.cpp
	g++ -c routing_table.cpp

random.o: random.cpp
	g++ -c random.cpp

initialize.o: initialize.cpp
	g++ -c initialize.cpp

routing.o: routing.cpp
	g++ -c routing.cpp

creat: creat.cpp
	g++ creat.cpp -o creat

clean:
	rm -rf *o main creat a
