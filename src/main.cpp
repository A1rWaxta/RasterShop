#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include "ApplicationSettings.h"

int main(int argc, char **argv)
{
	QApplication App(argc, argv);

	QCoreApplication::setOrganizationName("Marcin-Klima");
	QCoreApplication::setApplicationName("RasterShop");

	MainWindow mainWindow;

	if(ApplicationSettings::Instance() == nullptr)
	{
		return -1;
	}
	if(ApplicationSettings::Instance()->LoadData("res/settings.txt") == false)
	{
		return -1;
	}

	mainWindow.show();
	return App.exec();
}