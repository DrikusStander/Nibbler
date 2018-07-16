
#ifndef TCP_HPP
#define TCP_HPP


#include <string>
#include <SDL_net.h>

class TCP 
{
	private:
		TCPsocket _server;
		TCPsocket _client;
		IPaddress _ip;
		char _buff[100];

	protected:
	public:
		TCP( void );
		TCP( std::string ip);
		TCP( TCP const & src);
		~TCP( void );
		TCP const & operator=(TCP const & rhs);
		void	send(std::string str);
		char *	recv( void );
};

#endif