##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	src/main.cpp \
		src/ADisplayModule.cpp \
		src/AGameModule.cpp \
		src/Core.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME =	arcade

CC	=	g++

RM	=	rm -f

CFLAGS	= -Wall -Wextra -Werror

all:    $(NAME)

$(NAME): $(OBJ) core
	make -C ./lib

core: 	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -g -ldl -fno-gnu-unique
	make -C ./src/Menu

games:
	make -C ./lib games

graphicals:
	make -C ./lib graphicals

clean:
	$(RM) $(OBJ)
		make -C ./lib clean
	make -C ./src/Menu clean

fclean: clean
	$(RM) $(NAME)
		make -C ./lib fclean
	make -C ./src/Menu fclean

re: fclean all
