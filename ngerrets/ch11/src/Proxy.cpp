#include "Proxy.hpp"

Proxy::Proxy() : m_subject(new SubjectImpl()) {}
Proxy::Proxy(SubjectImpl* subject) : m_subject(subject) {}
Proxy::~Proxy() { delete m_subject; }

bool	Proxy::hasAccess() const
{
	if (!m_subject)
		return (false);
	return (true);
}

void	Proxy::print() const
{
	if (!hasAccess())
	{
		std::cout << "ERROR: No access to Subject!" << std::endl;
		return ;
	}
	std::cout << "Forwarding call to Subject..." << std::endl;
	m_subject->print();
}
