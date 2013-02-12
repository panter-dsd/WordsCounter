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

	bool isRunning () const {
		return running_;
	}

	QString lastError () const;

	QString fileName () const;
	void setFileName (const QString &fileName);

	int size () const;

Q_SIGNALS:
	void wordFound (const QString &word);
	void progress (int current, int total);
	void started ();
	void finished ();

public Q_SLOTS:
	void start ();
	void stop ();

private:
	Q_DISABLE_COPY (FileParser)

	void parseLine (const char *const data, int dataSize);

private:
	bool running_;
	QString fileName_;
	QString lastError_;
};
