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

public Q_SLOTS:
	void appendWord (const QString &word);

private:
	Q_DISABLE_COPY (WordsCounter)
};
