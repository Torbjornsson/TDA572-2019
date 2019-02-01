CXX = g++

CXXFLAGS = 
LDFLAGS = -I/usr/include/SDL2
LDLIBS = -lSDL2 -lSDL2main -lSDL2_ttf 

SRCS = lab3.cpp avancezlib.cpp


all: main.out

main.out: main.o
	$(CXX) $(LDLIBS) $(LDFLAGS) -o main.out lab3.o avancezlib.o
main.o: $(SRCS)
	$(CXX) -c $(SRCS) $(LDFLAGS)
clean: 
	rm main.out lab3.o