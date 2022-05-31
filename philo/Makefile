NAME = philo
cc = cc
flags = -Wall -Wextra -Werror
scrs = death.c \
			 eat.c \
			 init.c \
			 parse.c \
			 philo.c \
			 time.c \
			 utils.c

objs = $(scrs:.c=.o)

all : $(NAME)


$(NAME): $(objs)
	$(cc) $(flags) $(objs) -o $(NAME)

%.o : %.c philo.h
	$(cc) $(flags) -c $^ 

clean :
	@rm -rf $(objs)

fclean:clean
	@rm -rf $(NAME)

re:fclean all

.PHONY:all clean fclean re
