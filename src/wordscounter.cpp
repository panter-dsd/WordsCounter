/**
 * @author PanteR
 * @date 10.02.2013
 */

#include "fileparser.h"

#include "ui_wordscounter.h"
#include "wordscounter.h"

WordsCounter::WordsCounter (QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow (parent, flags)
	, ui_ (new Ui::WordsCounter)
	, fileParser_ (new FileParser (this))
{
	ui_->setupUi (this);

	updateButtons ();
}

WordsCounter::~WordsCounter()
{}

void WordsCounter::updateButtons()
{
	const bool isFileSelected = !fileParser_->fileName().isEmpty();
	ui_->changeCalculateState_->setEnabled (isFileSelected);
	ui_->saveResult_->setEnabled (isFileSelected);
}
