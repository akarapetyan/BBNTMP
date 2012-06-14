#include <bb/cascades/Application>
#include <bb/cascades/QListDataModel>

#include <bb/cascades/ListView>
#include <QVariantList>

#include "window.hpp"
#include "player.hpp"
#include "exceptions.hpp"
#include "utility.hpp"

#include <iostream>

using namespace bb::cascades;


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
		filters << "*.avi";
		filters << "*.mp4";
		bool b = utility::getEntryListR("/accounts/1000", result, filters);
		if(b)
		{
			//TODO for now let's play the first found video
			player.runPlayer(result[0]);
		}
    }
    catch(const exception& e)
    {
    	//do corresponding job
    }

    return Application::exec();
}

