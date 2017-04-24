#pragma once

#include <QListView>

#include "DicomDatabase.h"
/*
Ԥ�� DicomDatabase �е�ĳһ��������ͼ��
ListView
*/

class DicomDatabasePreview : public QListView
{
	Q_OBJECT

public:
	DicomDatabasePreview(QWidget *parent = Q_NULLPTR);
	~DicomDatabasePreview();

	//����model;
	void setDicomDatabase(DicomDatabase* database);

	//������ʾ����;
	void setLevel(DICOM_LEVEL level);

private:

};
