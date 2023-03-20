#include "PmergeMe.hpp"

bool isInvalidNum(char *str)
{
	int i = 0;

	if (str[0] == '0')
	{
		std::cout << "Error : Not a positive integer." << std::endl;
		return (ERROR);
	}
	while (str[i])
	{
		if (!isdigit(str[i]))
		{
			std::cout << "Error : Not a positive integer." << std::endl;
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

bool isDuplicate(std::deque<int> &deq, int num)
{
	std::deque<int>::iterator deq_top = deq.begin();
	std::deque<int>::iterator deq_end  = deq.end();

	if (std::find(deq_top, deq_end, num) != deq_end)
	{
		std::cout << "Error: there is duplicate. => " << num << std::endl;
		return (ERROR);
	}
	return (SUCCESS);
}

void putArr(std::string str, std::deque<int> vec)
{
	size_t i;

	i = 0;

	std::cout << str;

	if (vec.size() > 5)
	{
		for(;i < 4; i++)
		{
			std::cout << vec[i] << " ";
		}
		std::cout << "[...]" << std::endl;
	}
	else
	{
		for(;i < vec.size(); i++)
		{
			std::cout << vec[i] << " ";
		}
		std::cout << std::endl;
	}
	return ;
}
