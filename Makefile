CC = cc
CFLAGS = -Werror -Wextra -Wall
THREADS = -fsanitize=thread -pthread

SRC_DIR = src
SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")
OBJ_DIR = build
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

HEADER = -I ./include -I ./minishell.h/include

NAME = minishell
LIBFT_DIR = libft
LIBFT_A := $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ_FILES)
	@echo "Building $(NAME) application"
	@$(CC) $(CFLAGS) $(HEADER) -o $(NAME) $(OBJ_FILES) $(LIBFT_A) -lreadline
	@echo "$(COLOUR_GREEN)BUILD SUCCESSFUL$(COLOUR_END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ./include/minishell.h | $(OBJ_DIR)
	@echo "$(COLOUR_GREEN)Building C object $(notdir $@)$(COLOUR_END)"
	@$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_A):
	@cd $(LIBFT_DIR) && make all

clean:
	@echo "Cleaning"
	@cd $(LIBFT_DIR) && make clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Fcleaning"
	@cd $(LIBFT_DIR) && make fclean
	@-rm -f $(NAME)

re: fclean all