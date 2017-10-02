/* nln - Lucky Number generator and locator
 * reddit /r/dailyprogrammer [2017-8-28] Challenge #329 [Easy] Nearest Lucky Numbers
 * 
 * 2017/10/01 Stephen Houser
 */
#include <iostream>	// cout
#include <string>	// general string stuff
#include <cerrno>	// integer range errors
#include <cstdlib>	
#include <vector>	// vectors
#include <numeric>
#include <chrono>  	// for high_resolution_clock
#include <unistd.h>	// getopt

bool verbose = false;			// show progress and debug information
bool report = false;			// show report of lucky numbers
int max_lucky = 0;				// default maximum number to consider
std::vector<int> lucky_numbers;	// vector of lucky numbers

void usage(const char * program_name = NULL) {
	const char *pname = program_name ? program_name : "nln";
	std::cout << "Lucky Number Generator" << std::endl;
	std::cout << std::endl;
	std::cout << "usage: " << pname << " [-h] [-v] [-r] [-m <max>] [<number>...]" << std::endl;
	std::cerr << "\t-h\tprint help and usage" << std::endl;
	std::cerr << "\t-v\tprint verbose messages" << std::endl;
	std::cerr << "\t-r\tprint report of lucky numbers generated" << std::endl;
	std::cerr << "\t-m <max>\tset maximim lucky number to generate" << std::endl;
	std::cerr << "\t<number>...\tfind lucky numbers closest to <number>" << std::endl;
	std::cerr << std::endl;
}

// remove every n-th item from list 
void eliminate_numbers(std::vector<int> &numbers, long step) {
	int eliminator = (numbers[step] == 1) ? 2 : numbers[step];
	//std::cout << "step=" << step << " elim=" << eliminator << std::endl;
	std::vector<int>::iterator it = numbers.begin();
	int n = 1;	// start counting at 1 not 0 to avoid deleting first elemnent
	while (it != numbers.end()) {
		if ((n++ % eliminator) == 0) {
			// remove if n is mod the eliminator value
			// reset iterator with result of erase as it's now changed
			it = numbers.erase(it);
		} else {
			// advance the iterator if we don't erase this element
			it++;
		}
	}
}

void generate_lucky_numbers(int max_number) {
	// Populate all numbers, then eliminate from first step
	// std::vector<int> numbers(max_number);
	// std::iota(numbers.begin(), numbers.end(), 1);
	// for (int i = 0; i < max_number; i++) {	
	// 	eliminate_numbers(numbers, i);
	// }

	// Populate only odd numbers numbers, then eliminate starting at second step
	std::vector<int> numbers(max_number / 2 + 1);
	std::generate(numbers.begin(), numbers.end(), [n = -1]() mutable -> int { return n+=2; });
	for (int i = 1; i < numbers.size(); i++) {	
		eliminate_numbers(numbers, i);
	}
	
	lucky_numbers = numbers;
}

int main(int argc, char *argv[]){
	int option_char;	// getopt returned option character
	char *end;			// iterator for end of char string
	std::vector<int> lucky_guesses;	// numbers to find closest lucky numbers for
	
	while ((option_char = getopt(argc, argv, "?hvrm:")) != EOF) {
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
			case 'm': {
				long m = std::strtol(optarg, &end, 10);
				if (errno == ERANGE) {
					std::cerr << "ERROR: number out of range." << std::endl << std::endl;
					usage(argv[0]);		
					return -1;
				}
				max_lucky = m;
				break;
			}
			case 'r': {
				report = true;
				break;
			}
		default:
				break;
		}
	}

	// Parse remaining command line arguments (numbers) for what numbers to find
	// The following traditional code (commented) is replaced with the new
	// C++ std 17 `transform` algorithm.
	//
	// for (int index = optind; index < argc; index++) {
	// 	long n = std::strtol(argv[index], &end, 10);
	// 	if (errno == ERANGE || n <= 0) {
	// 		std::cerr << "ERROR: number [" << argv[index] << "] out of range." << std::endl << std::endl;
	// 		usage(argv[0]);
	// 		return -1;
	// 	} else {
	// 		lucky_guesses.push_back(n);
	// 	}
	// }
	std::transform(&argv[optind], &argv[argc], std::back_inserter(lucky_guesses),
		[](char *s) -> int { // lambda that takes a char * and returns an int
			char *end; // end of char string marker
			long n = std::strtol(s, &end, 10);
			if (errno == ERANGE || n <= 0) {
				std::cerr << "ERROR: number [" << s << "] invalid or out of range." << std::endl;
				usage();
				exit(-1);
			}
	
			return (int)n;
		}
	); 

	if (lucky_guesses.size()) {
		// determine the maximum lucky number we will need to answer all the questions
		auto max_ln = std::max_element(lucky_guesses.begin(), lucky_guesses.end());
		max_lucky = std::max(max_lucky, (*max_ln * 2));
	}

	if (verbose || lucky_guesses.size() == 0) {
		 std::cout << "Generating Lucky Numbers up to " << max_lucky << "..." << std::flush;
	}

	auto start = std::chrono::high_resolution_clock::now();

	generate_lucky_numbers(max_lucky);

	auto finish = std::chrono::high_resolution_clock::now();	
	if (verbose || lucky_guesses.size() == 0) {
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << " elapsed time: " << elapsed.count() << "s" << std::endl;
	}

	if (optind < argc) {
		// for each number on the command line, find closest lucky number
		for (auto n : lucky_guesses) {
			if (verbose) {
				std::cout << "Looking for lucky number closest to " 
							<< n 
							<< "..." 
							<< std::endl;
			}
		
			auto it = lucky_numbers.begin();
			while (*it < n) {
				it++;
			}
		
			if (*it == n) {
				std::cout << n << " is a lucky number" << std::endl;
			} else {
				std::cout << *prev(it) << " < " << n << " < " << *it << std::endl;
			}
		}
	}

	if (report) {
		// print out report of the lucky numbers
		std::cout << "Lucky_numbers: ";
		for (auto n: lucky_numbers) {
			std::cout << n << ' ';
		} 
		std::cout << std::endl;
	}
}