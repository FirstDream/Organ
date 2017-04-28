/*
����ͶӰ����, ����ͼ����;
*/


#pragma once

#include <QObject>

#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera : public QObject
{
	Q_OBJECT
public:
	
	enum PROJECTION_TYPE
	{
		Perspective,
		Ortho
	};

	Camera(QObject *parent = 0);
	virtual ~Camera();
//---------------��������------------------------------
	void setEye( const glm::vec3& eye );
	void setTarget( const glm::vec3& target );
	void setUp( const glm::vec3& up );

	glm::vec3 getEye(){ return this->v_eye_; }
	glm::vec3 getTarget(){ return this->v_target_; }
	glm::vec3 getUp(){ return this->v_up_; }

	//�ƶ� Target, ʹCamera�뽹����� = d;
	void setDistance(float d); 
	float getDistance(){ return this->distance_; }

	void lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up );

	//ǿ�� up���� ������;
	void orthogonalizeViewUp();

//-----------------------------------------------------------
	//��eye��target�������dolly, �ƶ�eye ;
	void dolly(float value);

	//����Roll��; Roll�ǣ��������ͶӰ(����)�ĽǶ�;
	void setRoll(float angle);
	float getRoll();

	//��ͶӰ(����)������ת���;
	void roll( float angle );
	//�� Target Ϊ������ת�� up ������תEye;
	void azimuth(float angle);
	//�� Eye Ϊ������ת�� up ������תTarget;
	void yaw(float angle);

	//�� Target Ϊ������ת�� ͶӰ��������up�Ĳ�˷��� ��תEye;
	void elevation( float angle );
	//�� Eye Ϊ������ת�� ͶӰ������up�Ĳ�˷��� ��תTarget;
	void pitch( float angle );
	
	//���Ա任;
	void applyViewTransfrom( const glm::mat4& transform_mat );

//--------------------------------------------------	

	//����ͶӰ�任;
	//͸��ͶӰ1:
	void setFrustum(float left, float right, float bottom, float top, float near = 0.1f, float far = 10000.0f);
	//͸��ͶӰ2��(fovy:����, aspect:��ƽ��width/height);
	void setPerspective(float fovy, float aspect, float near = 0.1f, float far = 10000.0f);
	//����ͶӰ��
	void setOrtho(float left, float right, float bottom, float top, float near = 0.1f, float far = 10000.0f);

	//��������;����ͶӰʱ:�޸�ͶӰ������ ͸��ͶӰ�� �޸�fovy��;
	void zoom(double amount);
	void setFovy(float fovyDegrees);

//---------------------------------------------------
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

//---------------------------------------------------
	//ע�⣺��������ת���е�Viewport�����꣨x, y�����ǹ�һ���� (0, 1)�ϵ�
	//����õ���ȷ����,Ӧ��x * w + x0; y * h + y0;
	bool viewportToWorld(const glm::vec3 & viewport, glm::vec3 & world);
	bool worldToViewport(const glm::vec3 & world, glm::vec3 & viewport);


protected:
	//���¼���m_view_����;
	void computeViewMatrix();
	void computeDistance();
	void computeProjectionMatrix();


	//��ȡ�����;
	glm::vec3 getOriention();

	void modified();
private:

	//���������λ��, ����, �Ϸ���;
	glm::vec3 v_eye_;
	glm::vec3 v_target_;
	glm::vec3 v_up_;

	glm::vec3 v_projection_direction_;

	float distance_;

	//����
	glm::mat4 m_view_;
	glm::mat4 m_projection_;

	//��ʱ����;
	glm::mat4 m_transform_;

	//��ת��
	//glm::quat q_rotate_;

	//---------------------
	//ͶӰ������
	float perspective_fovy_radians_;
	float perspective_aspect_;
	float z_near_;
	float z_far_;

	float ortho_left_;
	float ortho_right_;
	float ortho_top_;
	float ortho_bottom_;

	float ortho_scale_;
	//--------------------

	bool modified_;

	//
	int projection_type_;

	//w����ü� Ĭ�� = 1;
	float wClip_;


};

