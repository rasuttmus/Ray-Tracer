# Select appropriate compiler.
#CPP=gcc
#CPP=g++
CPP=clang++
#CPPFLAGS=-O3 -fopenmp       
# Use this for gcc >= 4.2
#CPPFLAGS=-O3               # Use this for gcc <  4.2

ifdef DEBUG
CPPFLAGS=-g
endif

MKDIR = mkdir -p bin
LIBFOLD = -L"/usr/local/lib"
INCFOLD = -I"/usr/local/include"

BINFOLD = bin/

FRAMEWORKS = -std=c++11 -stdlib=libc++

BINNAME = main

FILES = $(wildcard src/*.cpp)

#default: all

all: compile

compile: $(FILES)
	$(CPP) $(CPPFLAGS) $(FILES) -o $(BINFOLD)$(BINNAME) $(LIBFOLD) $(INCFOLD) $(FRAMEWORKS)
.PHONY: all

run:
	./$(BINFOLD)$(BINNAME)
.PHONY: run

clean:
	rm -f *.o main