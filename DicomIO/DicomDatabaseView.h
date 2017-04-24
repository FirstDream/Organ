#pragma once

#include <QTreeView>

#include "DicomDatabase.h"

/*
UIչʾDicomDatabase����;
TreeView;
*/

class DicomDatabseView : public QTreeView
{
	Q_OBJECT

public:
	DicomDatabseView(QWidget *parent = Q_NULLPTR);
	~DicomDatabseView();



	//������ʾ����
	void setLevel(DICOM_LEVEL min_level, DICOM_LEVEL max_level);


private:

};
