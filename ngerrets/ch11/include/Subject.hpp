#pragma once

#include <iostream>

//	Virtual subject class that make sure you can handle the Proxy and (actual) Subject the same way
class Subject
{
	public:
		virtual ~Subject() {}
		virtual void	print() const = 0;
};

//	The class that holds the subject implementation, can be substituted by a proxy
class SubjectImpl : public Subject
{

	public:
		void	print() const override;

};
