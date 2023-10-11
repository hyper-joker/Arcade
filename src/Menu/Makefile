##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	Menu.cpp \
		../AGameModule.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME =	arcade_menu.so

CC	=	g++

RM	=	rm -f

CFLAGS	= -Wall -Wextra -Werror

all:    $(NAME)

$(NAME): $(OBJ)
	g++ $(CFLAGS) -shared -fPIC -o $(NAME) $(SRC)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all
