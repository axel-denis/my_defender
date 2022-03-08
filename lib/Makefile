##
## EPITECH PROJECT, 2021
## myrunner
## File description:
## Makefile
##

SRC	=	my_get_nbr.c		\
		my_put_nbr.c		\
		my_putchar.c		\
		my_putstr.c			\
		my_strlen.c			\
		my_strcat.c			\
		my_nbr_to_str.c		\
		my_dec_to_base.c	\
		my_revstr.c			\
		dec_to_base.c		\
		my_str_isalpha.c	\
		my_strcmp.c			\
		my_strcpy.c			\
		my_split.c			\
		my_strdup.c			\

OBJ	=	$(SRC:.c=.o)

NAME	=	lib.a

$(NAME):	$(OBJ)
	ar	rc	$(NAME)	$(OBJ)

clean:
	rm	-f	$(OBJ)

fclean:	clean
	rm	-f	$(NAME)

re:	fclean	all
