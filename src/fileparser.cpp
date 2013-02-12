/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QDebug>
#include <QtCore/QTextCodec>

#include <boost/bind.hpp>

#include "fileparser.h"

FileParser::FileParser (QObject *parent)
	: QObject (parent)
	, running_ (false)
{

}

FileParser::~FileParser()
{

}

QString FileParser::fileName() const
{
	return fileName_;
}

void FileParser::setFileName (const QString &fileName)
{
	fileName_ = fileName;
	emit progress (0, size ());
}

int FileParser::size () const
{
	return QFileInfo (fileName_).size ();
}

QString FileParser::lastError() const
{
	return lastError_;
}

class SetToFalse
{
public:
	SetToFalse (bool &value) : value_ (value) {}
	~SetToFalse () {
		value_ = false;
	}

private:
	Q_DISABLE_COPY (SetToFalse)

private:
	bool &value_;
};

void FileParser::start()
{
	if (running_) {
		return;
	}

	running_ = true;
	SetToFalse setToFalse (running_);

	emit started ();

	QFile file (fileName_);

	if (!file.open (QIODevice::ReadOnly)) {
		lastError_ = file.errorString ();
		running_ = false;
		emit finished ();
		return;
	}
	
	const int fileSize = file.size ();

	typedef std::vector<char> Buffer;

	enum {BufferSize = 1024};
	Buffer buffer (BufferSize, 0);

	while (running_ && !file.atEnd ()) {
		const int readed = file.readLine (&buffer [0], BufferSize - 1);

		emit progress (file.pos(), fileSize);

		if (readed == BufferSize) {
			lastError_ = tr ("Line longer that %1 symbols").arg (BufferSize);
			break;
		}

		parseLine (&buffer [0], readed);
	}

	emit progress (fileSize, fileSize);
	emit finished ();
}

void FileParser::stop()
{
	running_ = false;
}

namespace
{
	bool isLetter (unsigned char c)
	{
		return (65 <= c && c <= 90)
			   || (97 <= c && c <= 122)
			   || 192 <= c;
	}
}

void FileParser::parseLine (const char *const data, int dataSize)
{
	static const QTextCodec *codec = QTextCodec::codecForName ("Windows-1251");
	const char *const end = data + dataSize;
	const char *it = data;

	while (it != end) {
		it = std::find_if (it, end, boost::bind (&isLetter, _1));

		if (it != end) {
			const char *const endWord = std::find_if (it,
										end,
										boost::bind (
											std::logical_not<bool>(),
											boost::bind (&isLetter, _1)));
			emit wordFound (codec->toUnicode (it, std::distance (it, endWord)));
			it = endWord;
		}
	}
}

