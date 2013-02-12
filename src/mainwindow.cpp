/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QThread>
#include <QtCore/QDateTime>

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
	, started_ (new QDateTime)
{
	ui_->setupUi (this);

	connect (ui_->selectFile_,
			 SIGNAL (clicked ()),
			 SLOT (selectFile()));

	connect (fileParser_, SIGNAL (progress (int, int)),
			 ui_->progressBar_, SLOT (setValue (int)));

	connect (ui_->changeCalculateState_,
			 SIGNAL (clicked ()),
			 SLOT (startWork()));
	connect (ui_->changeCalculateState_, SIGNAL (clicked ()),
			 wordsCounter_, SLOT (clear()));
	connect (ui_->changeCalculateState_, SIGNAL (clicked ()),
			 fileParser_, SLOT (start()));

	connect (wordsCounter_,
			 SIGNAL (wordsChanged()),
			 SLOT (updateProgress()));

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
			 wordsCounter_, SLOT (appendWord (QString)),
			 Qt::DirectConnection);
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
	const QFileInfo fi = QFileDialog::getOpenFileName (this,
						 tr ("Open file"),
						 QDir::homePath());

	if (fi.exists() && fi.size() > 0) {
		fileParser_->setFileName (fi.absoluteFilePath());
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

void MainWindow::updateProgress()
{
	ui_->wordsCountLabel_->setText (QString::number (wordsCounter_->wordsCount()));

	const QDateTime current = QDateTime::currentDateTime();

	const int elapsed = started_->secsTo (current);


	int row = 0;

	foreach (const QString &word, wordsCounter_->topList ()) {
		if (ui_->resultsView_->count() == row) {
			ui_->resultsView_->addItem (word);
		} else {
			ui_->resultsView_->item (row)->setText (word);
		}

		++row;
	}
}

void MainWindow::startWork()
{
	*started_ =  QDateTime::currentDateTime ();
	ui_->startedLabel_->setText (started_->toString ("dd.MM.yyyy hh:mm:ss"));
}
