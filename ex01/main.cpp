#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2 )
	{
		std::cout << "Error: invalid arguments." << std::endl;
		return (-1);
	}
	else
	{
		tokenizeFomula(std::string(argv[1]));
	}
	return (0);
}