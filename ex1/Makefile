#!make -f

CXX=clang++-9
CXXFLAGS=-std=c++2a

HEADERS=Document.h Editor.h
OBJECTS=Document.o Editor.o


main: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o main

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o main