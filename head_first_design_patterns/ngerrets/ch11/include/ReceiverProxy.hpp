#pragma once

#include "Subject.hpp"
#include "Connection.hpp"

class ReceiverProxy : public Subject
{
	public:
		ReceiverProxy(Subject* subject, Connection* connection);
		ReceiverProxy(Subject* subject, Connection* connection, const std::string& name);
		~ReceiverProxy();

		bool	hasAccess() const;
		void	print() const override;
		void	receive();
	
	private:
		static size_t	getProxyNumber();
		const Subject&	getSubject() const;

	private:
		Subject*	m_subject = NULL;
		Connection*	m_connection = NULL;
};
