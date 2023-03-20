#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	std::map<std::string, double> map_bitcoin_csv;
	std::string				   s_input_file_line;

	if (validateArgs(argc))
		return (-1);
	std::ifstream input_file(argv[1]);
	if (!input_file)
	{
		std::cout << "Error: cannot open to file." << std::endl;
		return (-1);
	}
	if (validateFirstLine(input_file))
		return (-1);
	debug;
	if (storeBitcoinCsvToMap(map_bitcoin_csv))
	{
		return (ERROR);
	}
	debug;
	while (std::getline(input_file, s_input_file_line, '\n'))
	{
		size_t	pipe_pos;

		pipe_pos = s_input_file_line.find("|");
		if  (pipe_pos == std::string::npos)
		{
			std::cout << "Error: bad input => " << s_input_file_line << std::endl;
			continue;
		}
		else if (pipe_pos  == s_input_file_line.size() - 1)
		{
			std::cout << "Error: there is no string after '|'." << std::endl;
			continue;
		}
		else if (std::count(s_input_file_line.begin(), s_input_file_line.end(), '|') != 1)
		{
			std::cout << "Error: threre must be only one pipe." << std::endl;
			continue;
		}

		putLine(s_input_file_line, map_bitcoin_csv);
	}
	return (0);
}