# pragma once

# include <iostream>
# include <iomanip>
# include <vector>
# include <deque>
# include <ctime>
# include <cmath>
# include <algorithm>

# define LOG 5

typedef std::vector<int>::iterator	v_it;

class PmergeMe
{
private:

// Orthodox Canonical Form
				PmergeMe(); 						//Default constructor
				PmergeMe(const PmergeMe &other);	//Copy constructor
	virtual 	~PmergeMe();						//Destructor
	PmergeMe	&operator=(const PmergeMe &other); //Assignement operator

	template <typename container> static void	_mergeInsertionSort(container &seq, int depth);
	template <typename container> static void	_compareAndSwap(container &sequence, size_t sequenceSize, size_t groupSize, size_t pairSize);
	template <typename container> static void	_mergeAndInsertSmalls(container &sequence, size_t sequenceSize, size_t groupSize, size_t pairSize);
	template <typename container> static void	_pushUppers(container &result, const container &sequence, size_t sequenceSize, size_t groupSize, size_t pairSize);
	template <typename container> static void	_insertSmalls(container &result, const container &sequence, size_t sequenceSize, size_t groupSize, size_t pairSize);
	template <typename container> static size_t	_binarySearch(container &result, size_t start, size_t end, size_t groupSize, int value);
	template <typename container> static void	_pushRemainingValues(container &result, const container &sequence, size_t sequenceSize);
	
	static	int		_jacobsthal(int count);

public:

	static	int					values;
	static	int					comp_count;
	static	std::vector<int>	c_vector;
	static	std::deque<int>		c_deque;
	static	std::time_t			chrono_vector;
	static	std::time_t			chrono_deque;

	static	void	addNumber(int);
	static	void	display(const std::string &prefixe);
	static	void	processVector();
	static	void	processDeque();
};
		
# include "PmergeMe.tpp"
