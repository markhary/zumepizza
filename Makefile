# Compiler options
CC=g++
CFLAGS=-c -Wall -std=c++11 -pedantic-errors
LDFLAGS=
EXECUTABLE_NAME=test

# Folders
SRC_DIRS := src
INC_DIRS := include
BIN=bin
OBJ=obj

##
## Don't change below here
##

# Files
SRC_FILES := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CFLAGS+=$(INC_FLAGS)

EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)
OBJECT_FILES     = $(SRC_FILES:%.cpp=$(OBJ)/%.o)
# ^^^ A more succinct expression for $(OBJECT_FILES), using
#     http://www.gnu.org/software/make/manual/make.html#Substitution-Refs

build: $(EXECUTABLE_FILES)

clean:
	rm -r -f $(BIN)
	@# ^^^ I don't recommend suppressing the echoing of the command using @

# http://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: build clean

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) -o $@ $^
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#Automatic-Variables
	@echo "Build successful!"

# http://www.gnu.org/software/make/manual/make.html#Static-Pattern
$(OBJECT_FILES): $(OBJ)/%.o: %.cpp
	@echo Compiling $<
	@# ^^^ Your terminology is weird: you "compile a .cpp file" to create a .o file.
	mkdir -p $(@D)
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	$(CC) $(CFLAGS) -o $@ $<
	@# ^^^ Use $(CFLAGS), not $(LDFLAGS), when compiling.
