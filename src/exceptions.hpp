#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

/**
 * @file exceptions.hpp
 * @brief Holder for all kind of exceptions
 */

namespace exceptions
{

/**
 * @brief class exception
 * @details exception is base class for all the exceptions using in the application
 */
class exception
{
	int m_error;
public:
	exception(int);
	virtual ~exception();
	virtual int what() const;
};

} //end of namespace

#endif
