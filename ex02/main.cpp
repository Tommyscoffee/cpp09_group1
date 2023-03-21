#include <iostream>
#include <deque>
#include <cstdlib>
#include "PmergeMe.hpp"

int main(int argc, char* argv[])
{
    std::deque<int> deq;
	std::vector<int> vec;
    std::clock_t s, e;
	int value;
	double vector_time;
	double deque_time;
	if (argc <= 2)
	{
		std::cout << "Error : we need positive int as arguments." << std::endl;
		return (ERROR);
	}

    for (int i = 1; i < argc; i++) {
		if (isInvalidNum(argv[i]))
			return (ERROR);
		else if (isDuplicate(deq, std::stoi(argv[i])))
			return (ERROR);
		value = std::stoi(argv[i]);
		deq.push_back(value);
		vec.push_back(value);
	}

	putArr("Before : ", deq);
	s = std::clock();
    mergeInsertionSort(deq, 0, deq.size() - 1);
    e = std::clock();
	deque_time = (double)(e - s) / CLOCKS_PER_SEC * ( 1000000 );
	putArr("After : ", deq);

	s = std::clock();
	mergeInsertionSort(vec, 0, vec.size() - 1);
	e = std::clock();
	vector_time = (double)(e - s) / CLOCKS_PER_SEC * ( 1000000 ) ;

	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << deque_time << " us" << std::endl;
	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << vector_time << " us" << std::endl;
	// if (isSorted(deq) == ERROR)
	// 	return (ERROR);
	// if (isSorted(vec) == ERROR)
	// 	return (ERROR);
    return 0;
}

