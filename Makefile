##
## EPITECH my_runner, 2018
## MUL_my_runner_2018
## File description:
## my_runner Makefile
##

CC	=	gcc
ECHO	=	echo -e

COLOR	=   31
LIGHT   =   \e[0m
BOLD    =   \e[1m
BLACK   =   \e[30m
RED     =   \e[31m
GREEN   =   \e[32m
YELLOW  =   \e[33m
BLUE    =   \e[34m
PURPLE  =   \e[35m
CYAN    =   \e[36m
WHITE   =   \e[37m
DEFAULT =   \e[0;37m

INFO    =   $(BOLD)$(GREEN)[INFO]\t$(WHITE)
WARNING =   $(BOLD)$(YELLOW)[WARNING]\t$(WHITE)
ERROR   =   $(BOLD)$(RED)[ERROR]\t$(WHITE)

BIN_DIR	=	./bin/
SRC_DIR	=	./src/
OBJ_DIR	=	./obj/
INC_DIR	=	./include/

SRC	=	$(wildcard $(SRC_DIR)*.c)	\
		$(wildcard $(SRC_DIR)str/*.c)
OBJ	=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CSFML	=	-lcsfml-system		\
		-lcsfml-window		\
		-lcsfml-graphics	\
		-lcsfml-audio

CFLAGS	=	-I$(INC_DIR)

NAME	=	my_runner

$(NAME):	$(OBJ)
	@echo -en "\e[1m\e[38;2;`expr $$RANDOM % 255`;`expr $$RANDOM % 255`;`expr $$RANDOM % 255`m"
	$(CC) $(OBJ) $(CFLAGS) $(CSFML) -lm -o $(BIN_DIR)$(NAME)
	@cp $(BIN_DIR)$(NAME) .
	@$(ECHO) "$(INFO)Build complete !$(DEFAULT)"

$(OBJ): $(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@echo -en "\e[1m\e[38;2;`expr $$RANDOM % 255`;`expr $$RANDOM % 255`;`expr $$RANDOM % 255`m"
	$(CC) $(CFLAGS) -g -c $< -o $@

all:	setup $(NAME)

clean:
	@rm -f $(OBJ)
	@rm -f $(BIN_DIR)$(NAME)
	@$(ECHO) "$(INFO)Files removed !$(DEFAULT)"

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

redebug:	fclean debug

setup:
	@$(ECHO) "\n$(BOLD)$(WHITE)Project setup : $(CYAN)$(NAME)$(DEFAULT)\n"
	@mkdir -p $(BIN_DIR) && $(ECHO) "$(INFO)$(BIN_DIR)\t\t\t$(GREEN)[OK]$(DEFAULT)" || $(ECHO) "$(ERROR)$(BIN_DIR)\t\t\t$(RED)[x]$(DEFAULT)"
	@mkdir -p $(SRC_DIR) && $(ECHO) "$(INFO)$(SRC_DIR)\t\t\t$(GREEN)[OK]$(DEFAULT)" || $(ECHO) "$(ERROR)$(SRC_DIR)\t\t\t$(RED)[x]$(DEFAULT)"
	@mkdir -p $(OBJ_DIR) && $(ECHO) "$(INFO)$(OBJ_DIR)\t\t\t$(GREEN)[OK]$(DEFAULT)" || $(ECHO) "$(ERROR)$(OBJ_DIR)\t\t\t$(RED)[x]$(DEFAULT)"
	@mkdir -p $(OBJ_DIR)str/ && $(ECHO) "$(INFO)$(OBJ_DIR)str/\t\t$(GREEN)[OK]$(DEFAULT)" || $(ECHO) "$(ERROR)$(OBJ_DIR)str/\t\t$(RED)[x]$(DEFAULT)"
	@mkdir -p $(INC_DIR) && $(ECHO) "$(INFO)$(INC_DIR)\t\t$(GREEN)[OK]$(DEFAULT)" || $(ECHO) "$(ERROR)$(INC_DIR)\t\t$(RED)[x]$(DEFAULT)"
	@$(ECHO) "\n"

.PHONY: all debug clean fclean setup re redebug
