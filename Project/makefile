CXX = g++

CXXFLAGS = 
LDFLAGS = -I/usr/include/SDL2
LDLIBS = -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_gfx

SRC_DIR = src/
OBJ_DIR = obj/
OUT_DIR = bin/

###add .cpp files and .o files here 
SRCS = $(SRC_DIR)main.cpp $(SRC_DIR)avancezlib.cpp $(COMPONENTS) $(SRC_DIR)GameObject.cpp
OBJS = $(OBJ_DIR)main.o $(OBJ_DIR)avancezlib.o

COMPONENTS = $(SRC_DIR)Component.cpp $(SRC_DIR)RenderComponent.cpp $(SRC_DIR)CollideComponent.cpp



all: main.out

main.out: $(OBJS)
	$(CXX) $(LDLIBS) $(LDFLAGS) -o $(OUT_DIR)main.out $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) -c $^ $(LDFLAGS) -o $@
dirs:
	mkdir $(OUT_DIR)
	mkdir $(OBJ_DIR)
clean: 
	rm $(OUT_DIR)main.out $(OBJS)