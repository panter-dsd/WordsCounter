/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QDebug>

#include "wordscounter.h"

WordsCounter::WordsCounter (QObject *parent)
	: QObject (parent)
{

}

WordsCounter::~WordsCounter()
{

}

void WordsCounter::appendWord (const QString &word)
{
	Words::iterator it = words_.find (word);

	if (it == words_.end()) {
		it = words_.insert (word, 0);
	}

	++ (*it);
}
