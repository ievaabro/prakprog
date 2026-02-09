CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

Out.txt: main
	./main > Out.txt
#	./$< > $@

main : main.o approx.o
	$(CC) -o main main.o approx.o $(LDLIBS)

approx.o : approx.h approx.cc
	$(CXX) $(CXXFLAGS) -o approx.o -c approx.cc

main.o : main.cc approx.h
	$(CXX) $(CXXFLAGS) -o main.o -c main.cc

clean:
	$(RM) main main.o Out.txt *.o