#ifndef RPN_HPP
# define RPN_HPP
# define ERROR 1
# define SUCCESS 0

#include <iostream>
#include <stack>
#include <ctype.h>

bool operateRPN(std::stack<ssize_t> &fomula_stack, char token);
bool tokenizeFomula(std::string fomula);
std::string trim(const std::string& string, const char*);
#endif