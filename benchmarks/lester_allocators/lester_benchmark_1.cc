
//#define DEBUG
// #define DEBUG_V1

#include <iostream>
#include <iomanip>
#include <memory>
#include <random>
#include <iterator>
#include <functional>
#include <ctime>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/wait.h>

// Changed : #include <vector>
// Changed : #include <string>

#include <bslstl_lesterstring.h>
#include <bslstl_lestervector.h>
#include <bslma_rawdeleterproctor.h>

// Changed : #include <unordered_set>

#include <bslma_allocator_database.h>

#include "lester_benchmark_common.h"

// Debugging
#include <typeinfo>
#include <assert.h>

using namespace BloombergLP;

// Global Variables
const size_t RANDOM_SIZE = 1000000;
const size_t RANDOM_DATA_POINTS = 1 << 16;
const size_t RANDOM_LENGTH_MIN = 33;
const size_t RANDOM_LENGTH_MAX = 1000;


alignas(long long) static char pool[1ull << 30];
char random_data[RANDOM_SIZE];
size_t random_positions[RANDOM_DATA_POINTS];
size_t random_lengths[RANDOM_DATA_POINTS];

// Setup Functions
void fill_random() {
	std::default_random_engine generator(1); // Consistent seed to get the same (pseudo) random distribution each time
	std::uniform_int_distribution<char> char_distribution(CHAR_MIN, CHAR_MAX);
	std::uniform_int_distribution<size_t> position_distribution(0, RANDOM_SIZE - RANDOM_LENGTH_MAX);
	std::uniform_int_distribution<size_t> length_distribution(RANDOM_LENGTH_MIN, RANDOM_LENGTH_MAX);


	for (size_t i = 0; i < RANDOM_SIZE; i++)
	{
		random_data[i] = char_distribution(generator);
	}
	for (size_t i = 0; i < RANDOM_DATA_POINTS; i++)
	{
		random_positions[i] = position_distribution(generator);
		random_lengths[i] = length_distribution(generator);
	}
}




// Convenience Typedefs
struct containers {
	typedef bsl::vector<int> DS1;
	typedef bsl::vector<bsl::string> DS2;
	// Changed : typedef std::unordered_set<int, hash<int>, equal<int>> DS3;
	// Changed : typedef std::unordered_set<std::string, hash<std::string>, equal<std::string>> DS4;
	typedef bsl::vector<DS1> DS5;
	typedef bsl::vector<DS2> DS6;
	// Changed : typedef std::vector<DS3> DS7;
	// Changed : typedef std::vector<DS4> DS8;
	// Changed : typedef std::unordered_set<DS1, hash<DS1>, equal<DS1>> DS9;
	// Changed : typedef std::unordered_set<DS2, hash<DS2>, equal<DS2>> DS10;
	// Changed : typedef std::unordered_set<DS3, hash<DS3>, equal<DS3>> DS11;
	// Changed : typedef std::unordered_set<DS4, hash<DS4>, equal<DS4>> DS12;
};





