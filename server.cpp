
#include <SDL_net.h>

int		main(void)
{
	SDLNet_Init();
	IPaddress ip;
	SDLNet_ResolveHost(&ip, NULL, 1234);

	TCPsocket server = SDLNet_TCP_Open(&ip);
	TCPsocket client;

	const char *text = "Hello from the server\n";

	while(1)
	{
		if (!client)
		{
			client = SDLNet_TCP_Accept(server);
		}
		else
		{
			SDLNet_TCP_Send(client, text, strlen(text) + 1);
			SDLNet_TCP_Close(client);
			break;
		}
	}
	SDLNet_TCP_Close(server);

	SDLNet_Quit();

	return(0);
}