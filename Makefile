#OBJS specifies which files to compile as part of the project
OBJS = main.cpp snake.cpp apple.cpp arena.cpp terminal.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -std=c++17

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lncurses

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = SnakeGame

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