template<typename GLOBAL_CONT, typename MONO_CONT, typename MULTI_CONT, typename POLY_CONT, template<typename CONT> class PROCESSER>
static void run_base_allocations(unsigned long long iterations, size_t elements) {

	std::clock_t c_start;
	std::clock_t c_end;

#ifdef DEBUG_V1
	std::cout << std::endl << "AS2" << std::endl;
#endif
	// AS2 - Global Default with Virtual
	{
		int pid = fork();
		if (pid == 0) {
			PROCESSER<POLY_CONT> processer;
			c_start = std::clock();
			for (unsigned long long i = 0; i < iterations; i++) {
				BloombergLP::bslma::NewDeleteAllocator alloc;

				// Changed : POLY_CONT container(&alloc);
                POLY_CONT& container = *new(alloc) POLY_CONT();
                bslma::RawDeleterProctor<POLY_CONT, bslma::Allocator> dp82(&container, &alloc);

				container.reserve(elements);
				processer(&container, elements);
			}
			c_end = std::clock();
			std::cout << (c_end - c_start) * 1.0 / CLOCKS_PER_SEC << " ";
			exit(0);
		}
		else {
			wait(NULL);
		}
	}

#ifdef DEBUG_V1
	std::cout << std::endl << "AS5" << std::endl;
#endif

	// AS5 - Monotonic with Virtual
	{
		int pid = fork();
		if (pid == 0) {
			PROCESSER<POLY_CONT> processer;
			c_start = std::clock();
			for (unsigned long long i = 0; i < iterations; i++) {
				BloombergLP::bdlma::BufferedSequentialAllocator  alloc(pool, sizeof(pool));

				// Changed : POLY_CONT container(&alloc);
                POLY_CONT& container = *new(alloc) POLY_CONT();
                bslma::RawDeleterProctor<POLY_CONT, bslma::Allocator> dp112(&container, &alloc);

				container.reserve(elements);
				processer(&container, elements);
			}
			c_end = std::clock();
			std::cout << (c_end - c_start) * 1.0 / CLOCKS_PER_SEC << " ";
			exit(0);
		}
		else {
			wait(NULL);
		}
	}

#ifdef DEBUG_V1
	std::cout << std::endl << "AS6" << std::endl;
#endif

	// AS6 - Monotonic with Virtual and Wink
	{
		int pid = fork();
		if (pid == 0) {
			PROCESSER<POLY_CONT> processer;
			c_start = std::clock();
			for (unsigned long long i = 0; i < iterations; i++) {
				BloombergLP::bdlma::BufferedSequentialAllocator  alloc(pool, sizeof(pool));

				// Changed ; POLY_CONT* container = new(alloc) POLY_CONT(&alloc);
                POLY_CONT* container = new(alloc) POLY_CONT();

				container->reserve(elements);
				processer(container, elements);
			}
			c_end = std::clock();
			std::cout << (c_end - c_start) * 1.0 / CLOCKS_PER_SEC << " ";
			exit(0);
		}
		else {
			wait(NULL);
		}
	}

#ifdef DEBUG_V1
	std::cout << std::endl << "AS9" << std::endl;
#endif

	// AS9 - Multipool with Virtual
	{
		int pid = fork();
		if (pid == 0) {
			PROCESSER<POLY_CONT> processer;
			c_start = std::clock();
			for (unsigned long long i = 0; i < iterations; i++) {
				BloombergLP::bdlma::MultipoolAllocator alloc;

				// Changed : POLY_CONT container(&alloc);
                POLY_CONT& container = *new(alloc) POLY_CONT();
                bslma::RawDeleterProctor<POLY_CONT, bslma::Allocator> dp112(&container, &alloc);

				container.reserve(elements);
				processer(&container, elements);
			}
			c_end = std::clock();
			std::cout << (c_end - c_start) * 1.0 / CLOCKS_PER_SEC << " ";
			exit(0);
		}
		else {
			wait(NULL);
		}
	}

#ifdef DEBUG_V1
	std::cout << std::endl << "AS10" << std::endl;
#endif

	// AS10 - Multipool with Virtual and Wink
	{
		int pid = fork();
		if (pid == 0) {
			PROCESSER<POLY_CONT> processer;
			c_start = std::clock();
			for (unsigned long long i = 0; i < iterations; i++) {

				BloombergLP::bdlma::MultipoolAllocator alloc;

				// Changed : POLY_CONT* container = new(alloc) POLY_CONT(&alloc);
                POLY_CONT* container = new(alloc) POLY_CONT();

				container->reserve(elements);
				processer(container, elements);
			}
			c_end = std::clock();
			std::cout << (c_end - c_start) * 1.0 / CLOCKS_PER_SEC << " ";
			exit(0);
		}
		else {
			wait(NULL);
		}
	}

#ifdef DEBUG_V1
	std::cout << std::endl << "AS13" << std::endl;
#endif

	// AS13 - Multipool backed by Monotonic with Virtual
	{
		int pid = fork();
		if (pid == 0) {
			PROCESSER<POLY_CONT> processer;
			c_start = std::clock();
			for (unsigned long long i = 0; i < iterations; i++) {
				BloombergLP::bdlma::BufferedSequentialAllocator underlying_alloc(pool, sizeof(pool));
				BloombergLP::bdlma::MultipoolAllocator  alloc(&underlying_alloc);

				// Changed : POLY_CONT container(&alloc);
                POLY_CONT& container = *new(alloc) POLY_CONT();
                bslma::RawDeleterProctor<POLY_CONT, bslma::Allocator> dp112(&container, &alloc);

				container.reserve(elements);
				processer(&container, elements);
			}
			c_end = std::clock();
			std::cout << (c_end - c_start) * 1.0 / CLOCKS_PER_SEC << " ";
			exit(0);
		}
		else {
			wait(NULL);
		}
	}

#ifdef DEBUG_V1
	std::cout << std::endl << "AS14" << std::endl;
#endif

	// AS14 - Multipool backed by Monotonic with Virtual and Wink
	{
		int pid = fork();
		if (pid == 0) {
			PROCESSER<POLY_CONT> processer;
			c_start = std::clock();
			for (unsigned long long i = 0; i < iterations; i++) {
				BloombergLP::bdlma::BufferedSequentialAllocator underlying_alloc(pool, sizeof(pool));
				BloombergLP::bdlma::MultipoolAllocator  alloc(&underlying_alloc);

				// Changed : POLY_CONT* container = new(alloc) POLY_CONT(&alloc);
                POLY_CONT* container = new(alloc) POLY_CONT();

				container->reserve(elements);
				processer(container, elements);
			}
			c_end = std::clock();
			std::cout << (c_end - c_start) * 1.0 / CLOCKS_PER_SEC << " ";
			exit(0);
		}
		else {
			wait(NULL);
		}
	}

	std::cout << std::endl;
}

