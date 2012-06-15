/**
 * @file exceptions.cpp
 * @brief Implementation of exception class
 */

#include "exceptions.hpp"

namespace exceptions
{

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

} //end of namespace
