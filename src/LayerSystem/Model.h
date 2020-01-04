//
// Created by waxta on 1/1/20.
//

#pragma once

#include <ImageLayer.h>
#include <vector>
#include "View.h"
#include "Globals.h"

namespace LayerSystem
{
	class View;

	class Model
	{
	public:
		Model();
		void DeleteActiveLayer();
		void MoveActiveLayer(LayerMoveDirection moveDirection);
		void CreateLayer();
		void AttachView(View* view);
		std::vector<ImageLayer*> GetLayers();

	private:
		ImageLayer* activeLayer;
		std::vector<ImageLayer*> layerStack;
		View* view;
	};
}