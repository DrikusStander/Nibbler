
#ifndef TCP_HPP
#define TCP_HPP


#include <string>
#include <SDL_net.h>
#include "Exceptions.hpp"

class TCP 
{
	private:
		TCPsocket	_server;
		TCPsocket	_client;
		IPaddress	_ip;
		char		*_buff;

	protected:
	public:
		TCP( void );
		TCP( std::string ip);
		TCP( TCP const & src);
		~TCP( void );
		TCP const & operator=(TCP const & rhs);
		void	send(int value);
		int		recv(int *value);
};

#endif