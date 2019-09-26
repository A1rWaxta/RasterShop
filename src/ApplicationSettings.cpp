//
// Created by waxta on 05.09.19.
//

#include "ApplicationSettings.h"
#include <fstream>
#include <QtWidgets/QMessageBox>
#include <QtCore/QFile>
#include <QtUiTools>

class ApplicationSettings::ConstructorEnabler : public ApplicationSettings
{
};

std::shared_ptr<ApplicationSettings> ApplicationSettings::instance;

ApplicationSettings::ApplicationSettings()
{
	windowHeight = -1;
	windowWidth = -1;
}

std::shared_ptr<ApplicationSettings> ApplicationSettings::Instance()
{
	if(instance == nullptr)
	{
		try
		{
			instance = std::make_shared<ConstructorEnabler>();
		}
		catch(std::bad_alloc & e)
		{
			instance = nullptr;
		}
	}

	return instance;
}

bool ApplicationSettings::LoadData(const std::string & filename = "settings.txt")
{
	std::ifstream configFile;
	std::string line;
	std::string key;
	int equalMarkPos;

	configFile.open(filename, std::ios::in);
	if(configFile.is_open() == false)
	{
		QMessageBox::critical(nullptr, "Error", "Setting's file not found!");
		return false;
	}

	while(configFile.eof() != true)
	{
		std::getline(configFile, line);
		equalMarkPos = line.find('=');
		key = line.substr(0, equalMarkPos);

		if(key == "window_title")
		{
			windowTitle = line.substr(equalMarkPos + 1);
			windowTitle.erase(std::remove(windowTitle.begin(), windowTitle.end(), '\"'), windowTitle.end());
		}
		else if(key == "window_width")
		{
			windowWidth = std::stoi(line.substr(equalMarkPos + 1));
		}
		else if(key == "window_height")
		{
			windowHeight = std::stoi(line.substr(equalMarkPos + 1));
		}
	}

	return true;
}

short ApplicationSettings::GetWindowHeight() const
{
	return windowHeight;
}

short ApplicationSettings::GetWindowWidth() const
{
	return windowWidth;
}

const std::string &ApplicationSettings::GetWindowTitle() const
{
	return windowTitle;
}
