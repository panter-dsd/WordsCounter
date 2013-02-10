/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QRegExp>
#include <QtCore/QDebug>

#include "fileparser.h"

FileParser::FileParser (QObject *parent)
	: QObject (parent)
	, file_ (new QFile)
	, running_ (false)
{

}

FileParser::~FileParser()
{

}

QString FileParser::fileName() const
{
	return file_->fileName ();
}

void FileParser::setFileName (const QString &fileName)
{
	file_->setFileName (fileName);
	emit progress (0, file_->size ());
}

int FileParser::size () const
{
	return file_->size ();
}

QString FileParser::lastError() const
{
	return file_->errorString ();
}

bool FileParser::open()
{
	return file_->open (QIODevice::ReadOnly);
}

void FileParser::start()
{
	if (running_) {
		return;
	}

	running_ = true;

	QTextStream stream (file_.get ());
	stream.setCodec ("Windows-1251");

	const QRegExp re ("[A-Z,a-z]*");

	while (running_) {
		const QString line = stream.readLine ();

		int pos = 0;

		while ( (pos = re.indexIn (line, pos)) != -1) {
			const int wordSize = re.matchedLength ();
			emit wordFound (line.mid (pos, wordSize));
			qDebug () << line.mid (pos, wordSize);
			pos += wordSize;
		}
	}
}

void FileParser::stop()
{
	running_ = false;
}

