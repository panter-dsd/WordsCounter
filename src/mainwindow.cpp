/**
 * @author PanteR
 * @date 10.02.2013
 */

#include "fileparser.h"

#include "ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow (QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow (parent, flags)
	, ui_ (new Ui::MainWindow)
	, fileParser_ (new FileParser (this))
{
	ui_->setupUi (this);

	updateButtons ();
}

MainWindow::~MainWindow()
{}

void MainWindow::updateButtons()
{
	const bool isFileSelected = !fileParser_->fileName().isEmpty();
	ui_->changeCalculateState_->setEnabled (isFileSelected);
	ui_->saveResult_->setEnabled (isFileSelected);
}
