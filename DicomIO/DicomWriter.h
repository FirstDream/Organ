#pragma once

#include <QObject>


/*
���� dcm �ļ�;
ͼƬ, buffer�� to dcm;
�޸ı༭ dcm;
*/

class DicomWriter : public QObject
{
	Q_OBJECT

public:
	DicomWriter(QObject *parent);
	~DicomWriter();
};
