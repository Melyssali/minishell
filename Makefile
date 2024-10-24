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
DEPS = ./include/minishell.h
RM = rm -rf
# ---------- PATH  ----------
LIBFT_DIR = ./libs/Libft
PARSER_PATH = ./src/parser/
EXEC_PATH = ./src/exec/
BUILTIN_PATH = ./src/builtin/
UTILS_PATH = ./src/utils/

# ---------- SOURCES  ----------
OBJS = $(SRCS:.c=.o)
SRCS = 	main.c 	$(UTILS_PATH)utils.c $(BUILTIN_PATH)cd.c $(BUILTIN_PATH)echo.c $(BUILTIN_PATH)env.c   \
					$(BUILTIN_PATH)exit.c $(BUILTIN_PATH)export.c $(BUILTIN_PATH)pwd.c $(BUILTIN_PATH)unset.c  \

# ---------- REGLES MAKEFILE  ----------
all : $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(CFLAGS) $(RLFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation successful. Library: $(NAME)$(WHITE)"

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c -o $@ $< -I$(LIBFT_DIR)

debug: CFLAGS += -g

debug: re

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