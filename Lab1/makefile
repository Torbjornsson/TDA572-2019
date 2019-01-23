CXX = g++

CXXFLAGS = 
LDFLAGS = 
LDLIBS =

SRCS = main.cpp


all: hello.exe

hello.exe: main.o
	$(CXX) -o bin/hello.exe main.o
main.o: $(SRCS)
	$(CXX) -c $(SRCS)
clean: 
	rm bin/hello.exe main.o