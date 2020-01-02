//
// Created by waxta on 1/1/20.
//

#include "View.h"

using LayerSystem::View;

View::View()
{
	auto scrollAreaWidget = new QWidget();
	setWidget(scrollAreaWidget); //becomes a child
	layout = new QVBoxLayout(widget());
}

void View::Update()
{

}