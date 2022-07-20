#include "Proxy.hpp"

//	Create a proxy and a new SubjectImpl (for ease)
Proxy::Proxy() : m_subject(new SubjectImpl()) {}

//	Create a proxy from an existing Subject
Proxy::Proxy(Subject* subject) : m_subject(subject) {}

//	When the proxy is destroyed it also deletes it's subject
Proxy::~Proxy() { delete m_subject; }

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
	std::cout << "I am Proxy." << std::endl;
	std::cout << "[PROXY] Forwarding call to Subject:" << std::endl;
	m_subject->print();
}
