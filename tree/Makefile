CXX = g++
CXXFLAGS = -g -Wall -std=c++20

# Define the target names and their dependencies
all: driver

driver: driver.o filetree.o
	$(CXX) $(CXXFLAGS) -o driver driver.o filetree.o

# Define the dependencies for the object files
driver.o: driver.cc filetree.h
	$(CXX) $(CXXFLAGS) -c driver.cc -o driver.o

filetree.o: filetree.cc filetree.h
	$(CXX) $(CXXFLAGS) -c filetree.cc -o filetree.o

# Define a phony target for cleaning
clean:
	-rm -f driver driver.o filetree.o
