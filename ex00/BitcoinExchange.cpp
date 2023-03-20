#include "BitcoinExchange.hpp"

std::string trim(const std::string& string, const char* trimCharacterList = " \t\v\r\n")
{

	std::string result;
	std::string::size_type left = string.find_first_not_of(trimCharacterList);
	if (left != std::string::npos)
	{
		std::string::size_type right = string.find_last_not_of(trimCharacterList);
		result = string.substr(left, right - left + 1);
	}
	return (result);
}

int calcMaxDay(int i_year,int i_month)
{
	if (i_year % 4 == 0 && i_month ==  2)//うるう年
		return (29);
	if ((i_month <= 7 && i_month % 2 == 1) ||(i_month >= 8 && i_month % 2 == 0))//３０か３１かを判定
		return (31);
	else if (i_month == 2)
		return (28);
	else
		return (30);

	return (0);
}

bool isOldDate(int i_year, int i_month, int i_day)
{
	if (i_year <= 2009 && i_month <= 1 && i_day <= 1)
	{
		std::cout << "Error: date is so old." << std::endl;
		return (ERROR);
	}
	else if (i_year < 2009)
	{
		std::cout << "Error: date is so old." << std::endl;
		return (ERROR);
	}
	return (SUCCESS);
}

bool	parseDate(std::string s_date, std::string &s_year, std::string &s_month, std::string &s_day)
{
	int i_year;
	int i_month;
	int i_day;

	if (std::count(s_date.begin(), s_date.end(), '-') != 2)
	{
		std::cout << "Error: YMD format is wrong." << std::endl;
		return (ERROR);
	}
	s_year = trim(std::string(strtok(const_cast<char*>(s_date.c_str()), "-")));
	if (s_year == "")
		return (ERROR);

	if (s_year.size() != 4 )
	{
		std::cout << "Error: invalid year. => " << s_year << std::endl;
		return (ERROR);
	}
	else
		i_year = std::stoi(s_year);
	s_month = trim(std::string(strtok(NULL, "-")));
	if (s_month == "")
		return (ERROR);

	if (s_month.size() != 2 || std::stoi(s_month) > MAX_MONTH || std::stoi(s_month) < MIN_MONTH)
	{
		std::cout << "Error: invalid month. => " << s_month << std::endl;
		return (ERROR);
	}
	else
		i_month = std::stoi(s_month);
	s_day = trim(std::string(strtok(NULL, "-")));
	if (s_day == "")
		return (ERROR);

	if (s_day.size() != 2 || std::stoi(s_day) > calcMaxDay(i_year, i_month) || std::stoi(s_day) < MIN_DAY)
	{
		std::cout << "Error: invalid day. => " << s_day << std::endl;
		return (ERROR);
	}
	else
		i_day = std::stoi(s_day);
	if (isOldDate(i_year, i_month, i_day))
	{
		return (ERROR);
	}
	return (SUCCESS);
}

bool isBadInputValue(std::string s_value)
{
	if (s_value == "")
		return (1);

	size_t itr = 0;
	if (s_value[itr] == '-')
	{
		std::cout << "Error: not a positive number." << std::endl;
		return (ERROR);
	}
	for(size_t itr = 0; itr < s_value.size(); itr++)
	{
		if (isdigit(s_value[itr]) == 0 && s_value[itr] !=  '.')
		{
			std::cout  << "Error: bad input => " << s_value << std::endl;
			return (ERROR);
		}

	}
	return (0);
}

bool isInvalidValue(double d_value)
{
	if (d_value == 0)
	{
		std::cout << "Error: value is not a double or a positive integer between 0 and 1000. " << std::endl;
		return (ERROR);
	}
	else if ( d_value < 0)
	{
		std::cout << "Error: not a positive number. " << std::endl;
		return (ERROR);
	}
	else if (d_value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return (ERROR);
	}
	else if (strtok(NULL, "|") != NULL)
	{
		std::cout << "Error: there are more than one pipe." << std::endl;
		return (ERROR);
	}
	return (0);
}

