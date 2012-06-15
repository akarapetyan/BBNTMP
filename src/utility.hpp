#ifndef UTILITY_HPP_
#define UTILITY_HPP_

/**
 * @file utility.hpp
 * @brief Holder for utility routines used in the application
 */
namespace utility
{

/**
 * @brief class FileSystemUtility
 * @details FileSystemUtility is intended to hold utility routines related to file system stuff
 */
class FileSystemUtility
{
public:
	/**
	 * @details getEntryListR get the files list in the specified directory using the specified filters.
	 * for example get all the ".avi" files
	 */
	static bool getEntryListR(const QString& dir, const QStringList& filters, QStringList& result);
};

}//end of namespace

#endif /* UTILITY_HPP_ */
