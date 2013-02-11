/**
 * @author PanteR
 * @date 10.02.2013
 */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QMap>

#include <list>

typedef QMap<QString, int> Words;

class WordsCounter : public QObject
{
	Q_OBJECT

	enum {
		TopListSize = 10
	};

	typedef std::list<Words::const_iterator> TopList;

public:
	explicit WordsCounter (QObject *parent = 0);
	virtual ~WordsCounter();

	int wordsCount () const;
	QStringList topList () const;

Q_SIGNALS:
	void wordsChanged ();

public Q_SLOTS:
	void appendWord (const QString &word);

private:
	Q_DISABLE_COPY (WordsCounter)

	void updateTopList (const Words::const_iterator &updated);

private:
	Words words_;
	TopList topList_;
};
