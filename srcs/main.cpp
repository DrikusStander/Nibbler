
#include "main.hpp"
// #include "Snake.hpp"
#include "Interface.hpp"
// #include "Fruit.hpp"
// #include <unistd.h>
#include "GameLoop.hpp"

#include <regex>

int main(int ac, char **av)
{
	srand(time(NULL));
	
	if (ac == 2)
	{
		if (std::regex_match(av[1], std::regex("([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}$)")))
		{
			try
			{
				ClientGameLoop(1, av[1]);
			}
			catch(SDL_error &exception)
			{
				std::cout << exception.what() << std::endl;
			}
			// catch(...)
			// {
			// 	std::cout << "Exception" << std::endl;
			// }
		}
		else
		{
			std::cout << "invalid IP" << std::endl;
			std::cout << "Single Player usage: ./Nibler <int x> <int y> <int 1-3 [lib]>" << std::endl;
			std::cout << "Server usage: ./Nibler <int x> <int y> <int 1-3 [lib]> <-s>" << std::endl;
			std::cout << "Client usage: ./Nibler <Server IP>" << std::endl;
			return(-1);
		}
	}
	else if ( ac < 4 || ac > 5)
	{
		std::cout << "Single Player usage: ./Nibler <int x> <int y> <int 1-3 [lib]>" << std::endl;
		std::cout << "Server usage: ./Nibler <int x> <int y> <int 1-3 [lib]> <-s>" << std::endl;
		std::cout << "Client usage: ./Nibler <Server IP>" << std::endl;
		return(-1);
	}
	else
	{
		int x_max;
		int y_max;
		int lib;
		try
		{
			x_max = std::stoi(av[1], NULL, 10);
			y_max = std::stoi(av[2], NULL, 10);
			lib = std::stoi(av[3], NULL, 10);
		}
		catch (...)
		{
			std::cout << "Single Player usage: ./Nibler <int x> <int y> <int 1-3 [lib]>" << std::endl;
			std::cout << "Server usage: ./Nibler <int x> <int y> <int 1-3 [lib]> <-s>" << std::endl;
			std::cout << "Client usage: ./Nibler <Server IP>" << std::endl;
			return(-1);
		}
		if (x_max > X_MAX || y_max > Y_MAX )
		{
			std::cout << "Map size to Big" << std::endl;
			std::cout << "X max val: " << X_MAX << std::endl;
			std::cout << "Y max val: " << Y_MAX << std::endl;
			return(-1);
		}
		else if (x_max < X_MIN || y_max < Y_MIN )
		{
			std::cout << "Map size to small" << std::endl;
			std::cout << "X min val: " << X_MIN << std::endl;
			std::cout << "Y min val: " << Y_MIN << std::endl;
			return(-1);
		}
		else if (lib < 1 || lib > 3)
		{
			std::cout << "Invalid Library selected" << std::endl;
			std::cout << "Single Player usage: ./Nibler <int x> <int y> <int 1-3 [lib]>" << std::endl;
			std::cout << "Server usage: ./Nibler <int x> <int y> <int 1-3 [lib]> <-s>" << std::endl;
			std::cout << "Client usage: ./Nibler <Server IP>" << std::endl;
			return(-1);
		}
		try
		{
			if (ac == 5)
			{
				std::string str(av[4]);
				if (str == "-s")
				{
					ServerGameLoop(x_max, y_max, lib);
				}
				else
				{
					std::cout << "Single Player usage: ./Nibler <int x> <int y> <int 1-3 [lib]>" << std::endl;
					std::cout << "Server usage: ./Nibler <int x> <int y> <int 1-3 [lib]> <-s>" << std::endl;
					std::cout << "Client usage: ./Nibler <Server IP>" << std::endl;
					return(-1);
				}
			}
			else
			{
				gameLoop(x_max, y_max, lib);
			}
		}
		catch(SDL_error &exception)
		{
			std::cout << exception.what() << std::endl;
		}
		catch(...)
		{
			std::cout << "Exception" << std::endl;
		}
	}
	return(0);
}