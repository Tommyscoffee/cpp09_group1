NAME	= btc

SRCS	= *.cpp

OBJS		= $(SRCS:%.c=%.o)

CXX			= c++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -fsanitize=address

all		: $(NAME)

$(NAME)	: $(SRCS)
		$(CXX) $(CXXFLAGS) -o $@ $^

clean	:

fclean	: clean
	rm -f $(NAME)

re : fclean all

test :
	./$(NAME) "89 * 9 - 9 - 9 - 4 - 1 +"
	./$(NAME) "77 * 7 -"
	./$(NAME) "(1 + 1)"
.PHONY : all clean fclean re test