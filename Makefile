##
## EPITECH PROJECT, 2021
## My_Defender
## File description:
## Makefile
##

MAIN		=	src/my_defender.c			\

SRC			=	src/ui.c 					\
				src/range.c					\
				src/howto.c					\
				src/enemy.c					\
				src/events.c				\
				src/upgrade.c				\
				src/options.c				\
				src/turrets.c				\
				src/bullets.c				\
				src/lose_menu.c				\
				src/ui_create.c 			\
				src/game_core.c				\
				src/main_menu.c				\
				src/ui_display.c 			\
				src/pause_menu.c			\
				src/map_reader.c			\
				src/math_utils.c			\
				src/create_hud.c			\
				src/update_hud.c			\
				src/lose_utils.c			\
				src/create_env.c			\
				src/scoreboard.c			\
				src/ui_display2.c 			\
				src/csfml_utils.c 			\
				src/map_display.c			\
				src/clone_enemy.c			\
				src/player_data.c			\
				src/wave_create.c			\
				src/display_hud.c			\
				src/window_setup.c			\
				src/enemy_reader.c			\
				src/wave_manager.c			\
				src/options_text.c			\
				src/button_setup.c 			\
				src/button_utils.c 			\
				src/csfml_utils2.c			\
				src/enemy_parser.c			\
				src/turret_reader.c			\
				src/upgrade_setup.c			\
				src/formating_hud.c			\
				src/mouse_manager.c			\
				src/enemy_display.c			\
				src/enemies_chain.c			\
				src/error_handling.c		\
				src/turrets_parser.c		\
				src/upgrade_turret.c		\
				src/turrets_display.c		\
				src/bullets_process.c		\
				src/options_creation.c		\
				src/options_managers.c		\
				src/options_managers2.c		\
				src/error_handling_utils.c	\

MAINOBJ		=	$(MAIN:.c=.o)
OBJ			=	$(SRC:.c=.o)

NAME		=	my_defender

LIB			= 	-L. ./lib/lib.a 	\
				-lcsfml-graphics 	\
				-lcsfml-system 		\
				-lcsfml-audio 		\
				-lcsfml-window 		\
				-lm					\


CPPFLAGS	+=	-I includes/
CFLAGS		+=	-Wall -Wextra -g3 -ggdb3

$(NAME):		$(MAINOBJ) $(OBJ)
				make -C lib/
				gcc -o $(NAME) $(MAINOBJ) $(OBJ) $(CFLAGS) $(LIB)

all:			$(NAME)

c:				$(NAME)
				./$(NAME)
				mr_clean

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
