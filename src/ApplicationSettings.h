//
// Created by waxta on 05.09.19.
//

#pragma once

#include <memory>
#include <QtWidgets/QWidget>

//SINGLETON CLASS
class ApplicationSettings
{
public:
	static std::shared_ptr<ApplicationSettings> Instance();

	short GetWindowHeight() const;

	short GetWindowWidth() const;

	bool LoadData(const std::string &filename);

	const std::string &GetWindowTitle() const;

private:
	ApplicationSettings();

	class ConstructorEnabler;

	static std::shared_ptr<ApplicationSettings> instance;

	short windowHeight;

	short windowWidth;

	std::string windowTitle;
};


