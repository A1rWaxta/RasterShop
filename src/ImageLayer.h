//
// Created by waxta on 24.11.19.
//

#pragma once

#include <QtGui/QImage>
#include <QtWidgets/QGraphicsItem>

class ImageLayer : public QGraphicsRectItem
{
public:
	explicit ImageLayer(QString& identifier);
	~ImageLayer() override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	[[nodiscard]] QRectF boundingRect() const override;
	void SetLayerIdentifier(QString& identifier);
	[[nodiscard]] QString& GetLayerIdentifier();

private:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	bool mouseLeftButtonPressed;
	QString identifier;
	QGraphicsRectItem* item;
};