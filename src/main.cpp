#include <bb/cascades/Application>

#include "window.hpp"
#include "player.hpp"
#include "exceptions.hpp"

#include <iostream>


using ::bb::cascades::Application;

int main(int argc, char **argv)
{
    Application app(argc, argv);

    Window mainWindow;

    Player player;
    try
    {
    	player.runPlayer();
    }
    catch(const exception& e)
    {
    	//do corresponding job
    }

    return Application::exec();
}

