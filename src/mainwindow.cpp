/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QThread>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QMetaObject>

#include <QtGui/QCloseEvent>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include <algorithm>

#include <boost/bind.hpp>

#include "fileparser.h"
#include "wordscounter.h"

#include "ui_mainwindow.h"
#include "mainwindow.h"

enum {UpdateInterval = 100};

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
	connect (ui_->saveResult_,
			 SIGNAL (clicked ()),
			 SLOT (saveResult()));

	connect (fileParser_, SIGNAL (progress (int, int)),
			 ui_->progressBar_, SLOT (setValue (int)));

	connect (ui_->changeCalculateState_,
			 SIGNAL (clicked ()),
			 SLOT (startWork()));

	connect (wordsCounter_,
			 SIGNAL (wordsChanged()),
			 SLOT (updateProgress()));
	connect (fileParser_, SIGNAL (started()), SLOT (updateButtons()));
	connect (fileParser_, SIGNAL (finished()), SLOT (updateButtons()));
	connect (fileParser_, SIGNAL (finished()), SLOT (workFinished()));

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
	ui_->changeCalculateState_->setText (fileParser_->isRunning ()
										 ? tr ("Stop calculate")
										 : tr ("Start calculate")
										);
	ui_->saveResult_->setEnabled (!fileParser_->isRunning()
								  && !wordsCounter_->isEmpty());
}

void MainWindow::closeEvent (QCloseEvent *e)
{
	if (fileParser_->isRunning()) {
		QMessageBox::critical (this,
							   QString(),
							   tr ("Stop before quit")
							  );
		e->ignore ();
	} else {

		std::for_each (threads_.begin(),
					   threads_.end(),
					   boost::bind (&QThread::quit, _1));

		QWidget::closeEvent (e);
	}
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
	} else {
		QMessageBox::critical (this,
							   tr ("Open file"),
							   tr ("File not select or size is 0")
							  );
	}
}

void MainWindow::updateWindowTitle()
{
	QString title = tr ("Words counter");

	const QString fileName = fileParser_->fileName ();

	if (!fileName.isEmpty()) {
		title += ": " + fileName;
	}

	setWindowTitle (title);
}

void MainWindow::updateProgress (bool forceUpdate)
{
	static QTime lastUpdate = QTime::currentTime ();

	if (!forceUpdate) {
		const QTime time = QTime::currentTime ();

		if (lastUpdate.msecsTo (time) > UpdateInterval) {
			lastUpdate = time;
		} else {
			return;
		}
	}

	const QDateTime current = QDateTime::currentDateTime();

	const int elapsed = started_->msecsTo (current);

	ui_->wordsCountLabel_->setText (QString::number (wordsCounter_->wordsCount()));

	ui_->workedTimeLabel_->setText (QTime().addMSecs (elapsed).toString ("hh:mm:ss"));

	ui_->etaLabel_->setText (QTime().addMSecs (calculateEta (elapsed)).toString ("hh:mm:ss"));

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

int MainWindow::calculateEta (int elapsed) const
{
	const int progress = std::max (1, ui_->progressBar_->value());
	const int total = ui_->progressBar_->maximum ();
	const int eta = static_cast<double> (elapsed) * (total - progress) / progress ;

	return eta;
}


void MainWindow::startWork()
{
	if (!fileParser_->isRunning()) {
		qDebug() << "Start";
		wordsCounter_->clear ();
		*started_ =  QDateTime::currentDateTime ();
		QMetaObject::invokeMethod (fileParser_, "start");
	} else {
		qDebug() << "Stop";
		fileParser_->stop ();
	}

	updateButtons ();
}

void MainWindow::workFinished()
{
	updateProgress (true);

	if (!fileParser_->lastError().isEmpty()) {
		QMessageBox::critical (this,
							   QString(),
							   fileParser_->lastError()
							  );
	}
}


void MainWindow::saveResult()
{
	const QString fileName = QFileDialog::getSaveFileName (this,
							 tr ("Save result"),
							 QDir::homePath());

	if (!fileName.isEmpty()) {
		const bool result = wordsCounter_->saveResult (fileName);

		if (result) {
			QMessageBox::information (this,
									  tr ("Save result"),
									  tr ("Result is saved")
									 );
		} else {
			QMessageBox::critical (this,
								   tr ("Save result"),
								   tr ("Error save result")
								  );
		}
	}
}
