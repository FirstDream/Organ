#pragma once

#include <QTreeView>

#include "DicomDatabase.h"

/*
UI展示DicomDatabase内容;
TreeView;
*/

class DicomDatabseView : public QTreeView
{
	Q_OBJECT

public:
	DicomDatabseView(QWidget *parent = Q_NULLPTR);
	~DicomDatabseView();



	//设置显示级别
	void setLevel(DICOM_LEVEL min_level, DICOM_LEVEL max_level);


private:

};
