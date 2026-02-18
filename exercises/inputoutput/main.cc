#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>

int main (int argc, char* argv[]) {
	std::vector<double> numbers;

	for(int i=0;i<argc;++i){
		std::string arg=argv[i];
		if(arg=="-n" && i+1<argc)
			numbers.push_back(std::stod(argv[i+1]));
	}

	std::string infile="", outfile="";
	for(int i=0;i<argc;i++){
		std::string arg=argv[i];
		if(arg=="--input" && i+1 < argc) infile=argv[i+1];
		if(arg=="--output" && i+1 < argc) outfile=argv[i+1];
	}

    if(!infile.empty() && !outfile.empty()) {
        std::ifstream myinput(infile);
        std::ofstream myoutput(outfile);
        double x;
        if( myinput.is_open() && myoutput.is_open() ){
            myoutput << "numbers are from file input/output" << std::endl;
            while( myinput >> x ){
                myoutput << "      " << x << "    " << std::sin(x) << "        " << std::cos(x) <<std::endl;
                }
            }
        else{
            std::cerr << "Error opening files: " << infile << outfile << std::endl;
            return EXIT_FAILURE;
        }

        myinput.close();
        myoutput.close();
    }

    else if (!numbers.empty()) {
        std::cout << "numbers are from argv" << std::endl;
        std::cout << "number:    sin(number):    cos(number):" << std::endl; 
        for (auto n : numbers)
            std::cout << "      " << n << "    " << std::sin(n) << "        " << std::cos(n) <<std::endl;

    }

    else {
        std::cout << "numbers are from input stream" << std::endl;
        std::cout << "number:    sin(number):    cos(number):" << std::endl; 
        double x;
        while( std::cin >> x ){
            std::cout << "      " << x << "    " << std::sin(x) << "        " << std::cos(x) <<std::endl;        }
    }

exit(EXIT_SUCCESS);


}
