#pragma once

#include <QWidget>

namespace Ui
{
	class LayerPreview;
}

class LayerPreview : public QWidget
{
Q_OBJECT

public:
	explicit LayerPreview(QWidget* parent = nullptr);

	~LayerPreview();

	void SetLayerName(QString& layerName);

private:
	void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

	bool selected;

	Ui::LayerPreview* ui;
};