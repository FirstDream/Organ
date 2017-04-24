#pragma once

#include <QObject>

#include <glm/fwd.hpp>

class Viewport : public QObject
{
	Q_OBJECT

public:
	Viewport(QObject* parent = 0);
	~Viewport();

	void setViewport(int x, int y, int w, int h);


private:

	glm::vec4 viewport_;

};

