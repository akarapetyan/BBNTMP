/**
 * @file utility.cpp
 * @brief Implementation of utility type classes
 */

#include <QDir>

#include "utility.hpp"

namespace utility {

bool FileSystemUtility::getEntryListR(const QString& dir, const QStringList& filters, QStringList& result)
{
	QDir currentDir(dir);
	QDir::setCurrent(dir);
	QStringList currentFileList = QDir::current().entryList(filters, QDir::Files);
	if(!currentFileList.isEmpty())
	{
	    foreach(QString item, currentFileList)
		{
		  result.append(dir + "/" + item);
		}
	}

	QStringList currentDirList = currentDir.entryList(QDir::Dirs);
	foreach(QString subDir, currentDirList)
	{
		if (subDir == "." || subDir == "..")
			continue;

		getEntryListR(dir + "/" + subDir, filters, result);
	}

	return !result.isEmpty();
}

} //end of namespace
