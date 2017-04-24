#pragma once

#include <QWidget>

class Canvas : public QWidget
{
	Q_OBJECT

public:
	Canvas(QWidget *parent = Q_NULLPTR);
	~Canvas();

};
