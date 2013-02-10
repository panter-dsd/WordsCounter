/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QThread>

#include <QtGui/QCloseEvent>
#include <QtGui/QFileDialog>

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

	connect (ui_->selectFile_,
			 SIGNAL (clicked ()),
			 SLOT (selectFile()));

	connect (fileParser_, SIGNAL (progress (int, int)),
			 ui_->progressBar_, SLOT (setValue (int)));

	init ();
	updateWindowTitle();
	updateButtons ();
}

MainWindow::~MainWindow()
{
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

void MainWindow::closeEvent (QCloseEvent *e)
{
	for (Threads::const_iterator it = threads_.begin(),
			end = threads_.end(); it != end; ++it) {
		(*it)->quit ();
	}

	QWidget::closeEvent (e);
}

void MainWindow::selectFile()
{
	const QString fileName = QFileDialog::getOpenFileName (this,
							 tr ("Open file"),
							 QDir::homePath());

	if (!fileName.isEmpty()) {
		fileParser_->setFileName (fileName);
		ui_->progressBar_->setRange (0, fileParser_->size ());
		updateWindowTitle ();
		updateButtons ();
	}
}

void MainWindow::updateWindowTitle()
{
	QString title = tr ("Worlds parser");

	const QString fileName = fileParser_->fileName ();

	if (!fileName.isEmpty()) {
		title += ": " + fileName;
	}

	setWindowTitle (title);
}
