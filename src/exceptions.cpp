#include "exceptions.hpp"

exception::exception(int error)
{
	m_error = error;
}

exception::~exception()
{
}

int exception::what()const
{
	return m_error;
}
