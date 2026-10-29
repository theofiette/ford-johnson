#include "PmergeMe.hpp"
// #include <cmath>

int					PmergeMe::values = 0;
int					PmergeMe::comp_count = 0;
std::vector<int>	PmergeMe::c_vector = std::vector<int>();
std::time_t			PmergeMe::chrono_vector;
std::deque<int>		PmergeMe::c_deque = std::deque<int>();
std::time_t			PmergeMe::chrono_deque;

/*
*	Entry point for container VECTOR.
*/
void PmergeMe::processVector()
{
	struct timespec	tm_start, tm_stop;

	clock_gettime(CLOCK_REALTIME, &tm_start);
	PmergeMe::_mergeInsertionSort(c_vector, 0);
	clock_gettime(CLOCK_REALTIME, &tm_stop);
	chrono_vector += (tm_stop.tv_nsec - tm_start.tv_nsec);
}

/*
*	Entry point for container DEQUE.
*/
void PmergeMe::processDeque()
{
	struct timespec	tm_start, tm_stop;

	clock_gettime(CLOCK_REALTIME, &tm_start);
	PmergeMe::_mergeInsertionSort(c_deque, 0);
	clock_gettime(CLOCK_REALTIME, &tm_stop);
	chrono_deque += (tm_stop.tv_nsec - tm_start.tv_nsec);
}

//  UTILS //////////////////////////////////////////////////////////////////////////////////////////////////////////////

int		PmergeMe::_jacobsthal(int count)
{
	return (((pow(2, count + 1) + pow(-1, count)) / 3));
}

void	PmergeMe::addNumber(int i)
{
	struct timespec	tm_start, tm_stop;

	{
		clock_gettime(CLOCK_REALTIME, &tm_start);
		c_vector.push_back(i);
		clock_gettime(CLOCK_REALTIME, &tm_stop);
		chrono_vector += (tm_stop.tv_nsec - tm_start.tv_nsec);
	}

	{
		clock_gettime(CLOCK_REALTIME, &tm_start);
		c_deque.push_back(i);
		clock_gettime(CLOCK_REALTIME, &tm_stop);
		chrono_deque += (tm_stop.tv_nsec - tm_start.tv_nsec);
	}

	values++;
}

void	PmergeMe::display(const std::string &prefixe)
{
	int	print_count = 0;

	std::cout << std::setw(10) << std::left << prefixe;
	for (v_it b = c_vector.begin(), e = c_vector.end(); b < e; b++)
	{
		std::cout << *b;
		print_count++;
		if (LOG && print_count >= LOG)
			break ;
		if (b != e - 1)
			std::cout << ", ";
	}
	std::cout << std::endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORS

PmergeMe::PmergeMe()
{
	std::cout
		<< "Default constructor called for class PmergeMe" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	(void) other;
	std::cout
		<< "Copy constructor called for class PmergeMe" << std::endl;
};

// ASSIGNEMENT OPERATOR

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	(void) other;
	std::cout
		<< "Copy assignment operator called for class PmergeMe" << std::endl;
	return (*this);
}

// DESTRUCTOR

PmergeMe::~PmergeMe()
{
	std::cout
		<< "Destructor called for class PmergeMe" << std::endl;
}