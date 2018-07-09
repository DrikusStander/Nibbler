FLAGS = -Wall -Werror -Wextra -Iincludes -ISDL_includes -std=c++11
SDLFLAGS = $(shell pkg-config --cflags --libs sdl2)
DIR = ./srcs/
SDLDIR = ./SDL_srcs/
SRCS = main.cpp Snake.cpp Fruit.cpp
SDLSRC = SDLclass.cpp
NAME = Nibler
	
all: dependancies
	clang++ $(addprefix $(DIR), $(SRCS)) $(addprefix $(SDLDIR), $(SDLSRC)) $(FLAGS) -o $(NAME) $(SDLFLAGS)

dependancies:
	brew list sdl2 &>/dev/null || brew install sdl2
	brew list pkg-config &>/dev/null || brew install pkg-config

clean:
	rm -fr $(NAME)

fclean: clean

re: fclean all