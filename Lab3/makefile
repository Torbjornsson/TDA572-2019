CXX = g++

CXXFLAGS = 
LDFLAGS = -I/usr/include/freetype2 -I/usr/include/SDL2
LDLIBS = -lSDL2 -lSDL2main -lSDL_ttf -lfreetype

SRCS = lab3.cpp avancezlib.cpp


all: main.exe

main.exe: main.o
	$(CXX) $(LDLIBS) $(LDFLAGS) -o main.exe lab3.o avancezlib.o
main.o: $(SRCS)
	$(CXX) -c $(SRCS) $(LDFLAGS)
clean: 
	rm main.exe lab3.o