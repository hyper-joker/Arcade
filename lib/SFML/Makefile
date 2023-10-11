##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	sfml.cpp \
		../../src/ADisplayModule.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME =	arcade_sfml.so

CC	=	g++

RM	=	rm -f

CFLAGS	= -Wall -Wextra -Werror

all:    $(NAME)

$(NAME): $(OBJ)
	g++ $(CFLAGS) -shared -fPIC -o $(NAME) $(SRC) -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
	cp $(NAME) ../

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all
