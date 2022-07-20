#pragma once

#include "Subject.hpp"
#include <iostream>

class Proxy : public Subject
{
	public:
		Proxy();
		Proxy(Subject* subject);
		Proxy(Subject* subject, const std::string& name);
		~Proxy();

		bool	hasAccess() const;
		void	print() const override;
	
	private:
		static size_t	getProxyNumber();
		const Subject&	getSubject() const;

	private:
		Subject*	m_subject = NULL;
};
