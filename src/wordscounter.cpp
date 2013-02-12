/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QMutex>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <boost/bind.hpp>

#include <functional>

#include "wordscounter.h"

namespace
{
	bool lessThen (const Words::const_iterator &l,
				   const Words::const_iterator &r)
	{
		return l.value () < r.value ();
	}
}


WordsCounter::WordsCounter (QObject *parent)
	: QObject (parent)
	, mutex_ (new QMutex)
{

}

WordsCounter::~WordsCounter()
{

}

int WordsCounter::wordsCount() const
{
	return words_.size ();
}

void WordsCounter::appendWord (const QString &word)
{
	//qDebug () << word;

	QMutexLocker locker (mutex_.get ());

	Words::iterator it = words_.find (word);

	if (it == words_.end()) {
		it = words_.insert (word, 0);
	}

	++ (*it);
	updateTopList (it);
	emit wordsChanged ();
}

void WordsCounter::updateTopList (const Words::const_iterator &updated)
{
	topList_.remove (updated);
	TopList::iterator it = std::lower_bound (topList_.begin(),
						   topList_.end(),
						   updated,
						   boost::bind (&lessThen, _1, _2));
	topList_.insert (it, updated);

	if (topList_.size() > TopListSize) {
		topList_.pop_front ();
	}
}

QStringList WordsCounter::topList() const
{
	QMutexLocker locker (mutex_.get ());

	QStringList result;

	for (TopList::const_reverse_iterator it = topList_.rbegin(),
			end = topList_.rend(); it != end; ++it) {
		result.push_back (it->key());
	}

	return result;
}

bool WordsCounter::isEmpty () const
{
	return words_.isEmpty ();
}

void WordsCounter::clear ()
{
	topList_.clear ();
	words_.clear ();
}

bool WordsCounter::saveResult (const QString &fileName) const
{
	QFile file (fileName);

	if (!file.open (QIODevice::WriteOnly)) {
		return false;
	}

	QTextStream stream (&file);
	stream.setCodec ("UTF-8");

	typedef QMultiMap<int, QString> SortByCount;
	SortByCount sortByCount;

	for (Words::const_iterator it = words_.begin(),
			end = words_.end(); it != end; ++it) {
		sortByCount.insert (it.value(), it.key());
	}

	for (SortByCount::const_iterator it = sortByCount.begin(),
			end = sortByCount.end(); it != end; ++it) {
		stream << it.value() << ": " << it.key() << endl;
	}

	return true;
}
