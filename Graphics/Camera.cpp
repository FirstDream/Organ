#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/orthonormalize.hpp> 

#include <math.h>

#include <QtDebug>


Camera::Camera(QObject *parent)
{
	wClip_ = 1.0;
}


Camera::~Camera()
{
}

void Camera::setEye(const glm::vec3& eye)
{
	if (this->v_eye_ == eye )
	{
		return;
	}

	this->v_eye_ = eye;
	
	//qDebug() << "Eye Pos setting to ( " << QString::number( eye.x ) << QString::number( eye.x ) << QString::number( eye.x ) <<" )";
	
	this->computeViewMatrix();
	this->computeDistance();

}

void Camera::setTarget(const glm::vec3& target)
{
	if (this->v_target_ == target )
	{
		return;
	}
	this->v_target_ = target;

	this->computeViewMatrix();
	this->computeDistance();
	this->modified();

}

void Camera::setUp(const glm::vec3& up)
{
	glm::vec3 norm;

	if ( glm::length( up ) == 0 )
	{
		norm = glm::vec3(0.0, 1.0, 0.0);
	}
	else
	{
		norm = glm::normalize(up);
	}

	if ( this->v_up_ == norm)
	{
		return;
	}

	this->v_up_ = norm;

	this->computeViewMatrix();
	this->computeDistance();
	this->modified();
}

void Camera::setDistance(float d)
{
	if (distance_ == d)
	{
		return;
	}
	
	distance_ = d;

	if (d < 0.0002)
	{
		distance_  = 0.0002;
	}

	this->v_target_ = this->v_projection_direction_ * this->distance_;

	this->computeViewMatrix();
	this->modified();

}

void Camera::lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	this->v_eye_ = eye;
	this->v_target_ = target;
	this->v_up_ = up;

	this->computeViewMatrix();
	this->computeDistance();
}

void Camera::orthogonalizeViewUp()
{
	this->v_up_[0] = this->m_view_[0][1];
	this->v_up_[1] = this->m_view_[1][1];
	this->v_up_[2] = this->m_view_[2][1];

	this->modified();
}

void Camera::dolly(float value)
{
	if ( value <= 0 )
	{
		return;
	}

	float d = distance_/value;

	glm::vec3 new_eye = this->v_target_ - d * this->v_projection_direction_;

	this->setEye( new_eye );
}

void Camera::setRoll(float angle)
{
	angle -= this->getRoll();
	if ( fabs(angle) < 0.00001 )
	{
		return;
	}

	this->roll(angle);
}

float Camera::getRoll()
{
	glm::vec3 orien = this->getOriention();

	return orien[2];
}

void Camera::roll(float angle)
{
	float rad = glm::radians(angle);

	this->m_transform_ = glm::mat4(1.0);

	this->m_transform_ = glm::rotate(this->m_transform_, rad, this->v_projection_direction_);

	glm::vec4 newUp = this->m_transform_ * glm::vec4( this->v_up_, 1.0 );

	newUp /= newUp[3];


	this->setUp(newUp);
}

void Camera::azimuth(float angle)
{
	float rad = glm::radians(angle);
	this->m_transform_ = glm::mat4(1.0);
	this->m_transform_ = glm::translate(this->m_transform_, this->v_target_ );
	this->m_transform_ = glm::rotate(this->m_transform_, rad, this->v_up_);
	this->m_transform_ = glm::translate(this->m_transform_, -this->v_target_);

	glm::vec4 newEye =  this->m_transform_ * glm::vec4(this->v_eye_, 1.0);
	newEye /= newEye[3];

	this->setEye( newEye );

}

void Camera::yaw(float angle)
{
	float rad = glm::radians(angle);

	glm::vec4 newTarget( this->v_target_, 1.0 );

	this->m_transform_ = glm::mat4(1.0);
	this->m_transform_ = glm::translate(this->m_transform_, this->v_eye_ );
	this->m_transform_ = glm::rotate(this->m_transform_, rad, this->v_up_);
	this->m_transform_ = glm::translate(this->m_transform_, -this->v_eye_);

	newTarget = this->m_transform_ * newTarget;
	newTarget /= newTarget[3];

	this->setTarget( glm::vec3(newTarget) );

}

