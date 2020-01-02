//
// Created by waxta on 1/1/20.
//

#pragma once

#include <ImageLayer.h>
#include <vector>
#include "View.h"

namespace LayerSystem
{
	class Model
	{
	public:
		Model();
		void DeleteImageLayer();
		void MoveActiveLayer(LayerMoveDirection direction);
		void CreateImageLayer();
		void AttachView(View* view);

	private:
		ImageLayer* activeLayer;
		std::vector<ImageLayer*> layerStack;
		View* view;
	};
}