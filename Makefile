CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = node.h finger.h chord.h
OBJ = Node.o main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

chord: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

