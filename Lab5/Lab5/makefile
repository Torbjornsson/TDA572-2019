CXX = g++

CXXFLAGS = 
LDFLAGS = -I/usr/include/SDL2
LDLIBS = -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_gfx

SRC_DIR = src/
OBJ_DIR = obj/
OUT_DIR = bin/
SRCS = %.cpp
OBJS = spatialphysics.o game_object.o component.o avancezlib.o



all: spatialphysics.out

spatialphysics.out: $(OBJS)
	$(CXX) $(LDLIBS) $(LDFLAGS) -o $(OUT_DIR)spatialphysics.out $(OBJS)

%.o: %.cpp
	$(CXX) $(LDFLAGS) -c $^ -o $@
dirs:
	mkdir $(OUT_DIR)
	mkdir $(OBJ_DIR)
clean: 
	rm $(OUT_DIR)spatialphysics.out $(OBJS)
	rm -rf $(OUT)