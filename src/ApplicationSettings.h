//
// Created by waxta on 05.09.19.
//

#pragma once

#include <memory>

class ApplicationSetting
{
public:
	static ApplicationSetting * Instance();

private:
	ApplicationSetting();
	static std::unique_ptr<ApplicationSetting> instance;
};


