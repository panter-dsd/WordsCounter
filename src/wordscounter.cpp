/**
 * @author PanteR
 * @date 10.02.2013
 */

#include "ui_wordscounter.h"
#include "wordscounter.h"

WordsCounter::WordsCounter (QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow (parent, flags)
	, ui_ (new Ui::WordsCounter)
{
	ui_->setupUi (this);
}

WordsCounter::~WordsCounter()
{}
