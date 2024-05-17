##
## EPITECH PROJECT, 2023
## make file
## File description:
## makes stuff
##

SRC	=	$(addprefix src/,\
			main.c	\
			corewar.c	\
			conv_coding_byte.c	\
			$(addprefix free/,\
				free_parameters.c	\
				free_arena.c	\
			)	\
			$(addprefix print/,\
				print_help.c	\
				print_arena.c	\
			)	\
			$(addprefix parameters/,\
				check_flag.c	\
				get_parameter.c	\
			)	\
			$(addprefix heads_utils/,\
				push_to_heads.c	\
			)	\
			$(addprefix init/,\
				init_champions_address.c	\
				init_parameter.c	\
				set_numbers.c	\
				init_arena.c	\
			)	\
			$(addprefix cycle/,\
				fight.c	\
				wait.c	\
			)	\
			$(addprefix instructions/,\
				live.c	\
				add.c	\
				aff.c	\
				and.c	\
				fork.c	\
				ldi.c	\
				lfork.c	\
				lld.c	\
				lldi.c	\
				load.c	\
				or.c	\
				st.c	\
				sti.c	\
				sub.c	\
				xor.c	\
				zjmp.c	\
			)	\
		)	\
		op/op.c	\

SRC_TEST	=

SRC_TO_TEST	=	$(filter-out src/main.c, $(SRC))

CPPFLAGS	=	-iquote./include

CFLAGS	+=	-Wall -Wextra

TEST_FLAGS	=	--coverage

LDFLAGS =	-L./lib

LDLIB	=	-lmy -lmini

TEST_LIB	=	-lcriterion

CC	?=	gcc

OBJ	=	$(SRC:.c=.o)

OBJ_TEST	=	$(SRC_TEST:.c=.o)

NAME	=	corewar

TEST_NAME	=	unit_tests

all:	build_lib $(NAME)

build_lib:
	make -C	lib/my
	make -C	lib/miniprintf

clean_lib:
	make clean -C lib/my
	make clean -C lib/miniprintf

fclean_lib:
	make fclean -C lib/my
	make fclean -C lib/miniprintf

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIB)

clean: clean_lib
	$(RM)  $(OBJ)

fclean:	clean fclean_lib tests_clean
	$(RM) $(NAME)

re:	fclean all

debug: CFLAGS += -ggdb3
debug: re

asan: CC = clang -fsanitize=address
asan: re

$(TEST_NAME):	build_lib $(OBJ_TEST)
	$(CC) -o $(TEST_NAME) $(CFLAGS) $(CPPFLAGS)	\
	$(OBJ_TEST) $(SRC_TO_TEST) $(LDFLAGS) $(LDLIB)	\
	$(TEST_FLAGS) $(TEST_LIB)

tests_run:	$(TEST_NAME)
	./$(TEST_NAME)

tests_clean:
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) coverage*
	$(RM) unit_tests

coverage:
	gcovr --html-details coverage && firefox coverage

.PHONY: all clean fclean re debug build_lib clean_lib fclean_lib \
	tests_run coverage tests_clean
