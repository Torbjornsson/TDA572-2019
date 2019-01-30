CXX = g++

CXXFLAGS = 
LDFLAGS = 
LDLIBS = -lSDL2 -lSDL2main

SRCS = lab3.cpp avancezlib.cpp


all: main.exe

main.exe: main.o
	$(CXX) $(LDLIBS) -o bin/main.exe lab3.o avancezlib.o
main.o: $(SRCS)
	$(CXX) -c $(SRCS)
clean: 
	rm bin/main.exe lab3.o