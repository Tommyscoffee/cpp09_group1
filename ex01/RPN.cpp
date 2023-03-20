#include "RPN.hpp"

std::string trim(const std::string& string, const char* trimCharacterList = " \t\v\r\n")
{

	std::string result;
	// 左側からトリムする文字以外が見つかる位置を検索します。
	std::string::size_type left = string.find_first_not_of(trimCharacterList);
	if (left != std::string::npos)
	{
		// 左側からトリムする文字以外が見つかった場合は、同じように右側からも検索します。
		std::string::size_type right = string.find_last_not_of(trimCharacterList);
		// 戻り値を決定します。ここでは右側から検索しても、トリムする文字以外が必ず存在するので判定不要です。
		result = string.substr(left, right - left + 1);
	}

	return result;
}

bool calcValue(ssize_t result, ssize_t &value)
{
	if (result > INT_MAX || result < INT_MIN)
	{
		return (ERROR);
	}
	value = result;
	return (SUCCESS);
}

bool operateRPN(std::stack<ssize_t> &fomula_stack, char token)
{
	ssize_t left = 0;
	ssize_t right = 0;
	ssize_t value = 0;
	
	if (fomula_stack.size() < 2)
		return (ERROR);
	right = fomula_stack.top();
	fomula_stack.pop();
	left = fomula_stack.top();
	fomula_stack.pop();

	if  (token == '+')
	{
		if (calcValue(left + right, value) ==  ERROR)
			return (ERROR);
	}
	else if (token == '-')
	{
		if (calcValue(left - right, value) ==  ERROR)
			return (ERROR);
	}
	else if (token == '*')
	{
		if (calcValue(left * right, value) ==  ERROR)
			return (ERROR);
	}
	else if (token == '/')
	{
		if (calcValue(left / right, value) ==  ERROR)
			return (ERROR);
	}
	else
	{
		return (ERROR);
	}
	fomula_stack.push(value);
	return (SUCCESS);
}

bool tokenizeFomula(std::string fomula)
{
	size_t				i;
	std::stack<ssize_t>	fomula_stack;
	std::string			trimed_fomula;

	if (fomula.size() < 2)
	{
		std::cout << "Error: there must be more than 1 term." << std::endl;
		return (ERROR);
	}

	fomula = trim(fomula);
	for (i = 0; i < fomula.size(); i++)
	{
		if (fomula[i] == ' ')
			continue;
		else if  (isdigit(fomula[i]))
		{
			fomula_stack.push(fomula[i] - '0');
		}
		else if (operateRPN(fomula_stack, fomula[i]) == ERROR)
		{
			std::cout << "Error" << std::endl;
			return (ERROR);
		}
	}

	std::cout << fomula_stack.top() << std::endl;

	return (SUCCESS);

}