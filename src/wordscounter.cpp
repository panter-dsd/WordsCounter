/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QDebug>

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
	qDebug () << word;

	Words::iterator it = words_.find (word);

	if (it == words_.end()) {
		it = words_.insert (word, 0);
	}

	++ (*it);
	updateTopList (it);
}

void WordsCounter::updateTopList (const Words::const_iterator &updated)
{
	topList_.removeAll (updated);
	TopList::iterator it = std::lower_bound (topList_.begin(),
						   topList_.end(),
						   updated,
						   boost::bind (&lessThen, _1, _2));
	topList_.insert (it, updated);

	if (topList_.size() > TopListSize) {
		topList_.pop_front ();
	}
}

Words WordsCounter::topList() const
{
	Words result;

	for (TopList::const_iterator it = topList_.begin(),
			end = topList_.end(); it != end; ++it) {
		result.insert (it->key(), it->value());
	}

	return result;
}
