CC=g++
CFLAGS=-c -Wall -std=c++0x
SOURCES=frequency.cpp se.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=search

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o search
