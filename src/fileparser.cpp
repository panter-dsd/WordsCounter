/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QFile>

#include "fileparser.h"

FileParser::FileParser (QObject *parent)
	: QObject (parent)
	, file_ (new QFile)
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

