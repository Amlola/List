all: MYLIST

MYLIST: main.o list.o 
	g++ -g -o myprog.exe main.o list.o -o MYLIST

main.o: main.cpp
	g++ -g -DDUMP -c main.cpp

list.o: list.cpp
	g++ -g -DDUMP -c list.cpp

clean:
	rm *.o MYLIST.exe