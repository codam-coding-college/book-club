#pragma once

#include <iostream>

//	Virtual subject class that make sure you can handle the Proxy and (actual) Subject the same way
class Subject
{
	public:
		virtual ~Subject() {}
		virtual void	print() const = 0;

		inline virtual const std::string&	getName() const { return m_name; }

	protected:
		std::string	m_name = "";
};

//	The class that holds the subject implementation, can be substituted by a proxy
class SubjectImpl : public Subject
{
	public:
		SubjectImpl();
		SubjectImpl(const std::string& name);

		void	print() const override;

	private:
		static size_t	getSubjectNumber();

};
