CC = cc
CFLAGS = -Werror -Wextra -Wall -g
THREADS = -fsanitize=thread -pthread

SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = src/lexer/quot_utils.c src/lexer/redirection_utils.c src/lexer/lexer.c src/lexer/redirection.c\
				src/lexer/variables_quotations.c src/lexer/heredoc.c src/lexer/var_utils.c src/lexer/add_path_utils.c\
				src/lexer/add_path.c src/signals.c src/parser/parse_utils.c src/parser/parse.c src/parser/split_sub.c\
				src/pipes/pipes_utils.c src/pipes/pipes.c src/buildins/ft_declare.c src/buildins/ft_echo.c\
				src/buildins/ft_export.c src/buildins/ft_cd.c src/buildins/ft_env.c src/buildins/ft_unset.c\
				src/buildins/bulitins_utils.c src/buildins/ft_export_utils.c src/buildins/ft_exit.c src/buildins/ft_pwd.c src/main.c
OBJ_SUBDIRS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(shell find $(SRC_DIR) -type d))
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

HEADER = -I ./include -I ./minishell.h/include

NAME = minishell
LIBFT_DIR = libft
LIBFT_A := $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ_FILES)
	@echo "Building $(NAME) application"
	@$(CC) $(CFLAGS) $(HEADER) -o $(NAME) $(OBJ_FILES) $(LIBFT_A) -lreadline -pthread
	@echo "BUILD SUCCESSFUL"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ./include/minishell.h | $(OBJ_SUBDIRS)
	@echo "Building C object $(notdir $@)"
	@$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<

$(OBJ_SUBDIRS):
	@mkdir -p $@

$(LIBFT_A):
	@cd $(LIBFT_DIR) && make all

#print src files
print_src:
	$(info SRC_FILES: $(SRC_FILES)) 

clean:
	@echo "Cleaning"
	@cd $(LIBFT_DIR) && make clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Fcleaning"
	@cd $(LIBFT_DIR) && make fclean
	@-rm -f $(NAME)

re: fclean all

