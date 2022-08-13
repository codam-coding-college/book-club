#include "Proxy.hpp"
#include "Connection.hpp"
#include "ReceiverProxy.hpp"

void	client(void)
{
	Connection client(4242, "127.0.0.1");

	std::cout << "Enter a message to send:" << std::endl;

	Connection::TransferData data;
	fgets(data.buffer, Connection::BUFFERSIZE - 1, stdin);

	client.send(data);
}

void	server(void)
{
	SubjectImpl*	actualSubject = new SubjectImpl("ActualSubject");
	Connection*		receiverConnection = new Connection(4242);

	ReceiverProxy	proxy(actualSubject, receiverConnection, "ReceiverProxy");
	
	while (true)
		proxy.receive();
}

int	main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "use: ./proxy <server/client>" << std::endl;
		return (1);
	}
	if (std::string{argv[1]} == "server")
		server();
	else if (std::string{argv[1]} == "client")
		client();
	else
	{
		std::cout << "use: ./proxy <server/client>" << std::endl;
		return (1);
	}
	return (0);
}
