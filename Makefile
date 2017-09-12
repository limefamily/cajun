all: test.out dump.out

test.out: test.cpp
	clang -o test.out --std=c++11 -lstdc++ test.cpp

dump.out: dump.cpp
	clang -o dump.out --std=c++11 -lstdc++ dump.cpp

clean:
	rm test.out dump.out
