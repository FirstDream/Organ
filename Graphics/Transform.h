/*
表示一个变换矩阵;
*/


#pragma once

#include <QObject>

class Transform : public QObject
{
	Q_OBJECT

public:
	Transform(QObject *parent);
	~Transform();

};
