# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++20 -Wall

# Target Executable
TARGET = testProgram

# Automatically find all .cpp files in the directory
SRCS = $(wildcard *.cpp)

# Generate object files for each .cpp file
OBJS = $(SRCS:.cpp=.o)

# Automatically find all .h files in the directory
HEADERS = $(wildcard *.h)

# Determine platform-specific cleanup command
ifeq ($(OS),Windows_NT)
    RM = del /F /Q
    EXE = $(TARGET).exe
else
    RM = rm -f
    EXE = $(TARGET)
endif

# Build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS)

# Compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Clean up object files and the executable
remove:
	$(RM) $(OBJS) $(EXE)
