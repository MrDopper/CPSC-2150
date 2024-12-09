CXX = g++

CXXFLAGS = -std=c++20 -Wall
#Name of th compile file
TARGET = skippedList.exe
SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.exe)

HEADERS = $(wildcard *.h)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.exe: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

remove:
	del /Q $(OBJS) $(TARGET)
