//
// Created by waxta on 13.07.19.
//

#include <QtUiTools/QUiLoader>
#include "UserInterface.h"

class QMainWindow;

UserInterface::UserInterface() : appSettings(ApplicationSettings::Instance()), userInterface(nullptr),
				mainWindow(nullptr)
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::CreateActions()
{

}

void UserInterface::OpenFile()
{
}

void UserInterface::Show()
{
	mainWindow = findChild<MainWindow*>("MainWindow");

	mainWindow->Show();
}

bool UserInterface::LoadUIFile()
{
	QFile uiFile("res/interface.ui");
	if (uiFile.open(QIODevice::ReadOnly) == false)
	{
		QMessageBox::critical(nullptr, "Error", "Interface's file not found!");
		return false;
	}

	QUiLoader loader;
	userInterface = loader.load(&uiFile, this);
	uiFile.close();

	return true;
}