#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(QObject *parent)
	: QObject(parent)
{
}

Camera::~Camera()
{
}

bool Camera::viewportToWorld(const glm::vec3 & win, glm::vec3 & world)
{
	//此处计算逆矩阵应该判断逆矩阵是否存在！
	glm::mat4 Inverse = glm::inverse(this->m_projection_ * this->m_view_);

	//这个viewport 可以去掉，默认认为传入的坐标已经归一化;
	glm::vec4 viewport(0, 0, 1, 1);
	glm::vec4 tmp = glm::vec4(win, wClip_);

	tmp[0] = (tmp[0] - viewport[0]) / viewport[2];
	tmp[1] = (tmp[1] - viewport[1]) / viewport[3];
	tmp[2] = (tmp[2] - zNear_) / (zFar_ - zNear_);
	
	//映射到 (-1, 1);
	tmp = tmp * 2.0f - 1.0f;
	
	glm::vec4 obj = Inverse * tmp;
	if (obj.w == 0.0f )
	{
		return false;
	}

	obj /= obj.w;

	world = obj;

	return true;
}

bool Camera::worldToViewport(const glm::vec3 & world, glm::vec3 & viewport)
{

	glm::vec4 tmp(world, 1.0f);
	tmp = this->m_view_ * tmp;
	tmp = this->m_projection_ * tmp;

	if (tmp.w == 0.0f)
	{
		return false;
	}

	tmp /= tmp.w;

	tmp = tmp * 0.5f + 0.5f;

	viewport = tmp;

	return true;
}
