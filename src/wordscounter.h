/**
 * @author PanteR
 * @date 10.02.2013
 */

#pragma once

#include <QtGui/QMainWindow>

class WordsCounter : public QMainWindow
{
	Q_OBJECT

public:
	WordsCounter (QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~WordsCounter();
};
