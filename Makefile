# THIS IS DIRECTLY FROM GPT
# i specifically recall makefiles not working correctly on my computer due to being windows
# and have been anticipating that this wont work as well
# so im going to assume this works :(
# will spend as much time as i can checking this, but more concerned with the MAIN file
# added a collaborations.txt to explain work done on this
# Compiler
#####
# This is mostly copied from lab08 since i think it should work the same - cant really test it tho on windows
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

# Executable Name
TARGET = matrix_operationsMAKE
# LEAVING THIS CALLED MATRIX_OPERATIONS AS A TESTING METHOD
# BASICALLY, i know that if i compiled base.cpp in vscode it will be base.exe, so by making this one different i can compare if its working right


# Source Files
SRCS = lab09.cpp
# this is the difference between lab8 and lab9 is the name of the file it is looking for
# everything else is the same

# Object Files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Compile the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(TARGET) $(OBJS)

# Run the program
run: $(TARGET)
	./$(TARGET)