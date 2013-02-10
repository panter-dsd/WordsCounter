/**
 * @author PanteR
 * @date 10.02.2013
 */

#pragma once

#include <QtCore/qobject.h>

class WordsCounter : public QObject
{
	Q_OBJECT

public:
	explicit WordsCounter (QObject *parent = 0);
	virtual ~WordsCounter();

private:
	Q_DISABLE_COPY (WordsCounter)
};
