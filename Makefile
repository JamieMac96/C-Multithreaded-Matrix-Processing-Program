NAME=findvals
LIBS=
SOURCES=\
	findvals.c utils.c


CC=gcc
CFLAGS=-fopenmp

CXX=g++
CXXFLAGS=$(CFLAGS)

LD=gcc
LDFLAGS=


OBJECTS=${SOURCES:.c=.o}


.PHONY: clean
.SUFFIXES: .o .c .cc .cpp


all: program

clean:
	$(RM) $(OBJECTS)
	$(RM) $(NAME)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<


program: $(NAME)
$(NAME): $(OBJECTS)
	$(LD) $(CFLAGS) $(LIBS) -o $@ $^
