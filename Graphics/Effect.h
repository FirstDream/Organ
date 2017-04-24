/*
´ú±íshader
*/

#pragma once

#include <QObject>

class Effect : public QObject
{
	Q_OBJECT

public:
	Effect(QObject *parent = 0);
	~Effect();

	virtual void use() = 0;
	virtual void unUse() = 0;


private:



};
