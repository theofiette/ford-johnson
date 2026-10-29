#pragma once

#include "PmergeMe.hpp"

template <typename container>
void	PmergeMe::_mergeInsertionSort(container &sequence, int depth)
{
	size_t	sequenceSize = sequence.size();
	size_t	groupSize = pow(2, depth);
	size_t	pairSize = groupSize * 2;
	
	// N = bloc
	// Comparing group of N elements, swapping when needed
	PmergeMe::_compareAndSwap(sequence, sequenceSize, groupSize, pairSize);
	
	// Exit condition
	if (sequenceSize < groupSize * 3)
		return ;

	// Recursive call
	PmergeMe::_mergeInsertionSort(sequence, depth + 1);

	// Insertion logic
	PmergeMe::_mergeAndInsertSmalls(sequence, sequenceSize, groupSize, pairSize);
}

template <typename container>
void	PmergeMe::_compareAndSwap(container &sequence, size_t sequenceSize, size_t groupSize, size_t pairSize)
{
	size_t i = groupSize - 1;
	typename container::iterator delim1, delim2;

	//While group of value can be paired
	while (i + groupSize < sequenceSize)
	{
		PmergeMe::comp_count++;
		if (sequence[i] > sequence[i + groupSize])
		{
			delim1 = sequence.begin() + i - (groupSize - 1);
			delim2 = delim1 + groupSize;
			std::swap_ranges(delim1, delim2, delim2);
		}
		i += pairSize;
	}
}

template <typename container>
void	PmergeMe::_mergeAndInsertSmalls(container &sequence, size_t sequenceSize, size_t groupSize, size_t pairSize)
{
	container	result;

	PmergeMe::_pushUppers(result, sequence, sequenceSize, groupSize, pairSize);
	PmergeMe::_insertSmalls(result, sequence, sequenceSize, groupSize, pairSize);
	PmergeMe::_pushRemainingValues(result, sequence, sequenceSize);
	sequence = result;
}

template <typename container>
void	PmergeMe::_pushUppers(
	container &result, const container &sequence, size_t sequenceSize, size_t groupSize, size_t pairSize)
{
	size_t	index = pairSize - (groupSize - 1);
	typename container::const_iterator	delim1, delim2;

	// while there is still an Upper group in sequence
	while (index + groupSize <= sequenceSize)
	{
		// insert the next upper group
		delim1 = sequence.begin() + index - 1;
		delim2 = delim1 + groupSize;
		result.insert(result.end(), delim1, delim2);
		index += pairSize;
	}
}

template <typename container>
void	PmergeMe::_insertSmalls(
	container &result, const container &sequence, size_t sequenceSize, size_t groupSize, size_t pairSize)
{
	typename container::const_iterator	delim1, delim2;
	size_t								jDelim;
	//!\ jIndex is the Nth groupe of small value, so lowest is 1 not 0
	size_t								jIndex;
	size_t								jCount = 2;
	size_t								jacobsthal = 1;
	size_t								insertDelim;
	bool								stopCheck = false;

	// insert first small with cost 0
	delim1 = sequence.begin();
	delim2 = delim1 + (groupSize);
	result.insert(result.begin(), delim1, delim2);

	size_t	numberOfSmallGroups = ((sequenceSize - groupSize) / pairSize) + 1;
	while (!stopCheck)
	{
		// recalculate insertion sequence and delim
		jDelim = jacobsthal;
		jacobsthal = _jacobsthal(jCount++);
		insertDelim = (jacobsthal + jDelim - 2);
		jIndex = jacobsthal;

		// checking if jacobsthal index is bigger than number of smalls in sequence
		if (jIndex > numberOfSmallGroups)
		{
			stopCheck = true;
			jIndex = numberOfSmallGroups;
		}

		while (jIndex > jDelim)
		{
			size_t	lookedUpIndex = (jIndex * pairSize) - groupSize - 1;
			size_t	lookedUpValue = sequence[lookedUpIndex];
			size_t	insertionIndex;
			size_t numGroups = result.size() / groupSize;
			if (insertDelim >= numGroups)
				insertionIndex = PmergeMe::_binarySearch(result, 0, numGroups, groupSize, lookedUpValue) * groupSize;
			else
				insertionIndex = PmergeMe::_binarySearch(result, 0, insertDelim, groupSize, lookedUpValue) * groupSize;
				
			delim2 = sequence.begin() + lookedUpIndex + 1;
			delim1 = delim2 - groupSize;
			
			result.insert(result.begin() + insertionIndex, delim1, delim2);
			jIndex--;
		}
	}
}
// binary insert with groups of value - [start, end]
template <typename container>
size_t	PmergeMe::_binarySearch(
	container &result, size_t start, size_t end, size_t groupSize, int value)
{
	if (start >= end)
	{
		if (end * groupSize == result.size())
			return (end);
		return (value > result[(start) * groupSize + groupSize - 1] ? start + 1 : start);
	}
	size_t	mid = (start + end) / 2;
	int		compValue = result[(mid + 1) * groupSize - 1];

	if (value == compValue)
		return (mid);
	
	if (value > compValue)
		return (PmergeMe::_binarySearch(result, mid + 1, end, groupSize, value));
	
	if (mid == 0)
		return (PmergeMe::_binarySearch(result, start, mid, groupSize, value));
	return (PmergeMe::_binarySearch(result, start, mid - 1, groupSize, value));
}

template <typename container>
void	PmergeMe::_pushRemainingValues(
	container &result, const container &sequence, size_t sequenceSize)
{
	size_t	pushIndex = result.size();
	while (pushIndex < sequenceSize)
		result.push_back(sequence[pushIndex++]);
}