GXXF = g++ -g -fsanitize=address
SRC_O = $(wildcard build/*.o)
SRC_RECT = src/rect.cpp src/addon.cpp
TEST_RECT_BASIC = tests/test_rect_basic_methods.cpp
TEST_RECT_PROPERTIES = tests/test_rect_properties.cpp
TEST_RECT_OPERATIONS = tests/test_rect_operations.cpp
TEST_BOUNDING_RECT = tests/test_bounding_rect.cpp

build/rect.o: src/rect.cpp src/rect.hpp
	g++ -g -c -o build/rect.o src/rect.cpp

build/mystring.o: src/mystring.cpp src/mystring.hpp
	g++ -g -c -o build/mystring.o src/mystring.cpp

build/barrel.o: src/barrel.cpp src/barrel.hpp
	g++ -g -c -o build/barrel.o src/barrel.cpp

build/addon.o: src/addon.cpp src/addon.hpp
	g++ -g -c -o build/addon.o src/addon.cpp

build/matrix.o: src/matrix.cpp src/matrix.hpp
	g++ -g -c -o build/matrix.o src/matrix.cpp

src/textwrapper.hpp: src/mystring.hpp

build/textwrapper.o: src/textwrapper.cpp src/textwrapper.hpp
	g++ -g -c -o build/textwrapper.o src/textwrapper.cpp

build/debug.out: build/rect.o build/mystring.o build/barrel.o build/addon.o build/matrix.o build/textwrapper.o src/main.cpp
	g++ -g -o build/debug.out src/main.cpp $(SRC_O)

debug: build/debug.out
	gdb build/debug.out

build/leaks.out: $(SRC_O) src/main.cpp
	$(GXXF) -o build/leaks.out src/main.cpp $(SRC_O)

leaks: build/leaks.out input.txt
	build/leaks.out < input.txt

build/test_rect_basic_methods.out: $(SRC_RECT) $(TEST_RECT_BASIC)
	$(GXXF) -o build/test_rect_basic_methods.out $(SRC_RECT) $(TEST_RECT_BASIC)

test_rect_basic_methods: build/test_rect_basic_methods.out
	build/test_rect_basic_methods.out

build/test_rect_properties.out: $(SRC_RECT) $(TEST_RECT_PROPERTIES)
	$(GXXF) -o build/test_rect_properties.out $(SRC_RECT) $(TEST_RECT_PROPERTIES)

test_rect_properties: build/test_rect_properties.out
	build/test_rect_properties.out

build/test_rect_operations.out: $(SRC_RECT) $(TEST_RECT_OPERATIONS)
	$(GXXF) -o build/test_rect_operations.out $(SRC_RECT) $(TEST_RECT_OPERATIONS)

test_rect_operations: build/test_rect_operations.out
	build/test_rect_operations.out

build/test_bounding_rect.out: $(SRC_RECT) $(TEST_BOUNDING_RECT)
	$(GXXF) -o build/test_bounding_rect.out $(SRC_RECT) $(TEST_BOUNDING_RECT)

test_bounding_rect: build/test_bounding_rect.out
	build/test_bounding_rect.out

test: build/test_rect_basic_methods.out build/test_rect_properties.out build/test_rect_operations.out build/test_bounding_rect.out
	build/test_rect_basic_methods.out
	build/test_rect_properties.out
	build/test_rect_operations.out
	build/test_bounding_rect.out