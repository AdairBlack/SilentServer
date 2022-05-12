CC = g++
CFLAGS = -g -Wall -Werror -I${DIR_INC}

DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC}))

TARGET = SilentClient

BIN_TARGET = ${DIR_BIN}/${TARGET}

all:${BIN_TARGET}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean

clean:
	rm -rf ${DIR_OBJ}/*
	rm -rf ${DIR_BIN}/*
	