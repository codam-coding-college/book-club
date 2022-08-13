#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>

//	Represents an internet connection to a remote host
class Connection
{
	public:
		static constexpr size_t BUFFERSIZE = 256;

		//	Represents the data that has been received/send
		struct TransferData
		{
			char	buffer[BUFFERSIZE];
		};

		enum TransferMode
		{
			SEND,
			RECEIVE,
			BOTH
		};

	public:
		Connection(unsigned int port);
		Connection(unsigned int port, const std::string& hostname);
		~Connection();

		bool			send(const TransferData& data);
		TransferData	receive();
	
	private:
		void	setupSocket();

	private:
		TransferMode		m_mode;
		unsigned int		m_port;
		std::string			m_hostname;

		int					m_socketfd;
		int					m_acceptfd;
		struct sockaddr_in	m_serverAddr;
		struct sockaddr_in	m_clientAddr;
};
