all:
	g++ -std=c++11 -O3 -I./include test.cc
clean:
	rm -f a.out
