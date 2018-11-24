CC = g++
CFLAGS = -Wall -std=c++11 -lssl -lcrypto -pthread -O0 -g3 -fmessage-length=0
DEPS = node.h chord.h helper.h finger.h create.h
OBJ = helper.o init.o Node.o create.o main.o
all: chord
%.o: %.cpp $(DEPS)
	$(CC)  -c -o $@ $< $(CFLAGS)
chord: $(OBJ)
	$(CC)  -o $@ $^ $(CFLAGS)