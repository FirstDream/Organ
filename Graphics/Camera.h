/*
观察相机;
*/


#pragma once

#include <QObject>

#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>

class Camera : public QObject
{
	Q_OBJECT

public:
	Camera(QObject *parent = 0);
	~Camera();

	void updateMatrix();

	void setEye(glm::vec3& eye);
	void setTarget(glm::vec3& target);
	void setUp(glm::vec3& up);


//-----------------------------
	//设置投影变换;
	//透视投影1:
	void setFrustum(float left, float right, float bottom, float top, float near = 0.1f, float far = 10000.0f);
	//透视投影2：
	void setPerspective(float fovy, float aspect, float near = 0.1f, float far = 10000.0f);
	//正交投影：
	void setOrtho(float left, float right, float bottom, float top, float near = 0.1f, float far = 10000.0f);
//-----------------------------

	//注意：以下坐标转换中的Viewport下坐标（x, y）都是归一化到 (0, 1)上的
	//如需得到正确坐标,应：x * w + x0; y * h + y0;
	bool viewportToWorld(const glm::vec3& viewport, glm::vec3& world);
	bool worldToViewport(const glm::vec3& world, glm::vec3& viewport);
private:
	
	
	glm::mat4 m_projection_;
	glm::mat4 m_view_;

	//z裁剪平面.默认zNear = 0, zFar = 1;
	//这里的两个值可能是glDepthRange()设置的，不同于上面的投影矩阵的远近平面，（此处不确定，还需看文档）
	float zNear_;
	float zFar_;

	//w坐标裁剪 默认 = 1;
	float wClip_;
};
