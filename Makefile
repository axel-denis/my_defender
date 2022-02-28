##
## EPITECH PROJECT, 2021
## My_Defender
## File description:
## Makefile
##

MAIN		=	src/main.c \
				src/button_setup.c \
				src/button_utils.c \
				src/csfml_utils.c \
				src/mouse_manager.c \

SRC			=		\

MAINOBJ		=	$(MAIN:.c=.o)
OBJ			=	$(SRC:.c=.o)

NAME		=	my_defender

LIB			= 	-L. ./lib/lib.a \
				-lcsfml-graphics \
				-lcsfml-system \
				-lcsfml-audio \
				-lcsfml-window \


CPPFLAGS	+=	-I includes/
CFLAGS		+=	-Wall -Wextra -g3 #-ggdb3

$(NAME):		$(MAINOBJ) $(OBJ)
				make -C lib/
				gcc -o $(NAME) $(MAINOBJ) $(OBJ) $(CFLAGS) $(LIB)

all:			$(NAME)

clean:
				rm -f $(OBJ) $(MAINOBJ)
				rm -f criterion_test

fclean: 		clean
				rm -f $(NAME)

re: 			fclean all

tests_run:
				make -C lib/
				gcc -o criterion_test tests/tests.c $(TESTS) --coverage \
				-lcriterion -L. ./lib/lib.a
				./criterion_test

.PHONY	=		all clean fclean re tests_run
