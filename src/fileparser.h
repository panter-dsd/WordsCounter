/**
 * @author PanteR
 * @date 10.02.2013
 */

#pragma once

#include <QtCore/QObject>

#include <auto_ptr.h>

class FileParser : public QObject
{
	Q_OBJECT

public:
	explicit FileParser (QObject *parent = 0);
	virtual ~FileParser ();

	QString fileName () const;
	void setFileName (const QString &fileName);

	int size () const;

Q_SIGNALS:
	void wordFound (const QString &word);
	void progress (int current, int total);
	void finished ();

private:
	Q_DISABLE_COPY (FileParser)

private:
	std::auto_ptr<class QFile> file_;
};
