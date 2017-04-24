/*
表示一个渲染场景;
*/

#pragma once

#include <QObject>
#include <QPointer>

#include "Viewport.h"

class Camera;

class Scene : public Viewport
{
	Q_OBJECT

public:
	Scene(QObject *parent = 0);
	~Scene();

private:

	QPointer<Camera> camera_;


};
