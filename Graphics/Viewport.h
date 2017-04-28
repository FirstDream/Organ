#pragma once

#include <QObject>

#include <glm/fwd.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

class Viewport : public QObject
{
	Q_OBJECT

public:
	Viewport(QObject* parent = 0);
	~Viewport();

	void setViewport(int x, int y, int w, int h);
	glm::vec4 getViewport() { return this->viewport_; }

	//viewport坐标与Screen坐标互转;
	glm::vec2 screenToViewport(const glm::vec2& screenPos);
	glm::vec2 viewportToScreen(const glm::vec2& viewportPos);

	//将viewport坐标归一化到[0, 1];
	glm::vec2 normalizeViewportPos(const glm::vec2& viewportPos);

private:

	//x, y, w, h;
	glm::vec4 viewport_;

};

