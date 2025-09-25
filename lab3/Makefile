GXXF = g++ -g -fsanitize=address
GXXC = g++ -g -c
SRC_CPP = $(wildcard src/*.cpp)
SRC_HPP = $(wildcard src/*.hpp)
BUILD_PARTS = $(wildcard build/*.o)

# .hpp files depending on one another
src/workerdb.hpp: src/mystring.hpp

# build partial .o files
build/matrix.o: src/matrix.cpp src/matrix.hpp
	$(GXXC) -o build/matrix.o src/matrix.cpp
build/mystring.o: src/mystring.cpp src/mystring.hpp
	$(GXXC) -o build/mystring.o src/mystring.cpp
build/shortarray.o: src/shortarray.cpp src/shortarray.hpp
	$(GXXC) -o build/shortarray.o src/shortarray.cpp
build/shortarray2.o: src/shortarray2.cpp src/shortarray2.hpp
	$(GXXC) -o build/shortarray2.o src/shortarray2.cpp
build/shortarray3.o: src/shortarray3.cpp src/shortarray3.hpp
	$(GXXC) -o build/shortarray3.o src/shortarray3.cpp
build/workerdb.o: src/workerdb.cpp src/workerdb.hpp
	$(GXXC) -o build/workerdb.o src/workerdb.cpp
build/basefile.o: src/basefile.cpp src/basefile.hpp
	$(GXXC) -o build/basefile.o src/basefile.cpp
build/boolarray.o: src/boolarray.cpp src/boolarray.hpp
	$(GXXC) -o build/boolarray.o src/boolarray.cpp

# debug
build/debug.out: src/main.cpp $(BUILD_PARTS)
	$(GXXF) -o build/debug.out src/main.cpp $(BUILD_PARTS)
debug: build/debug.out
	gdb build/debug.out
run: build/debug.out
	build/debug.out
run-in: build/debug.out
	build/debug.out < testinput.txt