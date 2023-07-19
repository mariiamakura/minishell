CC = cc
CFLAGS = -Werror -Wextra -Wall -pthread
SRC = ${wildcard *.c}
OBJ = ${SRC:.c=.o}

NAME = minishell
LIBFT = libft/libft.a
INCLUDES = -I libft/includes -I/usr/include -L/usr/local/lib -I/usr/local/include -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	make -s -C libft
	$(CC) $(CFLAGS) $(LIBFT) $(INCLUDES) -o $(NAME) $(OBJ)

clean:
	@-rm -f $(OBJ)

fclean: clean
	@-rm -f $(NAME)

re: fclean all
