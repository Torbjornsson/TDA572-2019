CXX = g++

CXXFLAGS = 
LDFLAGS = -I/usr/include/SDL2
LDLIBS = -lSDL2 -lSDL2main -lSDL2_ttf 

SRC_DIR = src/
OBJ_DIR = obj/
OUT_DIR = bin/
SRCS = $(SRC_DIR)main.cpp $(SRC_DIR)avancezlib.cpp
OBJS = $(OBJ_DIR)main.o $(OBJ_DIR)avancezlib.o



all: main.out
	dir

main.out: $(OBJS)
	$(CXX) $(LDLIBS) $(LDFLAGS) -o $(OUT_DIR)main.out $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) -c $^ $(LDFLAGS) -o $@
dir:
	mkdir $(OUT_DIR)
	mkdir $(OBJ_DIR)
clean: 
	rm main.out $(OBJS)
	rm -rf $(OUT)