void Camera::elevation(float angle)
{

	float rad = glm::radians(angle);
	glm::vec3 axis, savedUp;
	
	axis[0] = -this->m_view_[0][0];
	axis[1] = -this->m_view_[1][0];
	axis[2] = -this->m_view_[2][0];

	savedUp = this->v_up_;

	this->m_transform_ = glm::mat4(1.0);
	this->m_transform_ = glm::rotate(this->m_transform_, rad, axis);
	glm::vec4 up = this->m_transform_ * glm::vec4(v_up_, 1.0);
	up /= up[3];
	this->v_up_ = up;
	this->m_transform_ = glm::mat4(1.0);
	
	this->m_transform_ = glm::translate(m_transform_, this->v_target_);
	this->m_transform_ = glm::rotate(m_transform_, rad, axis);
	this->m_transform_ = glm::translate(m_transform_, -this->v_target_);

	glm::vec4 newEye =  this->m_transform_ *  glm::vec4(v_eye_, 1.0);
	newEye /= newEye[3];

	this->setEye( newEye );

	this->v_up_ = savedUp;
}

void Camera::pitch(float angle)
{
	float rad = glm::radians(angle);

	glm::vec3 axis, savedUp;

	axis[0] = this->m_view_[0][0];
	axis[1] = this->m_view_[1][0];
	axis[2] = this->m_view_[2][0];

	savedUp = this->v_up_;


	this->m_transform_ = glm::mat4(1.0);
	this->m_transform_ = glm::rotate(this->m_transform_, rad, axis);
	glm::vec4 up = this->m_transform_ * glm::vec4(v_up_, 1.0);
	up /= up[3];
	this->v_up_ = up;
	this->m_transform_ = glm::mat4(1.0);

	this->m_transform_ = glm::translate(m_transform_, this->v_eye_);
	this->m_transform_ = glm::rotate(m_transform_, rad, axis);
	this->m_transform_ = glm::translate(m_transform_, -this->v_eye_);

	glm::vec4 newTarget = this->m_transform_ * glm::vec4(v_target_, 1.0);
	newTarget /= newTarget[3];

	this->setTarget( newTarget );

	this->v_up_ = savedUp;
}

void Camera::zoom(double amount)
{
	if (amount <= 0.0)
	{
		return;
	}
	//todo
 	if (projection_type_ == Camera::Ortho )
 	{
 		this->ortho_scale_ /= amount;

		this->ortho_left_ *= this->ortho_scale_;
		this->ortho_right_ *= this->ortho_scale_;
		this->ortho_top_ *= this->ortho_scale_;
		this->ortho_bottom_ *= this->ortho_scale_;

		this->computeViewMatrix();
 	}
 	else
 	{
 		this->setFovy(this->perspective_fovy_radians_ / amount);
 	}


}

void Camera::setFovy(float fovyDegrees)
{
	this->perspective_fovy_radians_ = glm::radians(fovyDegrees);
	this->computeProjectionMatrix();
}

void Camera::applyViewTransfrom(const glm::mat4& transform_mat)
{
	glm::vec4 eyeOld( this->v_eye_, 1.0 );
	glm::vec4 targetOld(this->v_target_, 1.0);
	glm::vec4 upOld(this->v_up_, 1.0);

	upOld[0] += eyeOld[0];
	upOld[1] += eyeOld[1];
	upOld[2] += eyeOld[2];

	glm::vec4 eyeNew = transform_mat * eyeOld;
	glm::vec4 targetNew = transform_mat * targetOld;
	glm::vec4 upNew = transform_mat * upNew;

	upNew[0] -= eyeNew[0];
	upNew[1] -= eyeNew[1];
	upNew[2] -= eyeNew[2];

	this->lookAt(eyeNew, targetNew, upNew);
}

void Camera::setFrustum(float left, float right, float bottom, float top, float near /*= 0.1f*/, float far /*= 10000.0f*/)
{
	//弃用！
	//this->projection_type_ = Camera::Perspective;
	//this->m_projection_ = glm::frustum(left, right, bottom, top, near, far);
	
}

void Camera::setPerspective(float fovy, float aspect, float near /*= 0.1f*/, float far /*= 10000.0f*/)
{
	this->projection_type_ = Camera::Perspective;

	this->perspective_fovy_radians_ = glm::radians(fovy);
	this->computeProjectionMatrix();
}

