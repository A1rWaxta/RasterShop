#pragma once

#include <QWidget>
#include "ImageLayer.h"

namespace Ui
{
	class LayerPreview;
}

class LayerPreview : public QWidget
{
Q_OBJECT

public:
	explicit LayerPreview(ImageLayer* layer, QWidget* parent = nullptr);

	~LayerPreview() override;

	ImageLayer* GetLayer();

	void Select();

	void Unselect();

signals:
	void LayerSelected(LayerPreview* layer);

private:
	void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

	bool selected;

	ImageLayer* layer;

	Ui::LayerPreview* ui;
};