# Makefile для проекту ComplexTask (C++)

CXX = g++
CXXFLAGS = -Wall -std=c++14

TARGET = ComplexTask
OBJS = ComplexTask.o ComplexTask_test.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

ComplexTask.o: ComplexTask.cpp ComplexTask.h
	$(CXX) $(CXXFLAGS) -c ComplexTask.cpp

ComplexTask_test.o: ComplexTask_test.cpp ComplexTask.h
	$(CXX) $(CXXFLAGS) -c ComplexTask_test.cpp

clean:
	rm -f *.o $(TARGET)