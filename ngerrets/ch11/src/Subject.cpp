#include "Subject.hpp"

SubjectImpl::SubjectImpl()
{
	m_name = "Subject" + std::to_string(getSubjectNumber());
}

SubjectImpl::SubjectImpl(const std::string& name)
{
	m_name = name;
}

//	Simple static method that just increases the number by 1 every time it's called
size_t	SubjectImpl::getSubjectNumber()
{
	static size_t	n = 0;
	return (n++);
}

void	SubjectImpl::print() const
{
	std::cout << '[' << getName() << "] " << "I am a Subject." << std::endl;
}
