/**
Actor 表示渲染场景(Scene)中的一个实体;

*/


#pragma once

#include <QObject>
#include <QPointer>
#include <QSharedPointer>


class Effect;
class Transform;

class Actor : public QObject
{
	Q_OBJECT

public:
	Actor(QObject *parent);
	~Actor();

	virtual void render() = 0;

	QSharedPointer<Transform> getTransform() { return this->transform_; }
	void setTransform(QSharedPointer<Transform> trans) { this->transform_ = trans; }

	void setEffect(QSharedPointer<Transform> effect) { effect_ = effect; }


private:
	QSharedPointer<Transform> transform_;
	QSharedPointer<Effect> effect_;

};

