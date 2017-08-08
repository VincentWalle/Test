CXX=g++
CXXFLAGS=-Wall -g -std=c++11
LIBFLAGS=-lpthread -ldl -lhiredis -L/user/local/lib
TARGET=xin
OBJS=$(patsubst ./%.cpp, ./%o, $(wildcard *.cpp))

$(TARGET):$(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $@ $(LIBFLAGS)
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LIBFLAGS)

.PHONY:clean
clean:
	rm -rf *.o $(TARGET)

