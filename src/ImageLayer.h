//
// Created by waxta on 24.11.19.
//

#pragma once

#include <QtGui/QImage>
#include <QtWidgets/QGraphicsItem>

class ImageLayer : public QGraphicsRectItem
{
public:
	explicit ImageLayer();
	~ImageLayer() override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	void AddDrawableItem(QGraphicsItem* item);
	[[nodiscard]] QRectF boundingRect() const override;

private:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	bool mouseLeftButtonPressed;
	QVector<QGraphicsItem*> drawableList;
	QGraphicsRectItem* item;
};