CXX = g++-10

TARGET = exercise1

SRCS = main.cpp summation.cpp imageprocessing.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

INCDIRS = -L. -I../Stopwatch
CXXFLAGS = -Wall -fPIC -std=gnu++17 -pthread -fopenmp $(INCDIRS)

LDLIBS = -lfreeimageplus -ltbb
LDFLAGS = $(LDLIBS) 

.PHONY: all clean distclean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
