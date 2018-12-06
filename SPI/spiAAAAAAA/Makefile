# Quick and dirty (does not handle changes in h-file)
ifndef TARGET
TARGET=target
endif

#IF Target is host set compiler and BUILD_DIR
ifeq (${TARGET},host)
CXX = g++
BUILD_DIR = host
endif

#IF Target is target set compiler and BUILD_DIR
ifeq (${TARGET},target)
CXX = arm-rpizw-g++
BUILD_DIR = target
endif

SRCS=SPI_RPI.cpp Fileaccess.cpp modes.cpp
OBJS=$(SRCS:.cpp=.o)
BASEPATH=/home/stud/apps/OSApi

# Determine whether this is a debug build or not
ifdef DEBUG
CXXFLAGS=-ggdb -O0
LIBPATH=$(BASEPATH)/lib/${BUILD_DIR}/debug
else
CXXFLAGS=-O2
LIBPATH=$(BASEPATH)/lib/${BUILD_DIR}/release
endif
# Setup the CFLAGS to ensure that the relevant warnings, includes and defines.
CXXFLAGS+=-Wall -D_REENTRANT -DOS_LINUX -I$(BASEPATH)/inc

#%.o : %cpp
#	g++ $(CXXFLAGS) -c -o $@ $^
# Then again, note how the flags are NOT part of the linking process
main: $(OBJS)
	${CXX} -o main $(OBJS)  -L$(LIBPATH) -lOSApi -lrt -lpthread

all: main

clean:$(OBJS)
	rm -f *.o main
