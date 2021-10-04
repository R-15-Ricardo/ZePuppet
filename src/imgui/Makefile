SRCS := $(wildcard *.cpp)

OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(OBJS)

%.o: %.cpp
	g++  -c $<

clear:
	rm -rf  *.o
	
.PHONY: all clean