void Camera::setOrtho(float left, float right, float bottom, float top, float near /*= 0.1f*/, float far /*= 10000.0f*/)
{
	this->projection_type_ = Camera::Ortho;

	this->m_projection_ = glm::ortho(left, right, bottom, top, near, far);
	this->computeProjectionMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
	return this->m_view_;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return this->m_projection_;
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
	tmp[2] = (tmp[2] - z_near_) / (z_far_ - z_near_);

	//映射到 (-1, 1);
	tmp = tmp * 2.0f - 1.0f;

	glm::vec4 obj = Inverse * tmp;
	if (obj.w == 0.0f)
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

void Camera::computeViewMatrix()
{
	this->m_view_ = glm::lookAt( this->v_eye_, this->v_target_, this->v_up_ );
}

void Camera::computeDistance()
{
	this->distance_ = glm::distance(this->v_target_, this->v_eye_);

	if (distance_ < 1e-20 )
	{
		this->distance_ = 1e-20;
		this->v_target_ = v_eye_ + v_projection_direction_ * distance_;
	}

	this->v_projection_direction_ = glm::normalize( this->v_target_ - this->v_eye_ );

}

void Camera::computeProjectionMatrix()
{
	if (this->projection_type_ == Camera::Perspective)
	{
		this->m_projection_ = glm::perspective( perspective_fovy_radians_, perspective_aspect_, z_near_, z_far_);
	}
	else
	{
		this->m_projection_ = glm::ortho(ortho_left_, ortho_right_, ortho_bottom_, ortho_top_, z_near_, z_far_);
	}
}

glm::vec3 Camera::getOriention()
{
#define AXIS_EPSILON 0.001
#define ORTHO_EPSILON 4e-16

	glm::vec3 orientation;

	int i;

	glm::mat3x3 ortho;

	for (i = 0; i < 3; i++)
	{
		ortho[0][i] = this->m_view_[0][i];
		ortho[1][i] = this->m_view_[1][i];
		ortho[2][i] = this->m_view_[2][i];
	}
	if (glm::determinant(ortho) < 0)
	{
		ortho[0][2] = -ortho[0][2];
		ortho[1][2] = -ortho[1][2];
		ortho[2][2] = -ortho[2][2];
	}

	// Check whether matrix is orthogonal
	float r1 = glm::dot(ortho[0],ortho[1]);
	float r2 = glm::dot(ortho[0],ortho[2]);
	float r3 = glm::dot(ortho[1],ortho[2]);

	// Orthogonalize the matrix if it isn't already orthogonal
	if ((r1*r1) + (r2*r2) + (r3*r3) > (ORTHO_EPSILON * ORTHO_EPSILON))
	{
		glm::orthonormalize(ortho);
	}

	// first rotate about y axis
	double x2 = ortho[2][0];
	double y2 = ortho[2][1];
	double z2 = ortho[2][2];

	double x3 = ortho[1][0];
	double y3 = ortho[1][1];
	double z3 = ortho[1][2];

	double d1 = sqrt(x2*x2 + z2*z2);

	double cosTheta, sinTheta;
	if (d1 < AXIS_EPSILON)
	{
		cosTheta = 1.0;
		sinTheta = 0.0;
	}
	else
	{
		cosTheta = z2/d1;
		sinTheta = x2/d1;
	}

	double theta = atan2(sinTheta, cosTheta);
	orientation[1] = - glm::degrees( theta );

	// now rotate about x axis
	double d = sqrt(x2*x2 + y2*y2 + z2*z2);

	double sinPhi, cosPhi;
	if (d < AXIS_EPSILON)
	{
		sinPhi = 0.0;
		cosPhi = 1.0;
	}
	else if (d1 < AXIS_EPSILON)
	{
		sinPhi = y2/d;
		cosPhi = z2/d;
	}
	else
	{
		sinPhi = y2/d;
		cosPhi = (x2*x2 + z2*z2)/(d1*d);
	}

	double phi = atan2(sinPhi, cosPhi);
	orientation[0] = glm::degrees( phi );

	// finally, rotate about z
	double x3p = x3*cosTheta - z3*sinTheta;
	double y3p = - sinPhi*sinTheta*x3 + cosPhi*y3 - sinPhi*cosTheta*z3;
	double d2 = sqrt(x3p*x3p + y3p*y3p);

	double cosAlpha, sinAlpha;
	if (d2 < AXIS_EPSILON)
	{
		cosAlpha = 1.0;
		sinAlpha = 0.0;
	}
	else
	{
		cosAlpha = y3p/d2;
		sinAlpha = x3p/d2;
	}

	double alpha = atan2(sinAlpha, cosAlpha);
	orientation[2] = glm::degrees( alpha );

	return orientation;
}

void Camera::modified()
{
}

