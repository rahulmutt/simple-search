CXX=g++
INPUT=main.cpp frequency.cpp cli.cpp gui.cpp common.cpp model.cpp
CFLAGS=-std=c++11 `pkg-config --cflags --libs gtkmm-3.0`
OUTPUT=search
all:
	$(CXX) -o $(OUTPUT) $(INPUT) $(CFLAGS)

clean:
	rm *.o search
