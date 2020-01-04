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
	explicit LayerPreview(QWidget* parent = nullptr);
	~LayerPreview() override;
	void Select();
	void Unselect();
	QString GetLayerName();
	void SetLayerName(QString& name);

signals:
	void Selected(LayerPreview* layer);

private:
	void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
	bool selected;
	Ui::LayerPreview* ui;
};