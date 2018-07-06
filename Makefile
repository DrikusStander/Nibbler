FLAGS = -Wall -Werror -Wextra -Iincludes -ISDL_includes -std=c++11
SDLFLAGS = $(shell pkg-config --cflags --libs sdl2)
DIR = ./srcs/
SDLDIR = ./SDL_srcs/
SRCS = main.cpp Snake.cpp
SDLSRC = SDLclass.cpp
NAME = Nibler

all:
	clang++ $(addprefix $(DIR), $(SRCS)) $(addprefix $(SDLDIR), $(SDLSRC)) $(FLAGS) -o $(NAME) $(SDLFLAGS)

clean:
	rm -fr $(NAME)

fclean: clean
	rm -fr stdin

re: fclean all