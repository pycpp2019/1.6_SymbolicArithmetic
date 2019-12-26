SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,out/%.o,$(SRCS))
FLAGS=-std=c++14 -I.



.PHONY: all test run-test

all: test

test: out/test

out/test: out/test.o $(OBJS)
	g++ ${FLAGS} $^ -o $@

out/%.o: %.cpp *.h
	g++ ${FLAGS} -c $< -o $@

out/test.o: test/test.cpp test/*.hh *.h
	g++ ${FLAGS} -c $< -o $@

run-test: out/test
	./$<
