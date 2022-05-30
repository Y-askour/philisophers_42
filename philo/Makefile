NAME = philo
cc = cc
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

%.o : %.c philo.h
	$(cc) $(flags) -c $^ 

clean :
	@rm -rf $(objs)
	@make clean -C libft
fclean:clean
	@rm -rf $(NAME)

re:fclean all

.PHONY:all clean fclean re
