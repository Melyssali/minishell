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
RLFLAGS = -L./readline-master -lreadline -lncurses
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
		$(EXEC_PATH)exec.c $(EXEC_PATH)path.c $(EXEC_PATH)redirections.c

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

readline_script:
	@OS=$$(uname -s); \
	echo "OS detected: $$OS"; \
	case "$$OS" in \
	    Linux) \
	        if command -v apt-get &> /dev/null; then \
	            sudo apt-get update; \
	            sudo apt-get install -y build-essential libncurses5-dev libncursesw5-dev; \
	        elif command -v yum &> /dev/null; then \
	            sudo yum groupinstall -y "Development Tools"; \
	            sudo yum install -y ncurses-devel; \
	        elif command -v pacman &> /dev/null; then \
	            sudo pacman -S --needed base-devel ncurses; \
	        else \
	            echo "Unsupported Linux distribution. Please install build tools and ncurses manually."; \
	            exit 1; \
	        fi; \
	        ;; \
	    Darwin*) \
	        if command -v brew &> /dev/null; then \
	            brew install ncurses; \
	        else \
	            echo "Homebrew not found. Please install Homebrew and rerun the script."; \
	            exit 1; \
	        fi; \
	        ;; \
	    *) \
	        echo "Unsupported operating system: $$OS"; \
	        exit 1; \
	        ;; \
	esac

# readline_script:
# 	@if ls /usr/local/include | grep -q readline; then \
#     	echo "$(GREEN)readline est déjà installé"; \
# 	else \
#     	echo "Installation de readline et vérification des dépendances..."; \
#     	cd readline-master && ./configure --with-curses && make && sudo make install; \
#     	echo "$(GREEN)readline a été installé"; \
# 	fi
# 	@if ldconfig -p | grep -q libncurses; then \
#     	echo "$(GREEN)ncurses est déjà installé"; \
# 	else \
#     	echo "$(RED)ncurses manquant, installation en cours..."; \
#     	sudo apt-get install -y libncurses5-dev libncursesw5-dev; \
#     	echo "$(GREEN)ncurses a été installé"; \
# 	fi

# readline_script:
# 	@if ls /usr/lib/x86_64-linux-gnu | grep -q readline; then \
#     	echo "$(GREEN)readline est déjà installé$(NC)"; \
# 	else \
#     	echo "$(RED)readline n'est pas installé ou en conflit avec une autre version$(NC)"; \
#     	echo "Suppression des anciennes versions dans /usr/local/lib..."; \
#     	sudo rm -f /usr/local/lib/libreadline.so*; \
#     	sudo rm -rf /usr/local/include/readline; \
#     	echo "Installation de readline et ncurses depuis les paquets système..."; \
#     	sudo apt-get update && sudo apt-get install -y libreadline-dev libncurses5-dev libncursesw5-dev; \
#     	echo "$(GREEN)Installation de readline et ncurses terminée$(NC)"; \
# 	fi
# 	@echo "Compilation du projet avec readline et ncurses..."
# 	gcc -o minishell main.c -lreadline -lncurses

	
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

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
.PHONY: all clean fclean re