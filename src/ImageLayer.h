//
// Created by waxta on 24.11.19.
//

#pragma once


#include <QtGui/QImage>
#include <QtWidgets/QGraphicsItem>

class ImageLayer : public QGraphicsItem
{
public:
	explicit ImageLayer(QString& identifier);

	~ImageLayer() override;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void AddDrawableItem(QGraphicsItem* item);

	[[nodiscard]] QRectF boundingRect() const override;

	QString& GetIdentifier();

	void SetLayerIdentifier(const QString& identifier);

private:
	QVector<QGraphicsItem*> drawableList;

	QString layerIdentifier;
};


