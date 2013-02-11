/**
 * @author PanteR
 * @date 10.02.2013
 */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>

typedef QMap<QString, int> Words;

class WordsCounter : public QObject
{
	Q_OBJECT

	enum {
		TopListSize = 10
	};

	typedef QList<Words::const_iterator> TopList;

public:
	explicit WordsCounter (QObject *parent = 0);
	virtual ~WordsCounter();

	int wordsCount () const;
	Words topList () const;

public Q_SLOTS:
	void appendWord (const QString &word);

private:
	Q_DISABLE_COPY (WordsCounter)

	void updateTopList (const Words::const_iterator &updated);

private:
	Words words_;
	TopList topList_;
};
