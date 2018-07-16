
#include <SDL_net.h>
#include <iostream>

int		main(void)
{
	SDLNet_Init();
	IPaddress ip;
	SDLNet_ResolveHost(&ip, "10.210.3.6", 1234);

	TCPsocket client = SDLNet_TCP_Open(&ip);

	char text[100];

	SDLNet_TCP_Recv(client, text, 100);
	std::cout << text;
	SDLNet_TCP_Close(client);

	SDLNet_Quit();

	return(0);
}