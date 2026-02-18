CXXFLAGS = -Wall -Werror -Wextra -std=c++23 -O
LDLIBS = -lm

all: Out.txt Out-file.txt

main: main.cc
	$(CXX) $(CXXFLAGS) main.cc -o main $(LDLIBS)

data.txt:
	echo 1 2 3 4 5 > $@

my_input_file.txt:
	echo 1 2 3 4 5 > $@

minusn.txt:
	@>$@
	@for i in `seq 5`; do echo "-n " $$i >> $@; done

Out.txt: main minusn.txt
	./main $$(cat minusn.txt) > $@

Out-file.txt: main my_input_file.txt
	./main --input my_input_file.txt --output Out-file.txt

clean:
	$(RM) main Out.txt Out-file.txt minusn.txt data.txt my_input_file.txt my_output_file.txt