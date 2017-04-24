#pragma once

#include <QAbstractItemModel>
#include <QPointer>

#include "DicomDatabase.h"

class DicomDatabaseModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	DicomDatabaseModel(QObject *parent = 0);
	~DicomDatabaseModel();

	void setDatabase(DicomDatabase* database);

private:

	QPointer<DicomDatabase> dicom_database_;
};
