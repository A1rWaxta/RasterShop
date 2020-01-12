//
// Created by waxta on 11.01.20.
//

#include <QtGui/QFont>
#include "TextTool.h"
#include <QInputMethodEvent>
#include <QDebug>
#include <QTextCursor>

TextTool::TextTool() : layer(nullptr)
{
	QFont font("Times", 10, QFont::Bold);
	setFont(font);
	setFlag(QGraphicsItem::ItemIsFocusable, true);
	setTextInteractionFlags(Qt::TextEditorInteraction);
	setPos(mapToScene(25, 25));
	setTextWidth(75);
}

void TextTool::SetLayer(ImageLayer* layer)
{
	this->layer = layer;
}

void TextTool::Start(QPointF point)
{
//	setTextWidth(layer->boundingRect().left() - point.x());
//	setPos(point);
}

void TextTool::keyPressEvent(QKeyEvent* event)
{
	int keyCode = event->key();
	QString currentText = toPlainText();
	QTextCursor cursor = textCursor();
	int cursorPos = cursor.position();

	if( keyCode == Qt::Key_Shift )
	{
		return;
	}

	int start = textCursor().selectionStart();
	int end = textCursor().selectionEnd();
	currentText.remove(start, end - start);

	if( keyCode == Qt::Key_Delete )
	{
		currentText.remove(cursor.position(), 1);
	}

	if(keyCode == Qt::Key_Return)
	{
		currentText.insert(cursorPos, '\n');
		cursorPos++;
	}

	if( keyCode == Qt::Key_Backspace and cursor.position() != 0 )
	{
		currentText.remove(cursor.position() - 1, 1);
		cursorPos--;
	}

	if( event->modifiers() == Qt::ShiftModifier and keyCode >= 65 and keyCode <= 90 )
	{
		currentText.insert(cursor.position(), keyCode);
		cursorPos++;
	}
	else if( event->modifiers() != Qt::ShiftModifier and keyCode >= 65 and keyCode <= 90 )
	{
		currentText.insert(cursor.position(), keyCode + 32);
		cursorPos++;
	}

	if( keyCode >= 32 and keyCode <= 64 or keyCode >= 91 and keyCode <= 96 or keyCode >= 123 and keyCode <= 126 )
	{
		currentText.insert(cursor.position(), keyCode);
		cursorPos++;
	}

	setPlainText(currentText);
	cursor.setPosition(cursorPos);
	setTextCursor(cursor);
}

void TextTool::focusInEvent(QFocusEvent* event)
{
	qDebug() << "otrzymalem focusa";
}