double findRate(std::map<std::string, double> map_bitcoin_csv, std::string s_date)
{
	bool is_just_match = false;
	std::map<std::string, double>::iterator rate_itr = map_bitcoin_csv.find(s_date);
	if (rate_itr != map_bitcoin_csv.end())//find()で見つかった
		is_just_match = true;
	else
		rate_itr = map_bitcoin_csv.lower_bound(s_date);//見つからなかったので直近を検索

	if (is_just_match == false && rate_itr != map_bitcoin_csv.begin())
		--rate_itr;
	//文字列比較で最古のデータより前を参照しようとしたら
	return (rate_itr->second);
}

int countPrecision(std::string s_mult_res)
{
	int count = 0;
	for (int i = s_mult_res.size() - 1; i >= 0 && s_mult_res[i] == '0' ; i--)
	{
		count++;
	}
	return (count);
}

bool putLine(std::string input_file_line, std::map<std::string, double> map_bitcoin_csv)
{
	double 		d_value;
	double		d_rate;
	double		d_mult_res;
	std::string s_date;
	std::string s_value;
	std::string s_year;
	std::string s_month;
	std::string s_day;
	std::string s_mult_res;

	s_date = trim(std::string(strtok(const_cast<char*>(input_file_line.c_str()), "|")));
	s_value = trim(std::string(trim(std::string(strtok(NULL, "|")))));//連続して保持しないといけない

	if (parseDate(s_date, s_year, s_month, s_day))
	{
		return (ERROR);
	}
	if (isBadInputValue(s_value))
	{
		return (ERROR);
	}
	else
	{
		d_value = std::stof(s_value);
		if (isInvalidValue(d_value))
			return (ERROR);
	}
	d_rate = findRate(map_bitcoin_csv, s_date);//3はcsvファイルで検索した日時のレートの代わりに書いています。
	if (d_rate < 0)
		return (ERROR);
	int dot_pos = 2;
	d_mult_res = d_rate * d_value;
	s_mult_res = std::to_string(d_mult_res);
	dot_pos = 6 - countPrecision(s_mult_res);//doubleは小数点以下が6桁だから
	std::cout << std::fixed << std::setprecision(dot_pos) << s_year << "-" << s_month << "-" << s_day << " => " << d_value << " = " << d_mult_res << std::endl;
	return (SUCCESS);
}

bool validateArgs(int argc)
{
	if (argc == 1)
	{
		std::cout << "Error: need input.txt file\n";
		return (ERROR);
	}
	if (argc != 2)
	{
		std::cout <<"Error: num of arguments is invalid\n";
		return (ERROR);
	}
	return (SUCCESS);
}


bool validateFirstLine(std::ifstream &input_file)
{
	std::string s_input_file_line;

	std::getline(input_file, s_input_file_line, '\n');

	if (s_input_file_line != "date | value")
	{
		std::cout << "Error: file's first line is not 'date | value'." << std::endl;
		return (ERROR);
	}
	return (SUCCESS);
}

bool storeBitcoinCsvToMap(std::map<std::string, double> &map_bitcoin_csv)
{
    std::ifstream ifs(CSV_FILE);
    std::string s_rate_raw;
    std::string s_date;
	std::string s_value;
    size_t i = 0;
    double d_rate;

	std::getline(ifs, s_rate_raw, '\n');
	if (s_rate_raw == "")
		return (ERROR);
    while (std::getline(ifs, s_rate_raw, '\n'))
    {
        s_date = "";
        s_date = std::string(strtok(const_cast<char*>(s_rate_raw.c_str()), ","));
		if (s_date == "")
		{
			std::cerr << "Error: csv file is not valid." << std::endl;
			return (ERROR);
		}
        s_value = std::string(strtok(NULL, ","));
        if (s_value == "") {
            std::cerr << "Error: csv file is not valid." << std::endl;
			return (ERROR);
        }

        d_rate = atof(s_value.c_str());
        map_bitcoin_csv[s_date] = d_rate;
		i++;
	}
    return (0);
}