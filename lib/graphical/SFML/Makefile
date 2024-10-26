##
## EPITECH PROJECT, 2024
## B-OOP-400-PAR-arcade
## File description:
## Makefile
##

CXX = g++
CXXFLAGS = -iquote include -iquote ../../../include
CPPFLAGS = -Wall -Wextra -Werror

LIBS = -lcsfml-system -lcsfml-graphics -lcsfml-audio -lcsfml-window

NAME = arcade_sfml.so

SRC = src/Sfml.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS) -fPIC

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CPPFLAGS) -shared $(LIBS)

debug: CXXFLAGS += -g3
debug: re

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all
