# Variables to control Makefile operation

CC = g++
MYDIR = .
SRC_DIR = $(MYDIR)/src
OBJ_DIR = $(MYDIR)/obj
CFLAGS = -Wall -g -Wno-unused-variable
LDFLAGS = -Wall -g -lsfml-graphics -lsfml-window -lsfml-system# link these 

# create list of object files from source files but replace ".cpp" and "src"
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp))

# all:
# 	@echo $(SRC_FILES)
# 	@echo $(OBJ_FILES)

main: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o bin/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<
