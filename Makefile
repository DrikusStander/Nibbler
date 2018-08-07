# -Wall -Werror -Wextra
FLAGS =  -Iincludes -ILibs_includes -std=c++11 $(shell pkg-config --cflags --libs sdl2_net)
LIBFLAGS = -dynamiclib -flat_namespace
SDLFLAGS = $(shell pkg-config --cflags --libs sdl2) $(shell pkg-config --cflags --libs sdl2_ttf) $(shell pkg-config --cflags --libs sdl2_mixer)
FLTKFLAGS = -I$(HOME)/.brew/Cellar/fltk/1.3.4-2/include -L$(HOME)/.brew/Cellar/fltk/1.3.4-2/lib -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -lfltk $(shell pkg-config --cflags --libs sdl2_mixer)
SFMLFLAGS = -I$(HOME)/.brew/Cellar/sfml/2.4.2_1/include -L$(HOME)/.brew/lib -lsfml-graphics -lsfml-window -lsfml-audio
ALLEGROFLAGS = $(shell pkg-config --cflags --libs allegro-5 allegro_audio-5 allegro_acodec-5)
DIR = ./srcs/
SDLDIR = ./Libs_srcs/
SRCS = main.cpp Snake.cpp Fruit.cpp GameLoop.cpp 2PlayerLoop.cpp TCP.cpp ../Libs_srcs/Exceptions.cpp
SDLSRC = SDLclass.cpp Exceptions.cpp
FLTKSRC = FLTKclass.cpp Draw.cpp Exceptions.cpp
SFMLSRC = SFMLclass.cpp Exceptions.cpp

NAME = Nibler
	
all: libs
	clang++ $(addprefix $(DIR), $(SRCS)) $(FLAGS) -o $(NAME) $(SDLFLAGS)
ifneq ($(LD_LIBRARY_PATH),$(HOME)/.brew/lib)
	@echo "export LD_LIBRARY_PATH=~/.brew/lib" >> ~/.zshrc
	@exec zsh;
endif

libs: dependancies
	clang++ $(addprefix $(SDLDIR), $(SDLSRC)) $(LIBFLAGS) $(FLAGS) $(SDLFLAGS) -o lib1.so
	clang++ $(addprefix $(SDLDIR), $(FLTKSRC)) $(LIBFLAGS) $(FLAGS) $(FLTKFLAGS) $(ALLEGROFLAGS) -o lib2.so
	clang++ $(addprefix $(SDLDIR), $(SFMLSRC)) $(LIBFLAGS) $(FLAGS) $(SFMLFLAGS) -o lib3.so



dependancies:
	brew list sdl2 &>/dev/null || brew install sdl2
	brew list pkg-config &>/dev/null || brew install pkg-config
	brew list sdl2_ttf &>/dev/null || brew install sdl2_ttf
	brew list sdl2_mixer &>/dev/null || brew install sdl2_mixer
	brew list sdl2_net &>/dev/null || brew install sdl2_net
	brew list fltk &>/dev/null || brew install fltk
	brew list sfml &>/dev/null || brew install sfml

clean:
	rm -fr $(NAME)

fclean: clean
	rm -fr lib1.so lib2.so lib3.so
	
re: fclean all