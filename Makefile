################################################################################
# Declare some Makefile variables
################################################################################
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall  -Wfatal-errors 
DEBUGGING_SYMBOLS = -g
COMPILER_FLAGS = -w -Wfatal-errors
INCLUDE_PATH = -I"./libs/"
SRC_FILES = ./src/*.cpp \
			./src/game/*.cpp \
			./src/myVertex/*.cpp \
			./src/myModel/*.cpp 
			
			
			
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.4 -lsqlite3
OBJ_NAME = gameengine

################################################################################
# Declare some Makefile rules
################################################################################
build:
	$(CC) $(DEBUGGING_SYMBOLS) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)

git log:
	git log --all --pretty=format:"%h - %an, %ar : %s"



	