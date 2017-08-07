CXX=g++
CXXFLAGS=-Wall -g -std=c++11
LIBFLAGS=-lpthread -ldl -lhiredis
TARGET=xin
OBJS=$(patsubst ./%.cpp, ./%o, $(wildcard *.cpp))

.PHONY:$(TARGET)

$(TARGET):$(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $@ $(LIBFLAGS)
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LIBFLAGS)
clean:
	rm -rf *.o $(TARGET)

