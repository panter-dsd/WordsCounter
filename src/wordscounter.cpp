/**
 * @author PanteR
 * @date 10.02.2013
 */

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
	Q_UNUSED (word)
}
