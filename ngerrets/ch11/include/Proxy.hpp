#pragma once

#include "Subject.hpp"
#include <iostream>

class Proxy : public Subject
{
	public:
		Proxy();
		Proxy(Subject* subject);
		~Proxy();

		bool	hasAccess() const;
		void	print() const override;
	
	private:
		Subject*	m_subject = NULL;
};
