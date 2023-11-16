all: MYLIST1

MYLIST1: main.o list_nodes.o 
	g++ -g -o myprog.exe main.o list_nodes.o -o MYLIST1

main.o: main.cpp
	g++ -g -DDUMP -c main.cpp

list.o: list_nodes.cpp
	g++ -g -DDUMP -c list_nodes.cpp

clean:
	rm *.o MYLIST1.exe