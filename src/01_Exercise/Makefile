CXX = g++-10

TARGET = exercise1

SRCS = main.cpp summation.cpp imageprocessing.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

INCDIRS = -I../Stopwatch \
					-I../FreeImage
CXXFLAGS = -Wall -g -pthread -fopenmp $(INCDIRS)

LDLIBS = -lfreeimageplus -static
LDFLAGS = $(LDLIBS) 

.PHONY: all clean distclean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
