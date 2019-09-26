//
// Created by waxta on 05.09.19.
//

#include "ApplicationSetting.h"

ApplicationSetting ApplicationSetting::Instance()
{
	if(instance == 0)
	{
		instance = std::make_unique<ApplicationSetting>();
	}
	return instance.;
}
