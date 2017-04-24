#pragma once

#include <QObject>


/*
创建 dcm 文件;
图片, buffer等 to dcm;
修改编辑 dcm;
*/

class DicomWriter : public QObject
{
	Q_OBJECT

public:
	DicomWriter(QObject *parent);
	~DicomWriter();
};
