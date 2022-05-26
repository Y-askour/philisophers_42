NAME = philo
cc = gcc
flags = -Wall -Wextra -Werror
scrs = death.c \
			 eat.c \
			 init.c \
			 parse.c \
			 philo.c \
			 time.c

objs = $(scrs:.c=.o)

all : $(NAME)

util:
	@make -C libft
	@mv libft/libft.a .

$(NAME): $(objs) util
	$(cc) $(flags) $(objs) libft.a -o $(NAME)



clean :
	@rm -rf $(objs)
fclean:clean
	@rm -rf $(NAME)

re:fclean all

.PHONY:all clean fclean re
