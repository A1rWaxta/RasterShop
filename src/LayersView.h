#pragma once

#include <QWidget>

namespace Ui {
class LayersView;
}

class LayersView : public QWidget
{
    Q_OBJECT

	enum class LayerMoveDirection
	{
		Up,
		Down
	};

public:
    explicit LayersView(QWidget *parent = nullptr);
    ~LayersView();
    void EnableButtons();
    void DisableButtons();

private slots:
	void CreateLayer();
	void DeleteLayer();
	void MoveLayer(LayerMoveDirection direction);

private:
    Ui::LayersView *ui;
};