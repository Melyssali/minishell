CFLAGS= -Werror -Wextra -Wall -g
DEPS = ft_printf.h
NAME = libftprintf.a
AR	= ar -rcs
RM	= rm -rf
OBJ = ft_check_identifier.o ft_count_itoa.o ft_count_putchar.o ft_count_putstr.o ft_count_utoa.o ft_printf.o ft_putnbr.o  ft_strdup.o ft_strlen.o  

all:
	@$(MAKE) $(NAME)

$(NAME):  $(OBJ)
		@$(AR) $(NAME) $(OBJ)

%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
