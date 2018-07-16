FLAGS = -Wall -Werror -Wextra -Iincludes -ISDL_includes -std=c++11 $(shell pkg-config --cflags --libs sdl2_net)
LIBFLAGS = -dynamiclib -flat_namespace
SDLFLAGS = $(shell pkg-config --cflags --libs sdl2) $(shell pkg-config --cflags --libs sdl2_ttf) $(shell pkg-config --cflags --libs sdl2_mixer)
DIR = ./srcs/
SDLDIR = ./SDL_srcs/
SRCS = main.cpp Snake.cpp Fruit.cpp GameLoop.cpp 2PlayerLoop.cpp TCP.cpp ../SDL_srcs/Exceptions.cpp
SDLSRC = SDLclass.cpp Exceptions.cpp
SDLSRC2 = SDLclass2.cpp Exceptions.cpp
SDLSRC3 = SDLclass3.cpp Exceptions.cpp

NAME = Nibler
	
all: libs
	clang++ $(addprefix $(DIR), $(SRCS)) $(FLAGS) -o $(NAME) $(SDLFLAGS)

libs: dependancies
	clang++ $(addprefix $(SDLDIR), $(SDLSRC)) $(LIBFLAGS) $(FLAGS) $(SDLFLAGS) -o lib1.so
	clang++ $(addprefix $(SDLDIR), $(SDLSRC2)) $(LIBFLAGS) $(FLAGS) $(SDLFLAGS) -o lib2.so
	clang++ $(addprefix $(SDLDIR), $(SDLSRC3)) $(LIBFLAGS) $(FLAGS) $(SDLFLAGS) -o lib3.so



dependancies:
	brew list sdl2 &>/dev/null || brew install sdl2
	brew list pkg-config &>/dev/null || brew install pkg-config
	brew list sdl2_ttf &>/dev/null || brew install sdl2_ttf
	brew list sdl2_mixer &>/dev/null || brew install sdl2_mixer

clean:
	rm -fr $(NAME)

fclean: clean
	rm -fr lib1.so lib2.so lib3.so
	
re: fclean all