CC = cc
CFLAGS = -Werror -Wextra -Wall -pthread
SRC = ${wildcard *.c}
OBJ = ${SRC:.c=.o}

NAME = minishell
LIBFT = libft/libft.a
INCLUDES = -I libft/includes -I/usr/include -L/usr/local/lib -I/usr/local/include -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	@cd libft && make all
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(INCLUDES)

clean:
	@cd libft && make clean
	@-rm -f $(OBJ)

fclean: clean
	@cd libft && make fclean
	@-rm -f $(NAME)

re: fclean all
