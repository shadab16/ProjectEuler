CXX =		g++

CXXFLAGS =	-O3 -Wall -Wextra -pedantic -std=c++0x -Ilib

LIBS =		-Llib -lm -lgmp -leuler

VPATH =		src/

euler:		lib/euler.o
	ar rcs lib/libeuler.a lib/euler.o

1:		1.o
	$(CXX) -o problem$@ $@.o $(LIBS)

2:		2.o
	$(CXX) -o problem$@ $@.o $(LIBS)

3:		3.o
	$(CXX) -o problem$@ $@.o $(LIBS)

44:		44.o
	$(CXX) -o problem$@ $@.o $(LIBS)

54:		54.o
	$(CXX) -o problem$@ $@.o $(LIBS) -lpsim -lpoker-eval

58:		58.o
	$(CXX) -o problem$@ $@.o $(LIBS)

61:		61.o
	$(CXX) -o problem$@ $@.o $(LIBS)

66:		66.o
	$(CXX) -o problem$@ $@.o $(LIBS)

72:		72.o
	$(CXX) -o problem$@ $@.o $(LIBS)

73:		73.o
	$(CXX) -o problem$@ $@.o $(LIBS)

74:		74.o
	$(CXX) -o problem$@ $@.o $(LIBS)

76:		76.o
	$(CXX) -o problem$@ $@.o $(LIBS)

78:		78.o
	$(CXX) -o problem$@ $@.o $(LIBS)

120:		120.o
	$(CXX) -o problem$@ $@.o $(LIBS)

123:		123.o
	$(CXX) -o problem$@ $@.o $(LIBS)

124:		124.o
	$(CXX) -o problem$@ $@.o $(LIBS)

125:		125.o
	$(CXX) -o problem$@ $@.o $(LIBS)

127:		127.o
	$(CXX) -o problem$@ $@.o $(LIBS)

127b:		127b.o
	$(CXX) -o problem$@ $@.o $(LIBS)

187:		187.o
	$(CXX) -o problem$@ $@.o $(LIBS)

204:		204.o
	$(CXX) -o problem$@ $@.o $(LIBS)

207:		207.o
	$(CXX) -o problem$@ $@.o $(LIBS)

clean:
	$(RM) *.o problem*

