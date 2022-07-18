#pragma once

#include "Subject.hpp"
#include <iostream>

class Proxy : Subject
{
	public:
		Proxy();
		Proxy(SubjectImpl* subject);
		~Proxy();

		bool	hasAccess() const;
		void	print() const override;
	
	private:
		SubjectImpl*	m_subject = NULL;
};
