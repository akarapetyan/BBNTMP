#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <iostream>

//base class for all the exceptions
class exception
{
	int m_error;
public:
	exception(int);
	virtual ~exception();
	virtual int what() const;
};

#endif
