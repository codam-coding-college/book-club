#include "ReceiverProxy.hpp"
#include <locale>

ReceiverProxy::ReceiverProxy(Subject* subject, Connection* connection)
: m_subject(subject), m_connection(connection)
{
	m_name = "Proxy" + std::to_string(getProxyNumber());
}

ReceiverProxy::ReceiverProxy(Subject* subject, Connection* connection, const std::string& name)
: m_subject(subject), m_connection(connection)
{
	m_name = name;
}

//	Deletes it's subject and connection
ReceiverProxy::~ReceiverProxy()
{
	delete m_subject;
	delete m_connection;
}

//	Simple static method that just increases the number by 1 every time it's called
size_t	ReceiverProxy::getProxyNumber()
{
	static size_t	n = 0;
	return (n++);
}

const Subject&	ReceiverProxy::getSubject() const
{
	return (*m_subject);
}

bool	ReceiverProxy::hasAccess() const
{
	if (!m_subject)
		return (false);
	return (true);
}

//	The proxy delegates, it just checks for access and then executes it's subject's implementation
void	ReceiverProxy::print() const
{
	if (!hasAccess())
	{
		std::cout << "ERROR: No access to Subject!" << std::endl;
		return ;
	}
	std::cout
		<< '[' << getName() << "] "
		<< "I am a ReceiverProxy."
		<< std::endl;
	std::cout
		<< '[' << getName() << "] "
		<< "Forwarding call to my subject: "
		<< getSubject().getName()
		<< std::endl;
	getSubject().print();
}

//	This is blocking
void	ReceiverProxy::receive()
{
	if (!m_connection)
	{
		std::cout << "ERROR: No connection" << std::endl;
		return ;
	}

	Connection::TransferData data;
	data = m_connection->receive();
	//	Using c++strings cuz why not
	std::string buffstr(data.buffer);
	if (buffstr.at(buffstr.size() - 1) == '\n')
		buffstr.erase(buffstr.size() - 1);
	if (buffstr == "print")
		print();
	else
		std::cout << "Ignoring unknown command: '" << buffstr << "'" << std::endl;
}
