##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	snake.cpp \
		../../src/AGameModule.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME =	arcade_snake.so

CC	=	g++

RM	=	rm -f

CFLAGS	= -Wall -Wextra -Werror

all:    $(NAME)

$(NAME): $(OBJ)
	g++ $(CFLAGS) -shared -fPIC -o $(NAME) $(SRC)
	cp $(NAME) ../

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all