void run_base_loop(void(*func)(unsigned long long, size_t), std::string header) {
	std::cout << header << std::endl;
#ifdef DEBUG
	short max_element_exponent = 16;
	short max_element_iteration_product_exponent = 23;
#else
	short max_element_exponent = 16;
	short max_element_iteration_product_exponent = 27;
#endif // DEBUG


	for (unsigned long long elements = 1ull << 6; elements <= 1ull << max_element_exponent; elements <<= 1) {
		unsigned long long iterations = (1ull << max_element_iteration_product_exponent) / elements;
		std::cout << "Itr=" << iterations << " Elems=" << elements << " " << std::flush;
		func(iterations, elements);
	}
}

void run_nested_loop(void(*func)(unsigned long long, size_t), std::string header) {
	std::cout << header << std::endl;
#ifdef DEBUG
	short max_element_exponent = 16;
	short max_element_iteration_product_exponent = 23 - 7;
#else
	short max_element_exponent = 16;
	short max_element_iteration_product_exponent = 27 - 7;
#endif // DEBUG


	for (unsigned long long elements = 1ull << 6; elements <= 1ull << max_element_exponent; elements <<= 1) {
		unsigned long long iterations = (1ull << max_element_iteration_product_exponent) / elements;
		std::cout << "Itr=" << iterations << " Elems=" << elements << " " << std::flush;
		func(iterations, elements);
	}
}




// Functors to exercise the data structures
template<typename DS1>
struct process_DS1 {
	void operator() (DS1 *ds1, size_t elements) {
		escape(ds1);
		for (size_t i = 0; i < elements; i++) {
			ds1->emplace_back((int)i);
		}
		clobber();
	}
};

template<typename DS2>
struct process_DS2 {
	void operator() (DS2 *ds2, size_t elements) {
		escape(ds2);
		for (size_t i = 0; i < elements; i++) {

			// Changed : ds2->emplace_back(&random_data[random_positions[i]], random_lengths[i], ds2->get_allocator());
	        ds2->emplace_back(&random_data[random_positions[i]], random_lengths[i]);

		}
		clobber();
	}
};

template<typename DS5>
struct process_DS5 {
	void operator() (DS5 *ds5, size_t elements) {
		escape(ds5);
		for (size_t i = 0; i < elements; i++) {

			// Changed : ds5->emplace_back(ds5->get_allocator());
            ds5->emplace_back();

			ds5->back().reserve(1 << 7);
			for (size_t j = 0; j < (1 << 7); j++)
			{
				ds5->back().emplace_back((int)j);
			}
			
		}
		clobber();
	}
};

template<typename DS6>
struct process_DS6 {
	void operator() (DS6 *ds6, size_t elements) {
		escape(ds6);
		for (size_t i = 0; i < elements; i++) {

			// Changed : ds6->emplace_back(ds6->get_allocator());
            ds6->emplace_back();

			ds6->back().reserve(1 << 7);
			for (size_t j = 0; j < (1 << 7); j++)
			{
				// Changed : ds6->back().emplace_back(&random_data[random_positions[j]], random_lengths[j], ds6->get_allocator());
                ds6->back().emplace_back(&random_data[random_positions[j]], random_lengths[j]);
			}

		}
		clobber();
	}
};

int main(int argc, char *argv[]) {
	std::cout << "Started" << std::endl;
    
    std::cout << "Lester says hello!\n";

	std::cout << std::endl << "Generating random numbers" << std::endl;
	fill_random();

#if 0
	run_base_loop(&run_base_allocations<typename containers::DS1,
		typename containers::DS1,
		typename containers::DS1,
		typename containers::DS1,
		process_DS1>, "**DS1**");

	run_base_loop(&run_base_allocations<typename containers::DS2,
		typename containers::DS2,
		typename containers::DS2,
		typename containers::DS2,
		process_DS2>, "**DS2**");

	run_base_loop(&run_base_allocations<typename containers::DS5,
		typename containers::DS5,
		typename containers::DS5,
		typename containers::DS5,
		process_DS5>, "**DS5**");
#endif // 0

	run_base_loop(&run_base_allocations<typename containers::DS6,
		typename containers::DS6,
		typename containers::DS6,
		typename containers::DS6,
		process_DS6>, "**DS6**");


	std::cout << "Done" << std::endl;
}


