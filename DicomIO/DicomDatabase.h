#pragma once

#include <QObject>

enum DICOM_LEVEL
{
	DICOM_PATIENT,
	DICOM_STUDY,
	DICOM_SERIES,
	DICOM_IMAGE
};

class DicomDatabase : public QObject
{
	Q_OBJECT
public:
	DicomDatabase(QObject *parent);
	~DicomDatabase();
};
