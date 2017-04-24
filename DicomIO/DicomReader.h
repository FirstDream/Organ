#pragma once

#include <QObject>

/*
解析 dcm 文件， 以及 save 成图片格式;
*/
class DicomReader : public QObject
{
	Q_OBJECT

public:
	DicomReader(QObject *parent);
	~DicomReader();
};
