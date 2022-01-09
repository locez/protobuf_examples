.PHONY:all clean

all:
	mkdir -p build
	cmake -B build -S .
	cmake --build build
	cmake --install build

clean:
	rm ./build -rf
	rm ./bin -rf
