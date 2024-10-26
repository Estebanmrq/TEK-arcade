##
## EPITECH PROJECT, 2024
## B-OOP-400-PAR-arcade
## File description:
## Makefile
##

LIB_PATH = lib

GAME_NIBBLER_PATH = $(LIB_PATH)/game/nibbler
GAME_NIBBLER_NAME = arcade_nibbler.so

GAME_PACMAN_PATH = $(LIB_PATH)/game/pacman
GAME_PACMAN_NAME = arcade_pacman.so

GAME_SNAKE_PATH = $(LIB_PATH)/game/snake
GAME_SNAKE_NAME = arcade_snake.so

GRAPH_NCURSES_PATH = lib/graphical/nCurses
GRAPH_SDL2_PATH = lib/graphical/SDL2
GRAPH_ALLEGRO5_PATH = lib/graphical/Allegro5
GRAPH_SFML_PATH = lib/graphical/SFML

GRAPH_NCURSES_NAME = arcade_ncurses.so
GRAPH_SDL2_NAME = arcade_sdl2.so
GRAPH_ALLEGRO5_NAME = arcade_allegro5.so
GRAPH_SFML_NAME = arcade_sfml.so

CP ?= cp

CXX = g++
CXXFLAGS = -iquote include
CPPFLAGS = -Wall -Wextra -Werror

NAME = arcade

SRC = 	src/main.cpp		\
		src/Arcade.cpp		\
		src/Command.cpp		\
		src/Menu.cpp		\
		src/Game.cpp		\
		src/Launcher.cpp	\
		src/Score.cpp

OBJ = $(SRC:.cpp=.o)

all: core graphicals games

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(CPPFLAGS)

core: $(NAME)

graphicals:
	$(MAKE) -C $(GRAPH_NCURSES_PATH)
	$(MAKE) -C $(GRAPH_SDL2_PATH)
	$(MAKE) -C $(GRAPH_ALLEGRO5_PATH)
	$(MAKE) -C $(GRAPH_SFML_PATH)
	$(CP) $(GRAPH_NCURSES_PATH)/$(GRAPH_NCURSES_NAME) $(LIB_PATH)
	$(CP) $(GRAPH_SDL2_PATH)/$(GRAPH_SDL2_NAME) $(LIB_PATH)
	$(CP) $(GRAPH_ALLEGRO5_PATH)/$(GRAPH_ALLEGRO5_NAME) $(LIB_PATH)
	$(CP) $(GRAPH_SFML_PATH)/$(GRAPH_SFML_NAME) $(LIB_PATH)

games:
	$(MAKE) -C $(GAME_PACMAN_PATH)
	$(MAKE) -C $(GAME_SNAKE_PATH)
	$(MAKE) -C $(GAME_NIBBLER_PATH)
	$(CP) $(GAME_PACMAN_PATH)/$(GAME_PACMAN_NAME) $(LIB_PATH)/$(GAME_PACMAN_NAME)
	$(CP) $(GAME_SNAKE_PATH)/$(GAME_SNAKE_NAME) $(LIB_PATH)/$(GAME_SNAKE_NAME)
	$(CP) $(GAME_NIBBLER_PATH)/$(GAME_NIBBLER_NAME) $(LIB_PATH)/$(GAME_NIBBLER_NAME)

debug: CXXFLAGS += -g3
debug: core 
debug:
	$(MAKE) -C $(GRAPH_NCURSES_PATH) debug
	$(MAKE) -C $(GRAPH_SDL2_PATH) debug
	$(MAKE) -C $(GRAPH_ALLEGRO5_PATH)
	$(MAKE) -C $(GRAPH_SFML_PATH) debug
	$(MAKE) -C $(GAME_PACMAN_PATH) debug
	$(MAKE) -C $(GAME_SNAKE_PATH) debug
	$(MAKE) -C $(GAME_NIBBLER_PATH) debug
	$(CP) $(GRAPH_NCURSES_PATH)/$(GRAPH_NCURSES_NAME) $(LIB_PATH)/$(GRAPH_NCURSES_NAME)
	$(CP) $(GRAPH_SDL2_PATH)/$(GRAPH_SDL2_NAME) $(LIB_PATH)/$(GRAPH_SDL2_NAME)
	$(CP) $(GRAPH_ALLEGRO5_PATH)/$(GRAPH_ALLEGRO5_NAME) $(LIB_PATH)
	$(CP) $(GRAPH_SFML_PATH)/$(GRAPH_SFML_NAME) $(LIB_PATH)
	$(CP) $(GAME_PACMAN_PATH)/$(GAME_PACMAN_NAME) $(LIB_PATH)/$(GAME_PACMAN_NAME)
	$(CP) $(GAME_SNAKE_PATH)/$(GAME_SNAKE_NAME) $(LIB_PATH)/$(GAME_SNAKE_NAME)
	$(CP) $(GAME_NIBBLER_PATH)/$(GAME_NIBBLER_NAME) $(LIB_PATH)/$(GAME_NIBBLER_NAME)

clean:
	$(RM) -f $(OBJ)
	$(MAKE) -C $(GRAPH_NCURSES_PATH) clean
	$(MAKE) -C $(GRAPH_SDL2_PATH) clean
	$(MAKE) -C $(GRAPH_ALLEGRO5_PATH) clean
	$(MAKE) -C $(GRAPH_SFML_PATH) clean
	$(MAKE) -C $(GAME_PACMAN_PATH) clean
	$(MAKE) -C $(GAME_SNAKE_PATH) clean
	$(MAKE) -C $(GAME_NIBBLER_PATH) clean

fclean: clean
	$(RM) -f $(NAME)
	$(MAKE) -C $(GRAPH_NCURSES_PATH) fclean && $(RM) -f $(LIB_PATH)/$(GRAPH_NCURSES_NAME)
	$(MAKE) -C $(GRAPH_SDL2_PATH) fclean && $(RM) -f $(LIB_PATH)/$(GRAPH_SDL2_NAME)
	$(MAKE) -C $(GRAPH_ALLEGRO5_PATH) fclean && $(RM) -f $(LIB_PATH)/$(GRAPH_ALLEGRO5_NAME)
	$(MAKE) -C $(GRAPH_SFML_PATH) fclean && $(RM) -f $(LIB_PATH)/$(GRAPH_SFML_NAME)
	$(MAKE) -C $(GAME_PACMAN_PATH) fclean && $(RM) -f $(LIB_PATH)/$(GAME_PACMAN_NAME)
	$(MAKE) -C $(GAME_SNAKE_PATH) fclean && $(RM) -f $(LIB_PATH)/$(GAME_SNAKE_NAME)
	$(MAKE) -C $(GAME_NIBBLER_PATH) fclean && $(RM) -f $(LIB_PATH)/$(GAME_NIBBLER_NAME)

re: fclean all

.PHONY: all core graphicals games debug clean fclean re
