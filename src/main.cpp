/**
 * @file main.cpp
 * @brief Contains main - the entry point function implementation
 */

#include <bb/cascades/Application>
#include <bb/cascades/QListDataModel>

#include <bb/cascades/ListView>
#include <QVariantList>

#include "window.hpp"
#include "player.hpp"
#include "exceptions.hpp"
#include "utility.hpp"


using namespace bb::cascades;
using namespace utility;
using namespace exceptions;


//TODO for testing purposes only
/*ListView* getListView()
{
	ListView *pListView = new ListView();
	pListView->setDataModel(new QListDataModel<QString>(entries));
	return pListView;
}*/


int main(int argc, char **argv)
{
    Application app(argc, argv);

    Window mainWindow;
    Player player;

    try
    {
    	QStringList result;
		QStringList filters;
		filters << "*.mp4";
		filters << "*.avi";
		bool b = FileSystemUtility::getEntryListR("/", filters, result);
		if(b)
		{
			//TODO for now let's play the first found video
			QString firstVideo = result[0];
			player.runPlayer(firstVideo);
		}
    }
    catch(const exception& e)
    {
    	//do corresponding job
    }

    return Application::exec();
}

