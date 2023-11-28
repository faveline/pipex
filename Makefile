NAME = pipex

NAME_BONUS = pipex_bonus

SRCS = ft_creating_t_argv.c		\
	   ft_pipe_fork.c			\
	   ft_utils.c				\
	   main.c

SRCS_BONUS = ft_creating_t_argv.c		\
			 ft_pipe_fork.c				\
			 ft_utils.c					\
			 ft_utils_bonus.c			\
			 ft_utils_bonus2.c			\
			 ft_utils_bonus3.c			\
			 main.c

BONUS = $(addprefix bonus/, $(SRCS_BONUS))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
RM = rm -f
AR = ar rcs

all : $(NAME)

$(NAME):
	make -C libft/	
	$(CC) $(SRCS) libft/libft.a $(CFLAGS) -o $(NAME)

bonus :
	make -C libft/	
	$(CC) $(BONUS) libft/libft.a $(CFLAGS) -o $(NAME_BONUS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -I. -c $< -o ${<:.c=.o}

clean :
	make clean -C libft/

fclean :
	make fclean -C libft/
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re : fclean all

.PHONY:	all clean fclean re bonus
