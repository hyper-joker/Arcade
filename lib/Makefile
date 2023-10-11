##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

all: games graphicals

games:
	make -C ./pacman
	make -C ./marioKart
	make -C ./snake

graphicals:
	make -C ./ncurses
	make -C ./SFML
	make -C ./SDL2

clean:
	make -C ./pacman clean
	make -C ./marioKart clean
	make -C ./snake clean
	make -C ./ncurses clean
	make -C ./SFML clean
	make -C ./SDL2 clean

fclean: clean
	make -C ./pacman fclean
	make -C ./marioKart fclean
	make -C ./snake fclean
	make -C ./ncurses fclean
	make -C ./SFML fclean
	make -C ./SDL2 fclean

re: fclean all
