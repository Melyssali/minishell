CFLAGS = -Werror -Wextra -Wall -g
DEPS = libft.h
NAME = libft.a
CC = gcc
AR = ar rcs
RM = rm -rf
SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
      ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strdup.c ft_strlen.c \
      ft_strlcat.c ft_strncmp.c ft_strnstr.c ft_tolower.c ft_toupper.c ft_strlcpy.c \
      ft_strchr.c ft_strrchr.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_strcmp.c\
      ft_putnbr_fd.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
      ft_putstr_fd.c ft_strjoin_no_free.c ft_putendl_fd.c get_next_line.c get_next_line_utils.c ft_atol.c 
PRINTF_DIR = ft_printf

# -- COLORS -- #
BLACK=\033[0;30m# Black
RED=\033[0;31m# Red
GREEN=\033[0;32m# GREEN
YELLOW=\033[0;33m# YELLOW
BLUE=\033[0;34m# BLUE
PURPLE=\033[0;35m# PURPLE
CYAN=\033[0;36m# CYAN
WHITE=\033[0m# WHITE

OBJ = $(SRC:.c=.o)

# règle par défaut qui génère la bibliothèque #
all: $(NAME)

# génère la bibliothèque en utilisant les fichiers objets. #
$(NAME): $(OBJ)
	@$(MAKE) -C $(PRINTF_DIR)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)Compilation successful. Library: $(NAME)$(WHITE)"

# création des fichiers objets à partir des fichiers source. #
%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $< -I$(PRINTF_DIR) $(CFLAGS)

# supprime les fichiers objets. #
clean:
	@$(MAKE) -C $(PRINTF_DIR) clean
	@$(RM) $(OBJ)
	@echo "$(CYAN)Object files cleaned successfully. Library: $(NAME)$(WHITE)"
	@echo "--------------------------------------------------------"

# supprime les fichiers objets et la bibliothèque. #
fclean: clean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(CYAN)Library cleaned successfully. Library: $(NAME)$(WHITE)"
	@echo "--------------------------------------------------------"

re: fclean all

# indique que 'all', 'clean', 'fclean' et 're' ne sont pas des fichiers. #
.PHONY: all clean fclean re
