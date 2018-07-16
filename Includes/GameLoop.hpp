
#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include "Interface.hpp"
#include "Snake.hpp"
#include "Fruit.hpp"
#include <unistd.h>
#include "TCP.hpp"



SDLinterface * loadLib(std::string str, void *hndl , int x_max, int y_max, Direction dir);
int x_start(int x_max);
int y_start(int y_max);
void	gameLoop( int x_max, int y_max, int lib);
void	ServerGameLoop( int x_max, int y_max, int lib);
void	ClientGameLoop( int lib, std::string ip);

#endif