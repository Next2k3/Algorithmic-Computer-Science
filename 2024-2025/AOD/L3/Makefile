CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

EXEC_DIKSTRA = Dijkstra
EXEC_DIAL = Dial
EXEC_RADIX = RadixHeap

OBJS_GRAPH = Graph.o
OBJS_DIKSTRA = Dijkstra.o $(OBJS_GRAPH)
OBJS_DIAL = Dial.o $(OBJS_GRAPH)
OBJS_RADIX = RadixHeap.o $(OBJS_GRAPH)

all: $(EXEC_DIKSTRA) $(EXEC_DIAL) $(EXEC_RADIX)

$(EXEC_DIKSTRA): $(OBJS_DIKSTRA)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_DIKSTRA)

$(EXEC_DIAL): $(OBJS_DIAL)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_DIAL)

$(EXEC_RADIX): $(OBJS_RADIX)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_RADIX)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC_DIKSTRA) $(EXEC_DIAL) $(EXEC_RADIX)

.PHONY: all clean
