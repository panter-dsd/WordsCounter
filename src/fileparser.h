/**
 * @author PanteR
 * @date 10.02.2013
 */

#pragma once

#include <QtCore/qobject.h>

class FileParser : public QObject
{
	Q_OBJECT

public:
	explicit FileParser (QObject *parent = 0);
	virtual ~FileParser ();

	QString fileName () const {
		return fileName_;
	}
	void setFileName (const QString &fileName) {
		fileName_ = fileName;
	}

Q_SIGNALS:
	void wordFound (const QString &word);

private:
	Q_DISABLE_COPY (FileParser)

private:
	QString fileName_;
};
