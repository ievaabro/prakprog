CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

Out.txt: main
	./main > Out.txt
#	./$< > $@

main : main.o 			#vec.o
	$(CC) -o main main.o $(LDLIBS)

# vec.o : vec.h vec.cc
# 	$(CXX) $(CXXFLAGS) -o vec.o -c vec.cc

main.o : main.cc vec.h
	$(CXX) $(CXXFLAGS) -o main.o -c main.cc

clean:
	$(RM) main main.o Out.txt *.o