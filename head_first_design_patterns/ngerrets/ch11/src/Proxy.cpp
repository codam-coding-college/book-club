#include "Proxy.hpp"

//	Create a proxy and give it a name
Proxy::Proxy()
{
	m_name = "Proxy" + std::to_string(getProxyNumber());
}

//	Create a proxy from an existing Subject
Proxy::Proxy(Subject* subject) : m_subject(subject)
{
	m_name = "Proxy" + std::to_string(getProxyNumber());
}

//	Create a proxy from an existing Subject, with a custom name
Proxy::Proxy(Subject* subject, const std::string& name) : m_subject(subject)
{
	m_name = name;
}

//	When the proxy is destroyed it also deletes it's subject
Proxy::~Proxy() { delete m_subject; }

//	Simple static method that just increases the number by 1 every time it's called
size_t	Proxy::getProxyNumber()
{
	static size_t	n = 0;
	return (n++);
}

const Subject&	Proxy::getSubject() const
{
	return (*m_subject);
}

//	Check for access (or null-subject)
bool	Proxy::hasAccess() const
{
	if (!m_subject)
		return (false);
	return (true);
}

//	The proxy delegates, it just checks for access and then executes it's subject's implementation
void	Proxy::print() const
{
	if (!hasAccess())
	{
		std::cout << "ERROR: No access to Subject!" << std::endl;
		return ;
	}
	std::cout
		<< '[' << getName() << "] "
		<< "I am a Proxy."
		<< std::endl;
	std::cout
		<< '[' << getName() << "] "
		<< "Forwarding call to my subject: "
		<< getSubject().getName()
		<< std::endl;
	getSubject().print();
}
