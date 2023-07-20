CC = cc
CFLAGS = -Werror -Wextra -Wall
THREADS = -fsanitize=thread -pthread

SRC_DIR = src
SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")
OBJ_DIR = build
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

HEADER = -I ./include -I ./minishell.h/include

NAME = minishell
LIBFT_DIR = libft/libft.a
LIBFT	:= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): libft $(OBJ_FILES)
	@echo "Building $(NAME) application"
	@$(CC) $(CFLAGS) $(HEADER) -o $(NAME) $(OBJ_FILES)
	@echo "$(COLOUR_GREEN)BUILD SUCCESSFUL$(COLOUR_END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ./include/minishell.h | $(OBJ_DIR)
	@echo "$(COLOUR_GREEN)Building C object $(notdir $@)$(COLOUR_END)"
	@$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

libft:
	@echo "Building libft library"
	@cd libft && make all

clean:
	@echo "Cleaning"
	@cd libft && make clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Fcleaning"
	@cd libft && make fclean
	@-rm -f $(NAME)

re: fclean all
