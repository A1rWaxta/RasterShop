#include <QtWidgets/QApplication>
#include "UserInterface.h"
#include "MainWindowX.h"

int main(int argc, char **argv)
{
	QCoreApplication::setOrganizationName("Marcin-Klima");
	QCoreApplication::setApplicationName("RasterShop");

	QApplication App(argc, argv);
//	UserInterface userInterface;
	MainWindowX mainWindow;

	if(ApplicationSettings::Instance() == nullptr)
	{
		return -1;
	}
	if(ApplicationSettings::Instance()->LoadData("res/settings.txt") == false)
	{
		return -1;
	}
//	if(userInterface.LoadUIFile() == false)
//	{
//		return -1;
//	}
//	userInterface.Show();

	mainWindow.show();
	return App.exec();
}