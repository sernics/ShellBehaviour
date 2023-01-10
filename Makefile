CC=g++
CXXFLAGS=-std=c++17 -g
PROGNAME=shell

OBJS=$(patsubst %.cc,%.o,$(wildcard *.cc))
all: ${OBJS}
	$(CC) $(CXXFLAGS) -o $(PROGNAME) ${OBJS}

clean:
	rm -rf *.o $(PROGNAME)
