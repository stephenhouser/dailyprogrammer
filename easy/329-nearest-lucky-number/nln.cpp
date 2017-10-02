#include <iostream>
#include <string>
#include <cerrno>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <chrono>  // for high_resolution_clock

//using namespace std;

#define MAX_LUCKY 100000
#define HALF_LUCKY (MAX_LUCKY / 2 + 1)

void usage(const char * program_name) {
	std::cerr << program_name << " - find nearest lucky number." << std::endl;
	std::cerr << "Usage:" << program_name << " <number>" << std::endl;
}

bool verbose = 0;
std::vector<int> lucky_numbers;

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
	if (verbose) {
		std::cout << "Generating Lucky Numbers up to " << max_number << "...";
	}
	
	auto start = std::chrono::high_resolution_clock::now();

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
	
	auto finish = std::chrono::high_resolution_clock::now();
	if (verbose) {
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << " elapsed time: " << elapsed.count() << " s" << std::endl;
	}	

	lucky_numbers = numbers;
}

int main(int argc, char *argv[]){
	if (argc != 2) {
		std::cerr << "ERROR: No number specified" << std::endl << std::endl;
		usage(argv[0]);
		exit(2);
	}

	char *end;
	long n = std::strtol(argv[1], &end, 10);
	if (errno == ERANGE) {
		std::cerr << "ERROR: number out of range." << std::endl << std::endl;
		usage(argv[0]);		
	}

	if (n == -1) { // generate 100,000 numbers and print time
		verbose = 1;
		std::cout << "** Timing test..." << std::endl;
		generate_lucky_numbers(100000);
		return 0;		
	}

	generate_lucky_numbers(n*2);

	// std::cout << "Lucky_numbers: ";
	// for (auto n: lucky_numbers) {
	// 	std::cout << n << ' ';
	// } 
	// std::cout << std::endl;

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

	return 0;
}