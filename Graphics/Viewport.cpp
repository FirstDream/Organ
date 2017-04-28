#include "Viewport.h"



Viewport::Viewport(QObject* parent)
{
}


Viewport::~Viewport()
{
}

void Viewport::setViewport(int x, int y, int w, int h)
{
	this->viewport_ = glm::vec4(x, y, w, h);
}

glm::vec2 Viewport::screenToViewport(const glm::vec2 & screenPos)
{
	glm::dvec2 viewportPos;

	viewportPos.x = screenPos.x - this->viewport_.x;
	viewportPos.y = screenPos.y - this->viewport_.y;

	return viewportPos;
}

glm::vec2 Viewport::viewportToScreen(const glm::vec2 & viewportPos)
{
	glm::dvec2 screenPos;

	screenPos.x = viewportPos.x + this->viewport_.x;
	screenPos.y = viewportPos.y + this->viewport_.y;

	return screenPos;
}


glm::vec2 Viewport::normalizeViewportPos(const glm::vec2& viewportPos)
{
	glm::vec2 norm;

	norm.x = (viewportPos.x - viewport_.x) / viewport_.z;
	norm.y = (viewportPos.y - viewport_.y) / viewport_.w;

	return norm;
}
