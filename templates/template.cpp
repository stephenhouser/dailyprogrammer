/* template - Template code for C++17 Program
 * 
 * 2017/10/01 Stephen Houser
 */
#include <iostream>	// cout
#include <string>	// general string stuff
#include <cerrno>	// integer range errors
#include <cstdlib>	
#include <vector>	// vectors
#include <numeric>
#include <unistd.h>	// getopt

bool verbose = false;			// show progress and debug information
const char *program_name = "template";

void usage(const char * p_name = NULL) {
	const char *l_name = p_name ? p_name : program_name;
	std::cout << "Template Program" << std::endl;
	std::cout << std::endl;
	std::cout << "usage: " << l_name << " [-h] [-v] >] [<argument>...]" << std::endl;
	std::cerr << "\t-h\tprint help and usage" << std::endl;
	std::cerr << "\t-v\tprint verbose messages" << std::endl;
	std::cerr << "\t<argument>...\tstrings to print out..." << std::endl;
	std::cerr << std::endl;
}

int main(int argc, char *argv[]){
	int option_char;	// getopt returned option character
	std::vector<std::string> arguments;	// arguments to print out
	
	while ((option_char = getopt(argc, argv, "?hv")) != EOF) {
		switch(option_char) {
			case '?':
			case 'h': {
				usage();
				return 0;
			}
			case 'v': {
				verbose = true;
				break;
			}
		default:
				break;
		}
	}

	// Parse remaining command line arguments (numbers) for what numbers to find
	std::transform(&argv[optind], &argv[argc], std::back_inserter(arguments),
		// lambda that takes a char * and returns std::string
		[](char *s) -> std::string { 
			return std::string(s);
		}
	); 

	if (verbose) {
		std::cout << "There were " << arguments.size() << " arguments passed." << std::endl;
	}

	if (arguments.size() == 0) {
		usage();
	} else {
		for (auto n : arguments) {
			if (verbose) {
				std::cout << "[";
			}
			std::cout << n;
			if (verbose) {
				std::cout << "]";
			}
			std::cout << std::endl;		
		}
	}
}