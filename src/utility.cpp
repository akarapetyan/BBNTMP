#include <QDir>

#include "utility.hpp"

bool utility::getEntryListR(const QString& dir, QStringList& result, const QStringList& filters)
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

            getEntryListR(dir + "/" + subDir, result, filters);
        }

        return !result.isEmpty();
}
