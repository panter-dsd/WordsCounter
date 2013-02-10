/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QThread>

#include "fileparser.h"
#include "wordscounter.h"

#include "ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow (QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow (parent, flags)
	, ui_ (new Ui::MainWindow)
	, fileParser_ (new FileParser)
	, wordsCounter_ (new WordsCounter)
{
	ui_->setupUi (this);

	init ();
	updateButtons ();
}

MainWindow::~MainWindow()
{
	for (Threads::const_iterator it = threads_.begin(),
			end = threads_.end(); it != end; ++it) {
		(*it)->quit ();
	}
}

void MainWindow::init()
{
	QThread *thread = new QThread (this);
	threads_.push_back (thread);
	thread->start ();
	fileParser_->moveToThread (thread);

	thread = new QThread (this);
	threads_.push_back (thread);
	thread->start ();
	wordsCounter_->moveToThread (thread);

	connect (fileParser_, SIGNAL (wordFound (QString)),
			 wordsCounter_, SLOT (appendWord (QString)));
}

void MainWindow::updateButtons()
{
	const bool isFileSelected = !fileParser_->fileName().isEmpty();
	ui_->changeCalculateState_->setEnabled (isFileSelected);
	ui_->saveResult_->setEnabled (isFileSelected);
}
