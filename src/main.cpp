# include <string>
# include <sstream>
# include "PmergeMe.hpp"

typedef std::string::iterator it;

static int	str_to_posint(std::string &s)
{
	int 	i;
	double	d;

	std::istringstream(s) >> i;
	std::istringstream(s) >> d;

	if (static_cast<int>(d) != i)
		throw std::out_of_range("out_of_range: " + s);
	if (i < 0)
		throw std::runtime_error("not_posint: " + s);
	for (it b = s.begin(), e = s.end(); b != e; b++)
	{
		if (!isdigit(*b))
			throw std::runtime_error("not_posint: " + s);
	}
	return (i);
}

void	parsingLoop(int argc, char *argv[])
{
	std::string	arg;
	int			arg_count = 0;
	int			value;

	while (++arg_count < argc)
	{
		arg = argv[arg_count];
		if (arg.empty())
			continue ;
		value = str_to_posint(arg);	
		PmergeMe::addNumber(value);
	}
	if (PmergeMe::values <= 1)
		throw std::runtime_error("not enought values to sort");
}

bool	parsing(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr <<
			"Error: wrong usage. (./PmergeMe posint sequence)" << std::endl;
		return (false);
	}
	try 
	{ 
		parsingLoop(argc, argv);
	}
	catch (std::exception &e) 
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (false);
	}
	PmergeMe::display("Before:");
	return (true);
}

int		main(int argc, char *argv[])
{
	if (!parsing(argc, argv))
		return (1);
	PmergeMe::processVector();
	PmergeMe::processDeque();

	PmergeMe::display("After : ");
	std::cout << "Time to process a range of " << PmergeMe::values 
	<< " elements with std::vector : " << PmergeMe::chrono_vector << " ns." << std::endl;
	std::cout << "Time to process a range of " << PmergeMe::values 
	<< " elements with std::deque : " << PmergeMe::chrono_deque << " ns." << std::endl;
	// std::cout << "Number of comparaison is : " << PmergeMe::comp_count << std::endl;

	return (0);
}