/*
π‹¿ÌScene
*/

#pragma once

#include <QObject>

class RenderWindow : public QObject
{
	Q_OBJECT

public:
	RenderWindow(QObject *parent);
	~RenderWindow();
};
