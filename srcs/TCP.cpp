
#include "TCP.hpp"

TCP::TCP( void )
{
	SDLNet_Init();
	SDLNet_ResolveHost(&this->_ip, NULL, 1234);
	this->_server = SDLNet_TCP_Open(&this->_ip);
	this->_client = NULL;
	while(1)
	{
		if (!this->_client)
		{
			this->_client = SDLNet_TCP_Accept(this->_server);
		}
		else
		{
			break;
		}
	}
	return;
}

TCP::TCP( std::string ip)
{
	SDLNet_Init();
	SDLNet_ResolveHost(&this->_ip, ip.c_str(), 1234);
	this->_client = SDLNet_TCP_Open(&this->_ip);
	if (this->_client == NULL)
		throw SDL_error("Unable to connect to server at ip: " + ip);
	this->_server = NULL;
	return;
}

TCP::TCP( TCP const & src)
{
	this->_ip = src._ip;
	this->_server = src._server;
	this->_client = src._client;
	return;
}

TCP::~TCP( void )
{
	if (this->_server)
		SDLNet_TCP_Close(this->_server);
	if (this->_client)
		SDLNet_TCP_Close(this->_client);
	SDLNet_Quit();
	return;
}

TCP const & TCP::operator=(TCP const & rhs)
{
	this->_ip = rhs._ip;
	this->_server = rhs._server;
	this->_client = rhs._client;
	return(*this);
}

void	TCP::send(int value)
{
	this->_buff = reinterpret_cast<char *>(&value);
	SDLNet_TCP_Send(this->_client, this->_buff, sizeof(value));
}

int		TCP::recv(int *value )
{
	this->_buff = reinterpret_cast<char *>(value);
	SDLNet_TCP_Recv(this->_client, this->_buff, 4);
	if (!this->_buff)
		return(-42);
	return(*this->_buff);
}