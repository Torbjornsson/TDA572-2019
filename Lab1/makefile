all: hello.exe

hello.exe: main.o
	g++ -o bin/hello.exe main.o
main.o: main.cpp
	g++ -c main.cpp
clean: 
	rm bin/hello.exe main.o