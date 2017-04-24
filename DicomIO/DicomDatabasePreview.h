#pragma once

#include <QListView>

#include "DicomDatabase.h"
/*
预览 DicomDatabase 中的某一级别（缩略图）
ListView
*/

class DicomDatabasePreview : public QListView
{
	Q_OBJECT

public:
	DicomDatabasePreview(QWidget *parent = Q_NULLPTR);
	~DicomDatabasePreview();

	//设置model;
	void setDicomDatabase(DicomDatabase* database);

	//设置显示级别;
	void setLevel(DICOM_LEVEL level);

private:

};
