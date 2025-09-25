GXXF = g++ -g -fsanitize=address
BUILD_PARTS = build/rect.o build/mystring.o build/addon.o build/matrix.o build/textwrapper.o build/basefile.o
SRC_CPP = $(wildcard src/*.cpp)
SRC_HPP = $(wildcard src/*.hpp)

# Used to test Rect class.
SRC_RECT = src/rect.cpp src/rect.hpp
TEST_RECT_BASIC = tests/test_rect_basic_methods.cpp
TEST_RECT_PROPERTIES = tests/test_rect_properties.cpp
TEST_RECT_OPERATIONS = tests/test_rect_operations.cpp
TEST_BOUNDING_RECT = tests/test_bounding_rect.cpp

# .hpp files depending on one another
src/rect.hpp: src/addon.hpp
src/mystring.hpp: src/addon.hpp
src/barrel.hpp: src/addon.hpp
src/matrix.hpp: src/addon.hpp
src/textwrapper.hpp: src/mystring.hpp
src/basefile.hpp: src/basefile.hpp

# build partial .o files
build/rect.o: $(SRC_RECT)
	g++ -g -c -o build/rect.o src/rect.cpp
build/mystring.o: src/mystring.cpp src/mystring.hpp
	g++ -g -c -o build/mystring.o src/mystring.cpp
build/barrel.o: src/barrel.cpp src/barrel.hpp
	g++ -g -c -o build/barrel.o src/barrel.cpp
build/addon.o: src/addon.cpp src/addon.hpp
	g++ -g -c -o build/addon.o src/addon.cpp
build/matrix.o: src/matrix.cpp src/matrix.hpp
	g++ -g -c -o build/matrix.o src/matrix.cpp
build/textwrapper.o: src/textwrapper.cpp src/textwrapper.hpp
	g++ -g -c -o build/textwrapper.o src/textwrapper.cpp
build/basefile.o: src/basefile.cpp src/basefile.hpp
	g++ -g -c -o build/basefile.o src/basefile.cpp

# debug
build/debug.out: $(BUILD_PARTS) src/main.cpp
	g++ -g -fsanitize=address -o build/debug.out src/main.cpp $(BUILD_PARTS)
debug: build/debug.out
	gdb build/debug.out