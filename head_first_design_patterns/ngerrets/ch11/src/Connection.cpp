#include "Connection.hpp"

static void	error(const char* msg)
{
	perror(msg);
	exit(1);
}

Connection::Connection(unsigned int port)
: m_mode(RECEIVE), m_port(port)
{
	//	Setup the socket
	setupSocket();
	m_serverAddr.sin_addr.s_addr = INADDR_ANY;

	//	Bind the socket
	if (bind(m_socketfd,
		(struct sockaddr *)&m_serverAddr,
		sizeof(struct sockaddr_in)) < 0)
		error("ERROR binding");
	
	listen(m_socketfd, 5);
}

Connection::Connection(unsigned int port,  const std::string& hostname)
: m_mode(SEND), m_port(port), m_hostname(hostname)
{
	setupSocket();
}

Connection::~Connection()
{
	close(m_socketfd);
	close(m_acceptfd);
}

void	Connection::setupSocket()
{
	m_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socketfd < 0)
		error("ERROR opening socket");
	bzero(&m_serverAddr, sizeof(struct sockaddr_in));
	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(m_port);
}

bool	Connection::send(const TransferData& data)
{
	if (m_mode == RECEIVE)
	{
		std::cout << "WARNING Connection not set up to send." << std::endl;
		return (false);
	}
	struct hostent* server = gethostbyname(m_hostname.c_str());
	if (!server)
		error("ERROR on gethostbyname()");

	bcopy(server->h_addr, &m_serverAddr.sin_addr.s_addr, server->h_length);

	if (connect(m_socketfd, (struct sockaddr *) &m_serverAddr, sizeof(struct sockaddr_in)) < 0)
		error("ERROR connecting");

	int n = write(m_socketfd, data.buffer, strlen(data.buffer));
	if (n < 0)
		error("ERROR writing");

	return (true);
}

//	This function is blocking until something has been received
Connection::TransferData	Connection::receive()
{
	TransferData	data;

	bzero(data.buffer, BUFFERSIZE);
	if (m_mode == SEND)
	{
		std::cout << "WARNING Connection not set up to receive." << std::endl;
		return (data);
	}

	socklen_t clientLength = sizeof(struct sockaddr_in);
	m_acceptfd = accept(m_socketfd, (struct sockaddr *) &m_clientAddr, &clientLength);
	if (m_acceptfd < 0)
		error("ERROR accepting");

	std::cout
		<< "Connection::receive() got connection from "
		<< inet_ntoa(m_clientAddr.sin_addr)
		<< " port "
		<< ntohs(m_clientAddr.sin_port)
		<< std::endl;
	
	int n = read(m_acceptfd, data.buffer, BUFFERSIZE - 1);
	if (n < 0)
		error("ERROR reading from socket");
	return (data);
}
