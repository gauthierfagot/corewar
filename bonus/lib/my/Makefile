##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC     =	my_strlen.c	\
			my_strcmp.c	\
			my_puterr.c	\
			my_strcpy.c	\
			my_strdup.c	\
			my_compute_power_rec.c	\
			format_line.c	\
			my_arraylen.c	\
			is_number.c	\
			str_to_int.c	\
			is_alpha.c	\
			free_array.c	\
			get_buffer.c	\

OBJ     =	$(SRC:.c=.o)

NAME    =	libmy.a

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-I./include

all:    $(NAME)

$(NAME):	$(OBJ)
	ar rc -o $(NAME) $(OBJ)
	cp $(NAME) ..
	cp include/lib.h ../../include/libmy.h

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)
	$(RM) ../../include/lib.h

re:     fclean all

.PHONY: all clean fclean re
