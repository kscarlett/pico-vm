SRC_DIR = src
OUT_DIR = bin
BINARY = picovm
SRC_FILES = main.c
CFLAGS = -Wall -Wextra -g -std=c11
CC = clang

all:
	${CC} ${SRC_DIR}/${SRC_FILES} ${CFLAGS} -o $(OUT_DIR)/$(BINARY)

clean:
	@rm -rf $(OUT_DIR)/*