CXX = g++
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: main.cpp Point.o
	$(CXX) $^ -o $@ $(LDLIBS)

Point.o: Point.cpp
	$(CXX) -c $< $(LDLIBS) -o $@

clean:
	rm *.o
	rm main