#include "Proxy.hpp"

int	main(void)
{
	//	A proxy of a proxy of SubjectImpl
	Proxy	proxy
	(
		new Proxy( new SubjectImpl() )
	);

	proxy.print();

	return (0);
}