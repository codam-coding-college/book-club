#pragma once

#include "Subject.hpp"
#include "Connection.hpp"

class ClientProxy : public Subject
{
	public:
		ClientProxy();
		ClientProxy(Connection* connection, );
		~ClientProxy();

		//	bool	hasAccess() const;
		void	print() const override;
	
	private:
		static size_t	getProxyNumber();

	private:
		Connection*	m_connection;
};
