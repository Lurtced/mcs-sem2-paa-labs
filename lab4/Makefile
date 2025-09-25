GXXF = g++ -g -fsanitize=address
SRC_CPP = $(wildcard src/*.cpp)
SRC_HPP = $(wildcard src/*.hpp)
BUILD_PARTS = $(wildcard build/*.o)

# .hpp files depending on one another
src/Circle.hpp: src/Point.hpp
src/Node.hpp: src/Circle.hpp
src/List.hpp: src/Node.hpp

# build partial .o files
build/Point.o: src/Point.cpp src/Point.hpp
	g++ -g -c -o build/Point.o src/Point.cpp
build/Circle.o: src/Circle.cpp src/Circle.hpp
	g++ -g -c -o build/Circle.o src/Circle.cpp
build/Node.o: src/Node.cpp src/Node.hpp
	g++ -g -c -o build/Node.o src/Node.cpp
build/List.o: src/List.cpp src/List.hpp
	g++ -g -c -o build/List.o src/List.cpp

# debug
build/debug.out: src/main.cpp $(BUILD_PARTS)
	$(GXXF) -o build/debug.out src/main.cpp $(BUILD_PARTS)
debug: build/debug.out
	gdb build/debug.out
run: build/debug.out
	build/debug.out

# testing
build/circle_test.out: tests/Circle_test.cpp build/Point.o build/Circle.o build/Node.o
	$(GXXF) -o build/circle_test.out tests/Circle_test.cpp build/Point.o build/Circle.o build/Node.o
build/node_test.out: tests/Node_test.cpp build/Point.o build/Circle.o build/Node.o
	$(GXXF) -o build/node_test.out tests/Node_test.cpp build/Point.o build/Circle.o build/Node.o
build/list_test.out: tests/list_test.cpp src/List.hpp build/Point.o build/Circle.o build/Node.o build/List.o
	$(GXXF) -o build/list_test.out tests/List_test.cpp build/Point.o build/Circle.o build/Node.o build/List.o
circle-test: build/circle_test.out
	./build/circle_test.out
node-test: build/node_test.out
	./build/node_test.out
list-test: build/list_test.out
	./build/list_test.out
test: circle-test node-test list-test