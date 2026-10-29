# Ford-Johnson

[![C++](https://img.shields.io/badge/language-C++98-555?style=flat-square&logo=cplusplus)](https://en.cppreference.com/w/cpp)
![License](https://img.shields.io/badge/license-Educational-lightgrey?style=flat-square)

The Ford-Johnson merge-insertion sort in C++98, focusing on algorithms and on minimizing the number of comparisons.

Ford-Johnson (1959) is one of the sorting algorithms that use the fewest comparisons known. This implementation sorts the same sequence with `std::vector` and `std::deque` through one templated algorithm, and times both.

---

## Build & Run

### Requirements
- `g++` or `clang++` (C++98), `make`

> Note: Ford-Johnson has been tested on **Fedora Linux 44** and **Ubuntu 24.04**, with g++ 13, g++ 14 and clang++ 18.

### Compilation
`make`

### Run
`./PmergeMe <positive integers>`  
ex : `./PmergeMe 3 5 9 7 4`  
ex : ``./PmergeMe `shuf -i 1-100000 -n 3000 | tr '\n' ' '` ``

### Output

```
Before:   3, 5, 9, 7, 4
After :   3, 4, 5, 7, 9
Time to process a range of 5 elements with std::vector : ... ns.
Time to process a range of 5 elements with std::deque : ... ns.
```

- Values must be integers between 0 and `INT_MAX`; duplicates are allowed
- At least two values are required
- Only the first 5 values are printed, so long sequences stay readable

---

## Technical Overview

### The Algorithm

1. **Pair and compare** : elements are grouped in pairs, and each pair is ordered (one comparison per pair)
2. **Recurse** : the larger element of each pair is sorted recursively with the same algorithm
3. **Insert** : the smaller elements are inserted into the sorted sequence by binary search, in an order given by the **Jacobsthal numbers** (1, 3, 5, 11, 21, 43…). This order guarantees that each binary search runs on a range of 2^k − 1 elements, the size where a binary search wastes no comparison

### Comparison Count

Comparisons between elements were counted with an instrumented copy of the code (each binary-search step counts as one), on 200 random permutations per size, and compared with the theoretical worst case of Ford-Johnson, F(n) = Σ ⌈log₂(3k/4)⌉:

| n | This implementation (worst of 200) | Theoretical F(n) | `std::stable_sort` (average) | `std::sort` (average) |
| ---: | ---: | ---: | ---: | ---: |
| 21 | 66 | 66 | 79 | 109 |
| 100 | 534 | 534 | 600 | 794 |
| 1,000 | 8,641 | 8,641 | 9,767 | 11,945 |
| 3,000 | 30,531 | 30,546 | 32,870 | 41,550 |

- The count never exceeds F(n), on any of the 1,800 runs
- The result was checked against `std::sort` on 1,375 more sequences (sizes 1 to 3,000, random, many duplicates, reversed), for both containers

### Features

- One templated algorithm for any random-access container (`std::vector`, `std::deque`)
- Recursion works **in place on groups of 2^depth elements**: at each level, a "pair" is two neighbouring blocks, compared by their last element, and swapped as a whole with `std::swap_ranges`. No pair structures or index tables are allocated
- Binary insertion on blocks, with the search range bounded by the Jacobsthal sequence
- Timing of both containers with `clock_gettime`, including data insertion
- Input validation: negative numbers, non-digits and values above `INT_MAX` are rejected

### Architecture

- **Interface** : `inc/PmergeMe.hpp`
  - Containers, counters and timers (static class, no instance needed)
- **Algorithm** : `inc/PmergeMe.tpp`
  - `_mergeInsertionSort` : recursion on blocks of 2^depth elements
  - `_compareAndSwap` : orders each pair of blocks
  - `_insertSmalls`, `_binarySearch` : Jacobsthal-ordered binary insertion
- **Entry points and utilities** : `src/PmergeMe.cpp`
  - Sorting and timing for each container, Jacobsthal numbers, display
- **Parsing** : `src/main.cpp`
  - Argument validation and output

---

## More

### Educational Context

This project was developed as part of a programming curriculum (42 Paris, C++ Module 09) and aims to demonstrate:

- Implementation of a non-trivial algorithm from its description
- Generic programming with templates in C++98
- Comparison of standard containers (`std::vector`, `std::deque`)
- Measuring an algorithm against its theoretical bound

> Note: This project is for educational purposes, as a hands-on learning experience for algorithms and C++.

### AI Usage

This README was written with the help of Claude (Anthropic). The code itself was written without any LLM, as the project was part of a learning curriculum.
