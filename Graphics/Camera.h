/*
管理投影矩阵, 和视图矩阵;
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
//---------------基本操作------------------------------
	void setEye( const glm::vec3& eye );
	void setTarget( const glm::vec3& target );
	void setUp( const glm::vec3& up );

	glm::vec3 getEye(){ return this->v_eye_; }
	glm::vec3 getTarget(){ return this->v_target_; }
	glm::vec3 getUp(){ return this->v_up_; }

	//移动 Target, 使Camera与焦点距离 = d;
	void setDistance(float d); 
	float getDistance(){ return this->distance_; }

	void lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up );

	//强制 up向量 正交化;
	void orthogonalizeViewUp();

//-----------------------------------------------------------
	//将eye与target距离除以dolly, 移动eye ;
	void dolly(float value);

	//设置Roll角; Roll角：相机关于投影(视线)的角度;
	void setRoll(float angle);
	float getRoll();

	//沿投影(视线)方向旋转相机;
	void roll( float angle );
	//以 Target 为中心旋转绕 up 方向旋转Eye;
	void azimuth(float angle);
	//以 Eye 为中心旋转绕 up 方向旋转Target;
	void yaw(float angle);

	//以 Target 为中心旋转绕 投影方向反向与up的叉乘方向 旋转Eye;
	void elevation( float angle );
	//以 Eye 为中心旋转绕 投影方向与up的叉乘方向 旋转Target;
	void pitch( float angle );
	
	//线性变换;
	void applyViewTransfrom( const glm::mat4& transform_mat );

//--------------------------------------------------	

	//设置投影变换;
	//透视投影1:
	void setFrustum(float left, float right, float bottom, float top, float near = 0.1f, float far = 10000.0f);
	//透视投影2：(fovy:弧度, aspect:近平面width/height);
	void setPerspective(float fovy, float aspect, float near = 0.1f, float far = 10000.0f);
	//正交投影：
	void setOrtho(float left, float right, float bottom, float top, float near = 0.1f, float far = 10000.0f);

	//缩放因子;正交投影时:修改投影参数， 透视投影， 修改fovy角;
	void zoom(double amount);
	void setFovy(float fovyDegrees);

//---------------------------------------------------
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

//---------------------------------------------------
	//注意：以下坐标转换中的Viewport下坐标（x, y）都是归一化到 (0, 1)上的
	//如需得到正确坐标,应：x * w + x0; y * h + y0;
	bool viewportToWorld(const glm::vec3 & viewport, glm::vec3 & world);
	bool worldToViewport(const glm::vec3 & world, glm::vec3 & viewport);


protected:
	//重新计算m_view_矩阵;
	void computeViewMatrix();
	void computeDistance();
	void computeProjectionMatrix();


	//获取方向角;
	glm::vec3 getOriention();

	void modified();
private:

	//向量：相机位置, 焦点, 上方向;
	glm::vec3 v_eye_;
	glm::vec3 v_target_;
	glm::vec3 v_up_;

	glm::vec3 v_projection_direction_;

	float distance_;

	//矩阵：
	glm::mat4 m_view_;
	glm::mat4 m_projection_;

	//临时矩阵;
	glm::mat4 m_transform_;

	//旋转：
	//glm::quat q_rotate_;

	//---------------------
	//投影参数：
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

	//w坐标裁剪 默认 = 1;
	float wClip_;


};

