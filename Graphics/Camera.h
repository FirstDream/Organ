/*
�۲����;
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
	//����ͶӰ�任;
	//͸��ͶӰ1:
	void setFrustum(float left, float right, float bottom, float top, float near = 0.1f, float far = 10000.0f);
	//͸��ͶӰ2��
	void setPerspective(float fovy, float aspect, float near = 0.1f, float far = 10000.0f);
	//����ͶӰ��
	void setOrtho(float left, float right, float bottom, float top, float near = 0.1f, float far = 10000.0f);
//-----------------------------

	//ע�⣺��������ת���е�Viewport�����꣨x, y�����ǹ�һ���� (0, 1)�ϵ�
	//����õ���ȷ����,Ӧ��x * w + x0; y * h + y0;
	bool viewportToWorld(const glm::vec3& viewport, glm::vec3& world);
	bool worldToViewport(const glm::vec3& world, glm::vec3& viewport);
private:
	
	
	glm::mat4 m_projection_;
	glm::mat4 m_view_;

	//z�ü�ƽ��.Ĭ��zNear = 0, zFar = 1;
	//���������ֵ������glDepthRange()���õģ���ͬ�������ͶӰ�����Զ��ƽ�棬���˴���ȷ�������迴�ĵ���
	float zNear_;
	float zFar_;

	//w����ü� Ĭ�� = 1;
	float wClip_;
};
