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
	explicit LayerPreview(ImageLayer* layer, QString& layerIdentifier, QWidget* parent = nullptr);
	~LayerPreview() override;
	ImageLayer* GetLayer();
	void Select();
	void Unselect();
	QString GetLayerName();

signals:
	void Selected(LayerPreview* layer);

private slots:
	void ToggleVisibility();
	void SetOpacity(int i);

private:
	void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
	bool selected;
	ImageLayer* layer;
	Ui::LayerPreview* ui;
};