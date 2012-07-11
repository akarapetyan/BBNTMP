/**
 * @file main.cpp
 * @brief Contains main - the entry point function implementation
 */

#include <bb/cascades/Application>
#include <bb/cascades/OrientationSupport>

#include "window.hpp"
#include "exceptions.hpp"


using namespace bb::cascades;
using namespace exceptions;


int main(int argc, char **argv)
{
    Application app(argc, argv);

    OrientationSupport::instance().setSupportedDisplayOrientation(SupportedDisplayOrientation::All);
    Player* player = new Player;
    Window mainWindow(player);

    return  Application::exec();
}

