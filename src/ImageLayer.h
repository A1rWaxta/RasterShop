//
// Created by waxta on 24.11.19.
//

#pragma once


#include <QtGui/QImage>
#include <QtWidgets/QGraphicsItem>

class ImageLayer : public QGraphicsItem
{
public:
	explicit ImageLayer(QString& layerIdentifier, QGraphicsItem* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void AddDrawable(QGraphicsItem* item);

	[[nodiscard]] QRectF boundingRect() const override;

private:
	QVector<QGraphicsItem*> drawableList;

	QString layerIdentifier;
};


