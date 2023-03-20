#ifndef BITCOINEXCHANGE_CPP
#define BITCOINEXCHANGE_CPP

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <deque>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <iomanip>

#define MAX_YEAR 2023
#define MIN_YEAR 2008
#define MAX_MONTH 12
#define MIN_MONTH 1
#define MIN_DAY 1
#define ERROR 1
#define SUCCESS 0
#define CSV_FILE "data.csv"
typedef std::map<std::string, float>::iterator map_itr_;
# define debug std::cout << "DEBUG [" << __FILE__ << ":" << __LINE__ << "] "
std::string trim(const std::string& string, const char* trimCharacterListç);
int calcMaxDay(int i_year,int i_month);
bool isOldDate(int i_year, int i_month, int i_day);
bool	parseDate(std::string s_date, std::string &s_year, std::string &s_month, std::string &s_day);
bool isBadInputValue(std::string s_value);
bool isInvalidValue(double d_value);
double findRate(std::map<std::string, double> map_bitcoin_csv, std::string s_date);
int countPrecision(std::string s_mult_res);
bool putLine(std::string input_file_line, std::map<std::string, double> map_bitcoin_csv);
bool validateArgs(int argc);
bool validateFirstLine(std::ifstream &input_file);
bool storeBitcoinCsvToMap(std::map<std::string, double> &map_bitcoin_csv);

#endif
