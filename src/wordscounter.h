/**
 * @author PanteR
 * @date 10.02.2013
 */

#pragma once

#include <QtGui/QMainWindow>

#include <auto_ptr.h>

namespace Ui
{
	class WordsCounter;
}

class WordsCounter : public QMainWindow
{
	Q_OBJECT

public:
	explicit WordsCounter (QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~WordsCounter();

private:
	Q_DISABLE_COPY (WordsCounter)

private Q_SLOTS:
	void updateButtons ();

private:
	std::auto_ptr<Ui::WordsCounter> ui_;
	class FileParser *fileParser_;
};
