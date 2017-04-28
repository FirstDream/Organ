/*
表示一个变换矩阵;
线性变换：
平移缩放旋转。
*/


#pragma once

#include <QObject>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

class Transform : public QObject
{
	Q_OBJECT

public:
	Transform(QObject *parent);
	~Transform();
	



};
