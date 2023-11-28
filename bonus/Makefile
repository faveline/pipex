NAME = pipex

SRCS = ft_creating_t_argv.c		\
	   ft_pipe_fork.c			\
	   ft_utils.c				\
	   ft_utils_bonus.c			\
	   ft_utils_bonus2.c		\
	   ft_utils_bonus3.c		\
	   main.c

CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
RM = rm -f
AR = ar rcs

all : $(NAME)

$(NAME):
	make -C ../libft/	
	$(CC) $(SRCS) ../libft/libft.a $(CFLAGS) -o $(NAME)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -I. -c $< -o ${<:.c=.o}

clean :
	make clean -C ../libft/

fclean :
	make fclean -C ../libft/
	$(RM) $(NAME)
	$(RM) $(NAME_CHECKER)

re : fclean all

.PHONY:	all clean fclean re
