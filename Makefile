# -- COLORS -- #
BLACK=\033[0;30m# Black
RED=\033[0;31m# Red
GREEN=\033[0;32m# GREEN
YELLOW=\033[0;33m# YELLOW
BLUE=\033[0;34m# BLUE
PURPLE=\033[0;35m# PURPLE
CYAN=\033[0;36m# CYAN
WHITE=\033[0m# WHITE

# ---------- VARIABLES  ----------
NAME = minishell
CFLAGS = -Werror -Wextra -Wall
RLFLAGS = -L./readline-master -lreadline -lncurses
DEPS = ./include/minishell.h
RM = rm -rf
# ---------- PATH  ----------
LIBFT_DIR = ./libs/Libft
PARSER_PATH = ./src/parser/
PARSING_PATH = ./src/parsing/
BUILTIN_PATH = ./src/parser/builtin/
UTILS_PATH = ./src/utils/
# -----------------------------
OBJS = $(SRCS:.c=.o)
SRCS = src/main.c $(UTILS_PATH)utils.c $(UTILS_PATH)utils_tokenization.c $(PARSER_PATH)builtin.c $(PARSER_PATH)check_type.c $(PARSER_PATH)exec.c \
		$(PARSING_PATH)tokenization.c $(UTILS_PATH)utils_tokenization2.c $(UTILS_PATH)utils_check_quotes.c $(PARSING_PATH)parser.c \
		$(UTILS_PATH)utils_parsing.c $(PARSING_PATH)hashtable_builtins.c
# ---------- REGLES MAKEFILE  ----------
all : readline_script $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(CFLAGS) $(RLFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation successful. Library: $(NAME)$(WHITE)"

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c -o $@ $< -I$(LIBFT_DIR)

debug: CFLAGS += -g
debug: re

# ---------- BASH SCRIPT  ----------
# guide to configure https://tiswww.case.edu/php/chet/readline/INSTALL
# creating a little script to install readline
# grep -q is quiet mode, don't show result in shell
readline_script :
	@if ls /usr/local/include | grep -q readline; then \
    	echo "$(GREEN)readline est installé"; \
	else \
    	cd readline-master  && ./configure && make && sudo make install; \
		echo "$(GREEN) readling a été installé"; \
	fi
	
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(CYAN)files cleaned successfully. Library: $(NAME)$(WHITE)"
	@echo "--------------------------------------------------------"

fclean: clean
	@$(RM) $(NAME) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(CYAN)Library cleaned successfully. Library: $(NAME)$(WHITE)"
	@echo "--------------------------------------------------------"

re: fclean all
.PHONY: all clean fclean re