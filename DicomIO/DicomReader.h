#pragma once

#include <QObject>

/*
���� dcm �ļ��� �Լ� save ��ͼƬ��ʽ;
*/
class DicomReader : public QObject
{
	Q_OBJECT

public:
	DicomReader(QObject *parent);
	~DicomReader();
};
