//
// Created by waxta on 1/1/20.
//

#pragma once

#include <ImageLayer.h>
#include <vector>

namespace LayerSystem
{
	class Model
	{
	public:


	private:
		ImageLayer* activeLayer;
		std::vector<ImageLayer*> layerStack;
	};
}