CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

Out.txt: main
	./main > Out.txt
#	./$< > $@

main : main.o sfuns.o
	$(CC) -o main main.o sfuns.o $(LDLIBS)

sfuns.o : sfuns.h sfuns.cc
	$(CXX) $(CXXFLAGS) -o sfuns.o -c sfuns.cc
main.o : sfuns.h main.cc
	$(CXX) $(CXXFLAGS) -o main.o -c main.cc

clean:
	$(RM) main main.o Out.txt *.o