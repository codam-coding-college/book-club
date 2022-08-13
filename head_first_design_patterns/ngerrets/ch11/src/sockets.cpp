#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>

constexpr char		SERVER_HOSTNAME[] = "127.0.0.1";
constexpr int		SERVER_PORTN = 4242;
constexpr int		CLIENT_PORTN = 4242;
constexpr size_t	BUFFERSIZE = 256;

[[noreturn]] void	error(const char* msg)
{
	perror(msg);
	exit(1);
}

void	server(void)
{
	struct sockaddr_in	serverAddr;
	struct sockaddr_in	clientAddr;
	socklen_t			clientLength;
	char				buffer[BUFFERSIZE];

	// int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// if (sockfd < 0)
	// 	error("ERROR opening socket");
	
	// bzero(&serverAddr, sizeof(struct sockaddr_in));
	// serverAddr.sin_family = AF_INET;
	// serverAddr.sin_addr.s_addr = INADDR_ANY;
	// serverAddr.sin_port = htons(SERVER_PORTN);

	//if (bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(struct sockaddr_in)) < 0)
	//	error("ERROR binding");
	
	listen(sockfd, 5);

	clientLength = sizeof(struct sockaddr_in);
	
	int	acceptfd = accept(sockfd, (struct sockaddr *) &clientAddr, &clientLength);
	if (acceptfd < 0)
		error("ERROR accepting");
	
	printf("server: got connection from %s port %d\n",
		inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	
	while (true)
	{
		bzero(buffer, BUFFERSIZE);
		int n = read(acceptfd, buffer, BUFFERSIZE - 1);
		if (n < 0)
			error("ERROR reading from socket");

		printf("Recieved message: %s\n",buffer);
		if (strncmp(buffer, "exit", strlen("exit")) == 0)
			break ;
	}

	close(acceptfd);
	close(sockfd);
}

void	client(void)
{
	struct sockaddr_in	serverAddr;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	
	struct hostent* server = gethostbyname(SERVER_HOSTNAME);
	if (!server)
		error("ERROR on gethostbyname()");

	bzero(&serverAddr, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;

	bcopy(server->h_addr, &serverAddr.sin_addr.s_addr, server->h_length);
	serverAddr.sin_port = htons(CLIENT_PORTN);

	if (connect(sockfd, (struct sockaddr *) &serverAddr, sizeof(struct sockaddr_in)) < 0)
		error("ERROR connecting");

	while (true)
	{
		std::cout << "Write a message:" << std::endl;
		char buffer[BUFFERSIZE];
		bzero(buffer, BUFFERSIZE);

		fgets(buffer, BUFFERSIZE - 1, stdin);
		int n = write(sockfd, buffer, strlen(buffer));
		if (n < 0)
			error("ERROR writing");
		
		if (n == 0 || strncmp(buffer, "exit", strlen("exit")) == 0)
			break ;
	}
	close(sockfd);
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
