# -- COLORS -- #
BLACK=\033[0;30m# Black
RED=\033[0;31m# Red
GREEN=\033[0;32m# GREEN
YELLOW=\033[0;33m# YELLOW
BLUE=\033[0;34m# BLUE
PURPLE=\033[0;35m# PURPLE
CYAN=\033[0;36m# CYAN
WHITE=\033[0m# WHITE
# GREEN=\033[0;32m
# RED=\033[0;31m
# NC=\033[0m

# ---------- VARIABLES  ----------
NAME = minishell
CFLAGS = -Werror -Wextra -Wall
RLFLAGS = -L./libs/readline -lreadline -lncurses
DEPS = ./include/minishell.h
RM = rm -rf
# ---------- PATH  ----------
LIBFT_DIR = ./libs/libft
PARSING_PATH = ./src/parsing/
BUILTIN_PATH = ./src/builtin/
UTILS_PATH = ./src/utils/
EXEC_PATH = ./src/execution/


# ---------- SOURCES  ----------
OBJS = $(SRCS:.c=.o)
SRCS = 	main.c $(UTILS_PATH)builtin_utils.c $(UTILS_PATH)utils_tokenization.c\
		$(PARSING_PATH)tokenization.c $(PARSING_PATH)handle_interpreting.c $(UTILS_PATH)utils_tokenization2.c $(UTILS_PATH)utils_check_quotes.c $(PARSING_PATH)parser.c \
		$(UTILS_PATH)utils_parsing.c $(UTILS_PATH)execution_utils.c $(PARSING_PATH)hashtable_builtins.c $(PARSING_PATH)hashtable_operators.c \
		$(BUILTIN_PATH)cd.c $(BUILTIN_PATH)echo.c $(BUILTIN_PATH)env.c   \
		$(BUILTIN_PATH)exit.c $(BUILTIN_PATH)export.c $(BUILTIN_PATH)pwd.c $(BUILTIN_PATH)unset.c  \
		$(UTILS_PATH)utils_handle_error.c $(PARSING_PATH)handle_error.c $(PARSING_PATH)handle_heredoc.c \
		$(EXEC_PATH)exec.c $(EXEC_PATH)path.c $(EXEC_PATH)redirections.c $(UTILS_PATH)free_parsing.c

# ---------- REGLES MAKEFILE  ----------
all : $(RL) $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(CFLAGS) $(RLFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation successful. Library: $(NAME)$(WHITE)"

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c -o $@ $< -I$(LIBFT_DIR)

debug: CFLAGS += -g
debug: re

$(RL):
	@echo "$(YELLOW)Compiling readline...$(WHITE)"
	@cd libs/readline && ./configure
	@cd  libs/readline&& make
	@echo "$(GREEN)Readline compiled successfully$(WHITE)"

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
leaks: all
	leaks --atExit -- ./$(NAME)
val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
.PHONY: all clean fclean re
