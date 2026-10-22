CXX = g++
LIBS =
CXXFLAGS = -Wall -std=c++11
OBJECTS = main.o
HFILES = arraylist.hpp

ifeq ($(OS),Windows_NT)
    TARGET = main.exe
    RM = del /Q /F
else
    TARGET = main.out
    RM = rm -f
endif

all : $(TARGET)

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)

.PHONY : all clean run

run : $(TARGET)
	./$(TARGET)

clean :
	$(RM) $(TARGET) *.o core
